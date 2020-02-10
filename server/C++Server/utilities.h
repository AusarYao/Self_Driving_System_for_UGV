/*
NAME: Yuchen Yao
EMAIL: ausaryao00@gmail.com
ID: 605134100
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <getopt.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/wait.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "zlib.h"

void printErrMsg(const char* err);
void setupTerminal();
void resetTerminal();
void echoStringTerminal();
void writeCharToFd(int fd, char* buffer, int bufferSize);
int readFromFd(int fd, char* buffer, int bufferSize);
void dupFd(int fd);
void closeFd(int fd);
void killPs(int pid, int signum);
void printHelp(char* message);