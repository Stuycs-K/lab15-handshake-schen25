#include "pipe_networking.h"

int main() {
  int to_server;
  int from_server;
  int randNum;
  from_server = client_handshake( &to_server );
  while (1){
    int r = read(from_server, &randNum, sizeof(int));
    if (r<=0){
      break;
    }
    printf("Received number: %d\n", randNum);
    //forking server part
    int w = write(to_server, &randNum, sizeof(int));
    if (w<=0){
      break;
    }
  }
}
