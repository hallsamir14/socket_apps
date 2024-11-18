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

//private methods
void Client_Socket::handleError(const std::string& errorMessage) {
    perror(errorMessage.c_str());
    exit(EXIT_FAILURE);
}

int Client_Socket::createSocket() {
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        handleError("Socket creation error");
    }
    return client_fd;
}


//public methods
//todo_0 - - - what data should constructor set/define?
//todo_1 - - - what data should be passed/globally declard within class

Client_Socket::Client_Socket() {

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        handleError("Invalid address/ Address not supported");
    }


}

void Client_Socket::connectToServer(int client_fd, const struct sockaddr_in& server_addr) {
    if (connect(client_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        handleError("Connection failed");
    }
}

void Client_Socket::sendMessage(int client_fd){
    std::string message = "Client Message";
    char buffer[BUFFER_SIZE] = {0};

    send(client_fd, message.c_str(), message.length(), 0);
    int valread = read(client_fd, buffer, BUFFER_SIZE);
    if (valread < 0) {
        handleError("Read error");
    }
    std::cout << "Server: " << buffer << std::endl;
}
