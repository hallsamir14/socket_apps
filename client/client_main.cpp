#include "client_socket.cpp"

//Driver code for client socket

int main(int argc, char* argv[]) {
    Client_Socket client = Client_Socket();
    client.connectToServer();
    client.sendMessage();
    return 0;
}