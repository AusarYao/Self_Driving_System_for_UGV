#include <stdbool.h>
typedef struct listitem listitem;

struct CommData{
  char data[256];
  int dataLen = 0;
  bool isNew =  false;
};