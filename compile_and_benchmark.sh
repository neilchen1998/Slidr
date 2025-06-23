#!/bin/bash

# configures the repo
cmake -S . -B build -DCMAKE_BUILD_TYPE=Benchmark &&

# builds the repo
cmake --build build &&

# runs the benchmark
./build/benchmarks/mathbenchmarklib &&
./build/benchmarks/nodebenchmarklib
