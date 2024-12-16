CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Directories
CLIENT_DIR = client
SERVER_DIR = server

# Source files
CLIENT_SRC = $(CLIENT_DIR)/client_main.cpp $(CLIENT_DIR)/client_socket.cpp
SERVER_SRC = $(SERVER_DIR)/server_main.cpp $(SERVER_DIR)/server_socket.cpp

# Output binaries
CLIENT_BIN = client/client.bin
SERVER_BIN = server/server.bin

# Libraries
LIBS = -lglog

# Build all
all: $(CLIENT_BIN) $(SERVER_BIN)

# Build client
$(CLIENT_BIN): $(CLIENT_SRC)
	$(CXX) $(CXXFLAGS) -o $(CLIENT_BIN) $(CLIENT_SRC) $(LIBS)

# Build server
$(SERVER_BIN): $(SERVER_SRC)
	$(CXX) $(CXXFLAGS) -o $(SERVER_BIN) $(SERVER_SRC) $(LIBS)

# Clean build files
clean:
	rm -f $(CLIENT_BIN) $(SERVER_BIN)

.PHONY: all clean