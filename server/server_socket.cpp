#include "server_socket.h"
#include <arpa/inet.h>
#include <cstring>
#include <glog/logging.h>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <map>
#include <unistd.h>

#define PORT 8080
#define SERVER_IP "127.0.0.2"
#define BUFFER_SIZE 1024

// private methods..............
void Server_Socket::handleError(const std::string &errorMessage) {
  LOG(ERROR) << errorMessage;
  exit(EXIT_FAILURE);
}

void Server_Socket::bindSocket(struct sockaddr_in &address) {
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    throw std::runtime_error("Bind failed");
  }
}

void Server_Socket::setSocketOptions() {
  int opt = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt)) < 0) {
    throw std::runtime_error("Set socket options failed");
  }
}

void Server_Socket::listenForConnections() {
  if (listen(server_fd, 3) < 0) {
    throw std::runtime_error("Listen failed");
  }
}

void Server_Socket::acceptAndHandleClient(struct sockaddr_in &address) {
  socklen_t addrlen = sizeof(address);
  new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
  if (new_socket < 0) {
    throw std::runtime_error("Accept failed");
  }

  char buffer[1024] = {0};
  std::string message = "Server Message";

  read(new_socket, buffer, sizeof(buffer) - 1);
  std::cout << buffer << std::endl;

  send(new_socket, message.c_str(), message.length(), 0);
  std::cout << "Message sent" << std::endl;
}

// public methods.......................
Server_Socket::Server_Socket() {

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    throw std::runtime_error("Socket creation failed");
  }
}

bool Server_Socket::start() {

  try {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(SERVER_IP);
    address.sin_port = htons(PORT);

    LOG(INFO) << "Address Type:" << address.sin_family << std::endl;
    LOG(INFO) << "Host IP:" << SERVER_IP << std::endl;
    LOG(INFO) << "Host PORT:" << PORT << std::endl;

    setSocketOptions();
    bindSocket(address);
    listenForConnections();

    LOG(INFO) << "Server Listening..." << std::endl;

    acceptAndHandleClient(address);
    return 1;
  }

  catch (const std::exception &e) {
    handleError(e.what());
    return 0;
  }
}

bool Server_Socket::stop() {
  try {
    close(new_socket);
    LOG(INFO) << "Closing Server Socket" << std::endl;
    return 1;
  } catch (const std::exception &e) {
    return 0;
  }
}
