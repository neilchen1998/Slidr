#!/bin/bash

# Configure the repo
cmake -S . -B build -DCMAKE_BUILD_TYPE=gprof &&

# Build the repo
cmake --build build &&

# Run the app
./build/apps/app &&

# Run Gprof and generate a report
gprof ./build/apps/app gmon.out > ./build/apps/analysis.txt

# Remove gmon.out
rm gmon.out
