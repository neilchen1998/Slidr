#!/bin/bash

# Configure the repo
cmake -S . -B build -DBUILD_EXAMPLES=ON -DCMAKE_BUILD_TYPE=Release &&

# Build the repo
cmake --build build &&

# Run the app
./build/apps/app
