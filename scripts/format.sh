#!/bin/bash

#for format consistency across all designated src files

# using 'apt-get install clang-format' to install on debian
if [ $# -eq 0 ]; then
    echo "Formatting all source files"
    find . -name "*.cpp" -exec clang-format -i {} \;
    find . -name "*.h" -exec clang-format -i {} \;
else 
    for arg in "$@"; do
        clang-format -i "$arg"
        echo "Formatting file $arg"
    done
    fi
