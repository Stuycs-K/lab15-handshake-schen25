#include "pipe_networking.h"

int main() {
  int to_client;
  int from_client;
  int randNum;

  while (1){
    from_client = server_handshake( &to_client );
    randNum = rand()%101;
    printf("Sending %d to clients\n", randNum);
    int w = write(to_client, &randNum, sizeof(int));
    if (w<0){
      printf("errno: %d %s", errno, strerror(errno));
      exit(1);
    }
    sleep(1);
    close(to_client);
    close(from_client);
  }
}
