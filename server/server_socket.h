// server_socket.h

#ifndef SERVER_SOCKET_H
#define CLIENT_SOCKET_H

#include <string>

class Server_Socket {
private:
  int server_fd;
  int new_socket;
  void handleError(const std::string &errorMessage);
  void bindSocket(struct sockaddr_in &address);
  void setSocketOptions();
  void listenForConnections();
  void acceptAndHandleClient(struct sockaddr_in &address);

public:
  Server_Socket();
  // methods to start and stop server will return status code
  bool start();
  bool stop();
};

#endif // SERVER_SOCKET_H