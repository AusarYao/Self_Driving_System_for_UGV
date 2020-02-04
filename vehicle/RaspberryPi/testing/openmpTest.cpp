#include "omp.h"
#include <stdlib.h>
#include <stdio.h>
//Create different objects based on thread id with the same interface to guarentee
//data transmission and extensibility

//Comm module must be shared (cannot write to server at the same time. Will cause garbage data)
//Or open multiple sockets?
//Need to pass data between threads. e.g. force flush buffer by first transmitting it to

int main(){
  #pragma omp parallel num_threads(20)
  {
    int id = omp_get_thread_num();
    printf("hello %d\n", id);
  }
  return 0;
}