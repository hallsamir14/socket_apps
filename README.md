# BasicSocket

BasicSocket is a foundational client-server application implemented in C++ using socket programming. The `socket_base` branch serves as a base branch for more complex socket-based projects. It provides reusable and expandable server and client classes that can be used as building blocks for advanced networking applications.

![Alt text](image.png)

## Features

- **Client-Server Communication**: Establishes a connection between a client and a server using TCP sockets.
- **Message Exchange**: Allows the client to send messages to the server and receive responses.
- **Error Handling**: Includes basic error handling for socket operations.
- **Logging**: Integrates Google Logging Library (glog) for logging messages and errors.

## Project Structure

The project is organized into the following directories and files:

BasicSocket/ ├── client/ │ ├── client_main.cpp │ ├── client_socket.cpp │ └── client_socket.h ├── server/ │ ├── server_main.cpp │ ├── server_socket.cpp │ └── server_socket.h ├── .gitignore ├── Makefile └── README.md

