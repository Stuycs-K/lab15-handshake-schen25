#include "pipe_networking.h"

int main() {
  int to_client;
  int from_client;

  srand(getpid());
  int randNum = rand()%101;
  printf("Sending %d to clients\n", randNum);


  from_client = server_handshake( &to_client );
}
