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
  printf("Server created WKP, preparing to read...\n");
  from_client = open(WKP, O_RDONLY); // block until WKP can read
  if (from_client<0){
    printf("error opening WKP\n");
    exit(1);
  }
  printf("Server removing WKP...\n");
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
  *to_client = server_connect(from_client);
  printf("End of server handshake.\n");
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
  int syn_ack;
  char name[200];
  sprintf(name, "%d", getpid());
  printf("This is name: %s\n", name);
  printf("Client making private pipe...\n");
  int x = mkfifo(name, 0644); // make the private pipes
  printf("Client opening WKP...\n");
  int f = open(WKP, O_WRONLY);
  if (f<0){
    printf("error opening WKP\n");
    exit(1);
  }
  *to_server = f; // set to fds for upstream pipe
  printf("Client writing PP name to WKP...\n");
  write(f, name, sizeof(name)); // write PP to WKP
  printf("Client opening PP...\n");
  from_server = open(name, O_RDONLY); // block until PP can read
  if (from_server<0){
    printf("error opening PP\n");
    exit(1);
  }
  printf("Client removing PP...\n");
  remove(name);
  printf("Client reading SYN_ACK...\n");
  read(from_server, &syn_ack, sizeof(int)); // reading syn_ack
  printf("Client sending final ACK...\n");
  write(f, syn_ack+1, sizeof(int)); // send final ACK?
  printf("End of client handshake.\n");
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
  char name[200];
  int final_ack;
  int randNum = 13908; // change to random later
  printf("Server reading PP PID...\n");
  read(from_client, &name, sizeof(int)); //read the PP name/PID
  printf("This is name: %s\n", name);
  printf("Server opening PP...\n");
  to_client = open(name, O_WRONLY); //open pp
  if (to_client<0){
    printf("error opening PP\n");
    exit(1);
  }
  printf("Server sending SYN_ACK...\n");
  write(to_client, randNum, sizeof(int)); // sending SYN_ACK
  printf("Server reading final ACK...\n");
  read(from_client, &final_ack, sizeof(int)); // read final ACK?

  return to_client;
}
