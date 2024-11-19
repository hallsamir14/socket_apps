// client_socket.h

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

#include <string>
#include <arpa/inet.h>

class Client_Socket {
    private:
        int client_fd;
        void handleError(const std::string& errorMessage);
        int createSocket();
    public:
        Client_Socket();
        void connectToServer();
        void sendMessage();
};

#endif // CLIENT_SOCKET_H