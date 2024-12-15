// client_socket.h will contain foward declaration for data and methods for
// Client_Socket() class

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <string>

class Client_Socket {
private:
  int client_fd;
  void handleError(const std::string &errorMessage);
  int createSocket();

public:
  Client_Socket();
  void connectToServer();
  void sendMessage();
};

#endif // CLIENT_SOCKET_H