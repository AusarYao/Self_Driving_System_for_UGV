/*
NAME: Yuchen Yao
EMAIL: ausaryao00@gmail.com
ID: 605134100
*/
#include "utilities.h"
#define SUCCESS 0   //normal execution, an error on the network socket from server
#define FAIL 1      //unrecognized argument or system call failure
#define BUFFER_SIZE 256
#define PORT_FLAG 'p'
#define ENABLE 1
#define DISABLE 0
#define READ 0
#define WRITE 1
#define C_D 0x04
#define C_C 0x03
#define SPACE 0x20
#define FORWARD 'w'
#define LEFT 'a'
#define BACK 's'
#define RIGHT 'd'
#define TURN_LEFT 'j'
#define TURN_RIGHT 'l'
#define SLOW 'k'
#define FAST 'i'
#define NETWORK 0
#define KEYBOARD 1
#define HELP "Usage:\n\
  --port=PORT_NUMBER        Connect to specified port(Mandatory)\n"

struct option LongOptions[] = {
  {"port",     required_argument, NULL, PORT_FLAG},
  { NULL, 0, NULL, 0 }
};

void handleOptions(int argc, char **argv);
void acceptConnection();
void handleNetworkInput();
void handleKeyboardInput();
void writeArr(int fd, char* buffer, int end);
void startComm();
void flushBuffer();
void closeNetworkFd();

char readBuffer[BUFFER_SIZE],
      compressBuffer[BUFFER_SIZE];
int portNum = -1,
    serverSocketFd = -1,
    clientSocketFd = -1;

//Main body
int main(int argc, char** argv){
  handleOptions(argc, argv);
  setupTerminal();
  acceptConnection();
  atexit(closeNetworkFd);
  startComm();
  exit(SUCCESS);
}

//Handles optional arguments passed to the program
void handleOptions(int argc, char** argv){
  int option = 0, optionIdx = 0;
  while((option = getopt_long(argc, argv, "", LongOptions, &optionIdx)) != -1) {
    switch(option){
      case PORT_FLAG:
        portNum = atoi(optarg);
        break;
      default: //unknown argument
        printHelp(HELP);
        exit(FAIL);
    }
  }
  if(portNum < 0){
    // printErrMsg("invalid --port -expecting a number as input(should be greater than 1024)");
    printHelp(HELP);
    exit(FAIL);
  }
}

//Handle input from client
void handleNetworkInput(){
  flushBuffer();
  char *buffer = readBuffer;
  int count = readFromFd(clientSocketFd, buffer, BUFFER_SIZE);
  printf("%s", buffer);
}

//Handle input from keyboard
void handleKeyboardInput(){
  flushBuffer();
  char *buffer = readBuffer;
  int count = readFromFd(STDIN_FILENO, buffer, BUFFER_SIZE);
  writeArr(clientSocketFd, buffer, count);
}

//Accept client connection request
void acceptConnection(){
  serverSocketFd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocketFd < 0){
    printErrMsg("Could not open socket");
    exit(FAIL);
  }
  struct sockaddr_in serverAddr, clientAddr;
  bzero((char *) &serverAddr, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(portNum);
  if (bind(serverSocketFd, (struct sockaddr *) &serverAddr,
              sizeof(serverAddr)) < 0){
    printErrMsg("Failed binding to server socket");
    exit(FAIL);
  }
  listen(serverSocketFd,5);
  unsigned int clientLen = sizeof(clientAddr);
  clientSocketFd = accept(serverSocketFd, (struct sockaddr *) &clientAddr, &clientLen);
  if (clientSocketFd < 0){
      printErrMsg("Cannot accept connection from client");
      exit(FAIL);
  }
  fcntl(clientSocketFd, F_SETFL, fcntl(0, F_GETFL) | O_NONBLOCK);  //Enable nonblocking for network fd
}

//Write an array to file descriptor and parse it (from server to client)
void writeArr(int fd, char* buffer, int end){
  int idx = 0;
  while(idx < end){
    char* cur = buffer + (idx++);
    switch (*(cur)){
      case C_D:
      case C_C:
        exit(SUCCESS);
        break;
      case FORWARD:
      case LEFT:
      case BACK:
      case RIGHT:
      case TURN_LEFT:
      case TURN_RIGHT:
      case SPACE:
      case SLOW:
      case FAST:
        writeCharToFd(fd, cur, 1);
        writeCharToFd(STDOUT_FILENO, cur, 1);
        break;
    }
  }
}

void startComm(){
  struct pollfd inputFdList[] = {
    {clientSocketFd, POLLIN, 0},
    {STDIN_FILENO, POLLIN | POLLHUP | POLLERR, 0},
  };
  while (1) {
    int pollResult = poll(inputFdList, 2, -1);    //wait for any input
    if(pollResult < 0){
      printErrMsg("poll input from client or shell failed");
      exit(FAIL);
    }
    if(pollResult == 0)
      continue;
    if(inputFdList[NETWORK].revents & POLLIN)
      handleNetworkInput();
    if(inputFdList[KEYBOARD].revents & POLLIN)
      handleKeyboardInput();
    if(inputFdList[NETWORK].revents & POLLHUP ||
       inputFdList[NETWORK].revents & POLLERR ||
       inputFdList[KEYBOARD].revents & POLLHUP ||
       inputFdList[KEYBOARD].revents & POLLERR)
       break;
  }
}

//Empty the two buffers
void flushBuffer(){
  bzero(readBuffer, sizeof(readBuffer));
  bzero(compressBuffer, sizeof(compressBuffer));
}

void closeNetworkFd(){
  closeFd(clientSocketFd);
  closeFd(serverSocketFd);
}