# Socket Applications

Socket Applications is a foundational client-server application implemented in C++ using socket programming. The `socket_base` branch serves as a base branch for more complex socket-based projects. It provides reusable and expandable server and client classes that can be used as building blocks for advanced networking applications.

![Alt text](image.png)

## Features

- **Client-Server Communication**: Establishes a connection between a client and a server using TCP sockets.
- **Message Exchange**: Allows the client to send messages to the server and receive responses.
- **Error Handling**: Includes basic error handling for socket operations.
- **Logging**: Integrates Google Logging Library (glog) for logging messages and errors.

## Project Structure

The project is organized into the following directories and files:

    BasicSocket/ 
    ├── client/ 
    |    ├── client_main.cpp │ 
    |    ├── client_socket.cpp │ 
    |    └── client_socket.h 
    ├── server/ 
    |    ├── server_main.cpp │ 
    |    ├── server_socket.cpp │ 
    |    └── server_socket.h 
    ├── .gitignore 
    ├── Makefile 
    └── README.md


### Client

- **client_main.cpp**: The entry point for the client application. It creates a `Client_Socket` object, connects to the server, and sends a message.
- **client_socket.cpp**: Implements the `Client_Socket` class, which handles socket creation, connection to the server, and message sending.
- **client_socket.h**: Declares the `Client_Socket` class and its methods.

### Server

- **server_main.cpp**: The entry point for the server application. It creates a `Server_Socket` object and starts the server.
- **server_socket.cpp**: Implements the `Server_Socket` class, which handles socket creation, binding, listening for connections, and handling client messages.
- **server_socket.h**: Declares the `Server_Socket` class and its methods.

## Build Source

To build the client and server modules, use the provided `Makefile`:
```
make
```

Start Server:
```
./server/server.bin
```

Start Client:
```
./client/client.bin
```

Cleanup Binaries:
```
make clean
```
