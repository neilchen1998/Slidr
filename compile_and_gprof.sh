#!/bin/bash

if [[ "$OSTYPE" != "linux-gnu"* ]]; then
    echo "Gprof requires linux OS"
    exit 1
else
    echo "Gprof can run on this machine"
fi

# Configure the repo
cmake -S . -B build -DCMAKE_BUILD_TYPE=Gprof &&

# Build the repo
cmake --build build &&

# Run the app
./build/gprof/solverbenchmark &&

# Run Gprof and generate a report
gprof ./build/gprof/solverbenchmark gmon.out | gprof2dot | dot -Tpng -Gdpi=150 -o output.png &&

# Remove gmon.out
rm gmon.out
