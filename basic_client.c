#include "pipe_networking.h"
#include <signal.h>

static void sighandler(int signo){
  // if (signo==SIGINT){
  //   remove(WKP);
  //   kill(getpid(), SIGTERM);
  // }
  if (signo==SIGPIPE){
    printf("Server exited\n");
  }
}

int main() {
  int to_server;
  int from_server;
  int randNum = getpid();
  char str[200];
  signal(SIGPIPE, sighandler);
  sprintf(str, "Message from client with PID %d", randNum);
  from_server = client_handshake( &to_server );
  while (1){
    //persistant part
    // int r = read(from_server, &randNum, sizeof(int));
    // if (r<=0){
    //   break;
    // }
    // printf("Received number: %d\n", randNum);
    //forking server part
    int w = write(to_server, str, sizeof(str));
    //printf("Sending server: %s\n", str);
    if (w<=0){
      break;
    }
  }
  close(from_server);
  close(to_server);
}
