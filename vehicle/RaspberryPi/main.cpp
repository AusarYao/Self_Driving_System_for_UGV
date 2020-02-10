/*
0       2
 \     /
 /     \
1       3
motor instruction id 0, 0-3 motor id, 0 back/ 1 forward, 0 - 255 power
*/
#include "utilities.h"
#include "WifiComm.h"
#include "rs232.h"

#define PC_COMM 0
#define ARDUINO_COMM 1
#define FAIL 1
#define IP_FLAG 'i'
#define PORT_FLAG 'p'
#define ARDUINO_PORT 0
#define ARDUINO_BAUD 57600


struct option LongOptions[] = {
  {"ip",     required_argument, NULL, IP_FLAG},
  {"port",      required_argument, NULL, PORT_FLAG},
  { NULL, 0, NULL, 0 }
};

WifiComm* wifiComm;

void handleOptions(int argc, char **argv);
void freeWifiComm(){ free(wifiComm); };
void initializeUSB(int port, int baudRate);
void startArduComm(CommData* data);

int main(int argc, char** argv){
  CommData* commData = (CommData*)malloc(sizeof(CommData));
  wifiComm = new WifiComm(commData);
  atexit(freeWifiComm);
  handleOptions(argc, argv);
  initializeUSB(ARDUINO_PORT, ARDUINO_BAUD);
  wifiComm->initiateComm();
  #pragma omp parallel num_threads(2) shared(commData)
  {
    int id = omp_get_thread_num();
    switch(id){
      case PC_COMM:
        wifiComm->startComm();
        break;
      case ARDUINO_COMM:
        // startArduComm(commData);
        break;
      default:
        printErrMsg("Extra thread created");
        exit(1);
    }
  }
  return 0;
}


//Handles optional arguments passed to the program
void handleOptions(int argc, char** argv){
  int option = 0, optionIdx = 0;
  while((option = getopt_long(argc, argv, "", LongOptions, &optionIdx)) != -1) {
    switch(option){
      case PORT_FLAG:
        wifiComm->setServerPort(atoi(optarg));
        break;
      case IP_FLAG:
        wifiComm->setServerIp(optarg);
        break;
      default: //unknown argument
        printErrMsg("Invalid argument");
        exit(FAIL);
    }
  }
}

void initializeUSB(int port, int baudRate){
  char mode[]={'8','N','1',0};
  if(RS232_OpenComport(port, baudRate, mode)){
    printErrMsg("Can not open comport");
    exit(1);
  }
}

// void startArduComm(CommData* data){
//   while(1){
//     if(data->isNew){

//     }
//   }
// }