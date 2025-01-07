#include "pipe_networking.h"
#include <signal.h>

static void sighandler(int signo){
  if (signo==SIGINT){
    remove(WKP);
    kill(getpid(), SIGTERM);
  }
  if (signo==SIGPIPE){
    printf("Client exited\n");
    kill(getpid(), SIGTERM);
  }
}

int main() {
  signal(SIGINT, sighandler);
  signal(SIGPIPE, sighandler);
  int to_client;
  int from_client;
  int randNum;
  char str[200];
  pid_t p;

  srand(getpid());
  while (1){
    from_client = server_setup(); // parts 1-3
    p = fork();
    if (p<0){
      perror("fork failed\n");
      exit(1);
    }
    else if (p==0){ // step 4
      server_handshake_half(&to_client, from_client);
      // communication after handshake
      while (1){
        int r = read(from_client, str, sizeof(str));
        if (r<=0){
          close(to_client);
          close(from_client);
          exit(0);
        }
        sleep(1);
        printf("Subserver received: %s\n", str);
        int w = write(to_client, str, sizeof(str));
        if (r<=0){
          close(to_client);
          close(from_client);
          exit(0);
        }
      }
    }
    close(to_client);
    close(from_client);
  }
}
