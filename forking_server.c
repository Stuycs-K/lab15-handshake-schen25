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
      sleep(1);
      
    }

    // while (1){
    //   randNum = rand()%101;
    //   printf("Sending %d to clients\n", randNum);
    //   int w = write(to_client, &randNum, sizeof(int));
    //   if (w<=0){
    //     break;
    //   }
    //   sleep(1);
    // }
    close(to_client);
    close(from_client);
  }
}
