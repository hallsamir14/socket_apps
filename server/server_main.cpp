#include "server_socket.cpp"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  Server_Socket server = Server_Socket();

  server.start();
  server.stop();

  return 0;
}