// client_socket.cpp

#include "client_socket.h"
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define SERVER_IP "127.0.0.2"
#define BUFFER_SIZE 1024

/*
Client node class that defines an instance of a client-side socket.
*/

// private methods
void Client_Socket::handleError(const std::string &errorMessage) {
  perror(errorMessage.c_str());
  exit(EXIT_FAILURE);
}

Client_Socket::Client_Socket() {
  client_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (client_fd < 0) {
    handleError("Socket creation error");
  }
}

// TODO:define param to allow server IP and Port to be passed as argument to
// connectToServer()
void Client_Socket::connectToServer() {
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);

  if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
    handleError("Invalid address/ Address not supported");
  }

  if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
      0) {
    handleError("Connection failed");
  }
}

// TODO:define param to allow message to be passed as argument to sendMessage()
void Client_Socket::sendMessage() {
  std::string message = "Client Message";
  char buffer[BUFFER_SIZE] = {0};

  send(client_fd, message.c_str(), message.length(), 0);
  int valread = read(client_fd, buffer, BUFFER_SIZE);
  if (valread < 0) {
    handleError("Read error");
  }
  std::cout << "Server: " << buffer << std::endl;
}
