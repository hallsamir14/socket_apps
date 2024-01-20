#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>

using namespace std;
#define PORT 8080

int main (int argc, char* argv[]){
    //hold socket file descriptor for client - - - socket(domain,type,protocol):
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
    //..
    int valread;
    struct sockaddr_in server_addr;
    string message = "Client Message";
    char buffer[1024];

    if (client_fd <= 0){
        perror("Socket Creation error");
        exit(0);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    //Convert IP to binary
    //int inet_pton(int af, const char *restrict src, void *restrict dst);
    int conv_IP = inet_pton(AF_INET,"127.0.0.2", &server_addr.sin_addr);
    if (conv_IP <= 0){
        cout << "Invalid Address" << endl;
        exit(0);
    }
    
    int status = connect(client_fd, (struct sockaddr*)&server_addr,sizeof(server_addr));//hold status value for client
    //cout << (struct sockaddr*)&server_addr;
    if (status < 0){
        cout << "Connection Falied" << endl;
        exit(0);
    }

    send(client_fd,message.c_str(),strlen(message.c_str()),0);
    cout << "Message Sent" << endl;
    valread = read(client_fd, buffer,1024-1);
    cout << buffer << endl;

    //close socket
    close (client_fd);
    return 0;


}