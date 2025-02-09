#!/bin/bash

# Update package list and install required packages
sudo apt-get update

#Install clang formatter
sudo apt-get install clang-format

# Install build-essential for compiling C++ programs
sudo apt-get install -y build-essential

# Install CMake
sudo apt-get install -y cmake

# Install Google Logging Library (glog)
sudo apt-get install -y libgoogle-glog-dev

# Verify installation
echo "Installed packages:"
dpkg -l | grep -E 'build-essential|cmake|libgoogle-glog-dev'

echo "Setup complete. You can now build the project using CMake."