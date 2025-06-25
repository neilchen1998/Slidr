#!/bin/bash

# configures the repo
cmake -S . -B build -DCMAKE_BUILD_TYPE=gprof &&

# builds the repo
cmake --build build &&

./build/apps/app
