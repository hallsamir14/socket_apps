#include "client_socket.cpp"

//Driver code for client socket

int main(int argc, char* argv[]) {
    Client_Node client = Client_Socket();
    int client_fd = 0;
    client.connectToServer(client_fd);


    return 0;
}