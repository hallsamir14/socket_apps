#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <iostream>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>



using namespace std;

#define PORT 8080

int main(int argc, char* argv[])
{   
    int server_fd = 0; //hold socket file descriptor for server
    int new_socket = 0;//hold socket file descriptor for incoming clinet connection
    ssize_t valread;//hold number of bytes 
    struct sockaddr_in address;//stores address info for server (port and address)
    int opt1 = 1;//
    socklen_t addrlen = sizeof(address);//holds size of address struct
    char buffer[1024] = {0};//hold client data recieved
    string message = "Server Message";

    //Create socket file descriptor
    if((server_fd=socket(AF_INET, SOCK_STREAM, 0))<0){
        perror("Socket Failed");
        exit(0);
    }

    

}