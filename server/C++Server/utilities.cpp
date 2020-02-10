/*
NAME: Yuchen Yao
EMAIL: ausaryao00@gmail.com
ID: 605134100
*/
#include "utilities.h"
#define SUCCESS 0   //normal execution, shutdown on ^D
#define FAIL 1      //unrecognized argument or system call failure
#define CR '\r'
#define LF '\n'
#define C_D 0x04
#define C_C 0x03
#define BUFFER_SIZE 256
#define ENABLE 1
#define DISABLE 0
#define READ 0
#define WRITE 1

struct termios OriginalAttributes;

//Print out error message to file descriptor 3
void printErrMsg(const char* err){
  fprintf(stderr, "Error: %s %s\n", err, strerror(errno));
}

//Set up terminal on startup
void setupTerminal(){
  if(!isatty(STDIN_FILENO)){
    printErrMsg("stdin is not terminal");
    exit(FAIL);
  }
  struct termios newAttr;
  if(tcgetattr(STDIN_FILENO, &OriginalAttributes)){   //get original terminal attributes
    printErrMsg("cannot get original terminal attributes");
    exit(FAIL);
  }
  if (atexit(resetTerminal) != 0){    //set function to call at exit
    printErrMsg("atexit() function register failed");
    exit(FAIL);
  }
  tcgetattr(STDIN_FILENO, &newAttr);    //set new attributes
  newAttr.c_iflag = ISTRIP;
  newAttr.c_lflag = 0;
  tcsetattr(STDIN_FILENO, TCSANOW, &newAttr);
}

//Reset terminal before shutdown
void resetTerminal(){
  if (tcsetattr(STDIN_FILENO, TCSANOW, &OriginalAttributes) != 0){
    printErrMsg("reseting terminal attributes failed");
    exit(FAIL);
  }
}

//Echo input to fd
void writeCharToFd(int fd, char* buffer, int bufferSize){
  if(write(fd, buffer, bufferSize) < 0){
    printErrMsg("writing to file descriptor failed");
    exit(FAIL);
  }
}

//Echo string back to terminal
void echoStringTerminal(){
  char buffer[BUFFER_SIZE];
  while(1) {
    int count = read (STDIN_FILENO, buffer, BUFFER_SIZE);
    if (count < 0){
      printErrMsg("reading from stdin failed");
      exit(FAIL);
    }
    int idx = 0;
    while(idx < count){
      char cur = buffer[idx++], *result;
      size_t length;
      switch (cur){
      case CR:
      case LF:
        result = "\r\n";
        length = 2;
        break;
      case C_D:
        writeCharToFd(STDOUT_FILENO, "^D", 2);
        exit(SUCCESS);
      case C_C:
        result = "^C";
        length = 2;
        break;
      default:
        result = &cur;
        length = 1;
        break;
      }
      writeCharToFd(STDOUT_FILENO, result, length);
    }
  }
}

//Print help message
void printHelp(char* message){
  fprintf(stderr, "%s", message);
}

//Read from input and report error when failed
int readFromFd(int fd, char* buffer, int bufferSize){
  int count = read(fd, buffer, bufferSize);
  if (count < 0){
    printErrMsg("Cannot read from input");
    exit(FAIL);
  }
  return count;
}

//Cup file descriptor and report error when failed
void dupFd(int fd){
  if (dup(fd) < 0){
    printErrMsg("Error dup file descriptor");
    exit(FAIL);
  }
}

//Close file descriptor and report error when failed
void closeFd(int fd){
  if (close(fd) < 0){
    printErrMsg("Error closing file descriptor");
    exit(FAIL);
  }
}

//Kill process and report error when failed
void killPs(int pid, int signum){
  if(kill(pid, signum) < 0){
    printErrMsg("terminate child process failed");
    exit(FAIL);
  }
}