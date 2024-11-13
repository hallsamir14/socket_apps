#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define SERVER_IP "127.0.0.2"
#define BUFFER_SIZE 1024

void handleError(const std::string& errorMessage) {
    perror(errorMessage.c_str());
    exit(EXIT_FAILURE);
}

int createSocket() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        handleError("Socket creation error");
    }
    return client_fd;
}

void connectToServer(int client_fd, const struct sockaddr_in& server_addr) {
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        handleError("Connection failed");
    }
}

void sendMessage(int client_fd) {
    std::string message = "Client Message";
    char buffer[BUFFER_SIZE] = {0};

    send(client_fd, message.c_str(), message.length(), 0);
    int valread = read(client_fd, buffer, BUFFER_SIZE);
    if (valread < 0) {
        handleError("Read error");
    }
    std::cout << "Server: " << buffer << std::endl;
}

int main(int argc, char* argv[]) {
    int client_fd = createSocket();

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        handleError("Invalid address/ Address not supported");
    }

    connectToServer(client_fd, server_addr);
    sendMessage(client_fd);

    close(client_fd);
    return 0;
}