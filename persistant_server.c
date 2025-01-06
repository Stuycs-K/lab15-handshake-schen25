#include "pipe_networking.h"
#include <signal.h>

static void sighandler(int signo){
  if (signo==SIGINT){
    remove(WKP);
    kill(getpid(), SIGTERM);
  }
  if (signo==SIGPIPE){
    printf("Client exited\n");
  }
}

int main() {
  signal(SIGINT, sighandler);
  signal(SIGPIPE, sighandler);
  int to_client;
  int from_client;
  int randNum;

  srand(getpid());
  while (1){
    from_client = server_handshake( &to_client );
    while (1){
      randNum = rand()%101;
      printf("Sending %d to clients\n", randNum);
    //  printf("to_client: %d\n", to_client);
      int w = write(to_client, &randNum, sizeof(int));
      if (w<=0){
        break;
      }
      sleep(1);
    }
    close(to_client);
    close(from_client);
  }
}
