#include "pipe_networking.h"

int main() {
  int to_server;
  int from_server;
  int randNum;
  from_server = client_handshake( &to_server );
  while (1){
    int r = read(from_server, &randNum, sizeof(int));
    if (r<0){
      printf("errno: %d %s", errno, strerror(errno));
      exit(1);
    }
    printf("Received number: %d\n", randNum);
  }
}
