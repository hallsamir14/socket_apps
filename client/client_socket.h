// client_socket.h will contain foward declaration for data and methods for
// Client_Socket() class

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <string>

class Client_Socket {
private:
  bool status;
  int client_fd;
  int createSocket();

public:
  Client_Socket();
  void connectToServer();
  void sendMessage();
};

#endif // CLIENT_SOCKET_H