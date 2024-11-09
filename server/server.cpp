#include <iostream>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

void handleError(const std::string& errorMessage) {
    perror(errorMessage.c_str());
    exit(EXIT_FAILURE);
}

int initializeServerSocket() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        handleError("Socket creation failed");
    }
    return server_fd;
}

void setSocketOptions(int server_fd) {
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        handleError("Set socket options failed");
    }
}

void bindSocket(int server_fd, struct sockaddr_in& address) {
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        handleError("Bind failed");
    }
}

void listenForConnections(int server_fd) {
    if (listen(server_fd, 3) < 0) {
        handleError("Listen failed");
    }
}

void acceptAndHandleClient(int server_fd, struct sockaddr_in& address) {
    socklen_t addrlen = sizeof(address);
    int new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    if (new_socket < 0) {
        handleError("Accept failed");
    }

    char buffer[1024] = {0};
    std::string message = "Server Message";

    read(new_socket, buffer, sizeof(buffer) - 1);
    std::cout << buffer << std::endl;

    send(new_socket, message.c_str(), message.length(), 0);
    std::cout << "Message sent" << std::endl;

    close(new_socket);
}

int main() {
    int server_fd = initializeServerSocket();

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.2");
    address.sin_port = htons(PORT);

    setSocketOptions(server_fd);
    bindSocket(server_fd, address);
    listenForConnections(server_fd);

    acceptAndHandleClient(server_fd, address);

    close(server_fd);
    return 0;
}