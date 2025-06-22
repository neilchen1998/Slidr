#!/bin/bash

# configures the repo
cmake -S . -B build -DCMAKE_BUILD_TYPE=Bench &&

# builds the repo
cmake --build build &&

# runs the bench mark
./build/bench/mathbenchlib &&
./build/bench/nodebenchlib
