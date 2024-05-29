#!/bin/bash

# configures the repo
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

# builds the repo
cmake --build build

# runs the binary
./build/apps/app