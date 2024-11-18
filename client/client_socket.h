// client_socket.h

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <string>
#include <arpa/inet.h>

class Client_Socket {
    private:
        void handleError(const std::string& errorMessage);
        int createSocket();
    public:
        Client_Socket();
        void connectToServer(int client_fd, const struct sockaddr_in& server_addr);
        void sendMessage(int client_fd);
};

#endif // CLIENT_SOCKET_H