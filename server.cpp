#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>



using namespace std;

#define PORT 8080

int main(int argc, char* argv[])
{   
    //hold socket file descriptor for server - - - socket(domain,type,protocol):
    int server_fd = socket(AF_INET, SOCK_STREAM, 0); 
    //...
     
    struct sockaddr_in address;//stores address info for server (port and address)
    int opt = 1;//hold socket option value
    int bind_ret = 0;//hold returned value from bind function
    socklen_t addrlen = sizeof(address);//holds size of address struct
    //hold socket file descriptor for incoming clinet connection
    int new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
    //...
    char buffer[1024] = {0};//hold client data recieved
    //hold number of bytes
    ssize_t valread = read(new_socket, buffer, 1024 - 1);//reserve one character for null terminator
    string message = "Server Message";

    //Create socket file descriptor 
    if(server_fd<0){
        perror("Socket Failed");
        exit(0);
    }

    //Setsocket options
    if (setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR|SO_REUSEPORT, &opt, sizeof(opt))){
        perror("Setsocketopt");
        exit(0);
    }
    
    //store address info for server node
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //Bind function binds socket to address and port number to addr struct
    //- - - int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    bind_ret = bind(server_fd,(struct sockaddr*)&address,sizeof(address));

    if(bind_ret < 0){
        perror("bind failed");
        exit(0);
    }
    //Server node waits for incoming client connection
    //- - - int listen(int sockfd, int backlog);
    if(listen(server_fd, 3) < 0){
        perror("Server listening error");
        exit(0);
    }

    if (new_socket < 0){
        perror("Connection Refused");
        exit(0);
    }

    cout << buffer << endl;
    send(new_socket,message.c_str(),strlen(message.c_str()),0);
    cout << "Message sent" << endl;



}