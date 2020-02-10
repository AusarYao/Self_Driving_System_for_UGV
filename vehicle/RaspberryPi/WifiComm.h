#include "CommData.h"
#include "utilities.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace std;
class WifiComm {
  public:
    WifiComm(CommData* commData);
    ~WifiComm();
    void initiateComm();
    void startComm();
    void sendToServer(char arr, int arrLen);
    void listenFromServer();
    void setServerIp(char* ip);
    void setServerPort(int port);
    
  private:
    int mServerPort = -1;
    int mSocketFd = -1;
    struct hostent *mServerHost = NULL;
    CommData* mCommData = NULL;
};