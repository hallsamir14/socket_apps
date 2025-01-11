#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <glog/logging.h>
#include "server_socket.h"
int main() {
  FLAGS_logtostderr = 1;  // Log all messages to stderr
  google::InitGoogleLogging("server_main");
  
  Server_Socket server = Server_Socket();

  server.start();
  server.stop();

  return 0;
}