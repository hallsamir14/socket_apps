#include "server_socket.h"
#include <arpa/inet.h>
#include <glog/logging.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 8080
#define SERVER_IP "127.0.0.2"
#define BUFFER_SIZE 1024

// private methods..............
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
  server_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen);
  if (server_socket < 0) {
    throw std::runtime_error("Accept failed");
  }

  char buffer[1024] = {0};
  std::string message = "Server Message";

  read(server_socket, buffer, sizeof(buffer) - 1);
  LOG(INFO) << "[Inbound Message]:" << buffer << std::endl;

  send(server_socket, message.c_str(), message.length(), 0);
  LOG(INFO) << "[Outbound Message]:"
            << "Message:" << message << std::endl;
}

// public methods.......................
Server_Socket::Server_Socket() {

  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  status = 0;
  if (server_fd < 0) {
    throw std::runtime_error("Socket creation failed");
  }
}

bool Server_Socket::start() {

  if (status == 0) {
    LOG(INFO) << "Starting Server Socket" << std::endl;
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

    status = 1;

    acceptAndHandleClient(address);

    return 1;
  }

  else if (status == 1) {
    LOG(INFO) << "Server Socket Is Already Active" << std::endl;
  }

  return 0;
}

bool Server_Socket::stop() {
  if (status == 1) {
    close(server_socket);
    LOG(INFO) << "Closing Server Socket" << std::endl;
    return 1;
  }

  else if (status == 0) {
    LOG(INFO) << "Socket Is Not Active" << std::endl;
  }

  return 0;
}

bool Server_Socket::get_status() { return status; }
