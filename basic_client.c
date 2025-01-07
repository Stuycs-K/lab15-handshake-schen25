#include "pipe_networking.h"
#include <signal.h>

static void sighandler(int signo){
  // if (signo==SIGINT){
  //   remove(WKP);
  //   kill(getpid(), SIGTERM);
  // }
  if (signo==SIGPIPE){
    printf("Server exited\n");
    kill(getpid(), SIGTERM);
  }
}

int main() {
  int to_server;
  int from_server;
  srand(getpid());
  int randNum = getpid();
  char str[200];
//  signal(SIGINT, sighandler);
  signal(SIGPIPE, sighandler);
  sprintf(str, "Message from client with PID %d", randNum);
  from_server = client_handshake( &to_server );
  while (1){
    //forking server part
    int w = write(to_server, str, sizeof(str));
    //printf("Sending server: %s\n", str);
    if (w<=0){
      break;
    }
    int r = read(from_server, str, sizeof(str));
    printf("Received from subserver: %s\n", str);
  }
  close(from_server);
  close(to_server);
}
