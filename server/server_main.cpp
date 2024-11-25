#include "server_socket.cpp"
#include <iostream>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(){

    Server_Socket server = Server_Socket();

    server.start();

    return 0;


}