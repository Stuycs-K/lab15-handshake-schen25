#include "pipe_networking.h"
//UPSTREAM = to the server / from the client
//DOWNSTREAM = to the client / from the server
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  int from_client = 0;
  int a = mkfifo(WKP, 0644);
  if (a==-1) {
    perror("failed to create wkp\n");
    exit(1);
  }
  int f = open(WKP, O_RDONLY); // block until WKP can read
  if (f<0){
    printf("error opening WKP");
    exit(1);
  }
  read(f, &from_client, sizeof(int));
  remove(WKP);
  return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client) {
  int from_client = server_setup();
  int pp = open()

  return from_client;
}


/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int from_server;
  char* name =(char*)getpid();
  int x = mkfifo(name, 0644);
  int f = open(WKP, O_WRONLY);
  if (f<0){
    printf("error opening WKP");
    exit(1);
  }
  write(f, name, sizeof(name)); // write PP to WKP
  int pp = open(name, O_RDONLY); // block until PP can read
  if (pp<0){
    printf("error opening WKP");
    exit(1);
  }
  return from_server;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int to_client  = 0;
  return to_client;
}
