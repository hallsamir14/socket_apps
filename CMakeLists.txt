cmake_minimum_required(VERSION 3.10)

# Project name
project(BasicSocket)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/client)
include_directories(${PROJECT_SOURCE_DIR}/server)

# Source files
set(CLIENT_SRC
    ${PROJECT_SOURCE_DIR}/client/client_main.cpp
    ${PROJECT_SOURCE_DIR}/client/client_socket.cpp
)

set(SERVER_SRC
    ${PROJECT_SOURCE_DIR}/server/server_main.cpp
    ${PROJECT_SOURCE_DIR}/server/server_socket.cpp
)

# Output binaries
set(CLIENT_BIN ${PROJECT_SOURCE_DIR}/client/client.bin)
set(SERVER_BIN ${PROJECT_SOURCE_DIR}/server/server.bin)

# Find glog
find_package(glog REQUIRED)

# Client executable
add_executable(client ${CLIENT_SRC})
target_link_libraries(client glog::glog)

# Server executable
add_executable(server ${SERVER_SRC})
target_link_libraries(server glog::glog)

# Output binary names
set_target_properties(client PROPERTIES OUTPUT_NAME "client.bin")
set_target_properties(server PROPERTIES OUTPUT_NAME "server.bin")

# Custom target for cleaning build files
add_custom_target(clean
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/cmake_clean.cmake
)

# Create a script to clean build files
file(WRITE ${CMAKE_BINARY_DIR}/cmake_clean.cmake
"file(REMOVE_RECURSE ${CLIENT_BIN} ${SERVER_BIN})\n"
)