#include "WifiComm.h"
#include "rs232.h"
#define COMMAND_TIME 1
#define START_MARK 128
#define MOTOR0 0
#define MOTOR1 1
#define MOTOR2 2
#define MOTOR3 3
#define ROT_F 1
#define ROT_B 0
#define ARDUINO_PORT 0
#define FORWARD 'w'
#define LEFT 'a'
#define BACK 's'
#define RIGHT 'd'
#define TURN_LEFT 'j'
#define TURN_RIGHT 'l'
#define SLOW 'k'
#define FAST 'i'
#define SPACE 0x20

const int overAllPow = 200;
unsigned char primeCommand[] = {128, 16, 0, 0, 0, 0, 
                                0, 1, 0, 0,
                                0, 2, 0, 0,
                                0, 3, 0, 0};
unsigned char stopCommand[] = {128, 16, 0, 0, 0, 0, 
                               0, 1, 0, 0,
                               0, 2, 0, 0,
                               0, 3, 0, 0};

void parseCommand(char* command, int count){
  for(int idx = 0; idx < count; idx++){
    int dir[4], curPow = overAllPow, dirChange = 0;
    switch(*(command + idx)){
      case FORWARD:
        dirChange = 1;
        for(int i = 0; i < 4; i++)
          dir[i] = ROT_F;
        break;
      case LEFT:
        dirChange = 1;
        dir[0] = ROT_F;
        dir[1] = ROT_B;
        dir[2] = ROT_F;
        dir[3] = ROT_B;
        break;
      case BACK:
        dirChange = 1;
        for(int i = 0; i < 4; i++)
          dir[i] = ROT_B;
        break;
      case RIGHT:
        dirChange = 1;
        dir[0] = ROT_B;
        dir[1] = ROT_F;
        dir[2] = ROT_B;
        dir[3] = ROT_F;
        break;
      case TURN_LEFT:
        dirChange = 1;
        dir[0] = ROT_B;
        dir[1] = ROT_B;
        dir[2] = ROT_F;
        dir[3] = ROT_F;
        break;
      case TURN_RIGHT:
        dirChange = 1;
        dir[0] = ROT_F;
        dir[1] = ROT_F;
        dir[2] = ROT_B;
        dir[3] = ROT_B;
        break;
      case SLOW:
        if(overAllPow > 100){
          overAllPow -= 5;
          curPow -= 5;
        }
        break;
      case FAST:
        if(overAllPow < 255){
          overAllPow += 5;
          curPow += 5;
        }
      case SPACE:
        curPow = 0;
        break;
      default:
        fprintf(stderr, "Received unknown command %s\n", command);
    }
    for(int i = 0; i < 4; i++){
      if(dirChange != 0)
        primeCommand[(4 + i * 4)] = dir[i];
      primeCommand[(5 + i * 4)] = curPow;
    }
    RS232_SendBuf(ARDUINO_PORT, primeCommand, sizeof(primeCommand));
  }
}

WifiComm::WifiComm(CommData* commData){
  mCommData = commData;
}

WifiComm::~WifiComm(){
  if(mCommData != NULL)
    free(mCommData);
}

void WifiComm::initiateComm(){
  mSocketFd = socket(AF_INET, SOCK_STREAM, 0);
  if(mSocketFd < 0){
    printErrMsg("Socket cretion failed");
    exit(1);
  }
  struct sockaddr_in serverAddr;
  bzero((char *) &serverAddr, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  bcopy((char *)mServerHost->h_addr,
    (char *)&serverAddr.sin_addr.s_addr,
    mServerHost->h_length);
  serverAddr.sin_port = htons(mServerPort);
  if(connect(mSocketFd, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0){
    printErrMsg("Connection to server failed");
    exit(1);
  }
}

void WifiComm::startComm(){
  while(1){
    char buffer[256];
    int count = read(mSocketFd, buffer, 256);
    if (count < 0){
      printErrMsg("Cannot read from server");
      exit(1);
    } else if (count > 0){
      writeCharToFd(STDOUT_FILENO, buffer, count);
      parseCommand(buffer, count);
    }
  }
}

void WifiComm::sendToServer(char arr, int arrLen){

}

void WifiComm::listenFromServer(){

}

void WifiComm::setServerIp(char* ip){
  mServerHost = gethostbyname(ip);
  if (mServerHost == NULL){
    printErrMsg("Unable to obtain ip of localhost");
    exit(1);
  }
}

void WifiComm::setServerPort(int port){
  mServerPort = port;
}
