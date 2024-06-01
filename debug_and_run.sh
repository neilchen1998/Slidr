#!/bin/bash

# configures the repo
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug &&

# builds the repo
cmake --build build &&

# runs the binary
echo "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 x" | ./build/apps/app