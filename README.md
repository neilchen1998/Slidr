# 8 Puzzle Problem

This project solves the famous 8 Puzzle problem.

## Summary

## Requirements

The requirements are:

- CMake 3.11 or better; 3.14+ highly recommended
- A C++17 compatible compiler
- The Boost libararies
- Git
- Doxygen (optional, highly recommended)

## Instructions

To configure:

```bash
cmake -S . -B build
```

Add `-GNinja` if you have Ninja.

To build:

```bash
cmake --build build
```

To test (`--target` can be written as `-t` in CMake 3.15+):

```bash
cmake --build build --target test
```

To run exe
```
./build/apps/app
```

To build and run exe
```
cmake --build build && ./build/apps/app
```

To build and test
```
cmake --build build && cmake --build build --target test
```

To build docs (requires Doxygen, output in `build/docs/html`):

```bash
cmake --build build --target docs
```

## Note

### `const std::vector<T>& vec` vs. `std::span<T> s`

According to [Quick C++ Benchmark](https://quick-bench.com/), there is no significant performance difference 
between hashing a `const std::vector<T>& vec` and `std::span<T> s`.
The overhead of converting a `std::vector<T> vec` to `std::span<T> s` is minimal.
Since this project uses C++20, this is the way to go.
