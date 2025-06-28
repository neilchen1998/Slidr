# 8 Puzzle Problem

This project solves the famous 8 Puzzle problem.

## Summary

8 Puzzle problem is a simple version of [15 Puzzle problem](https://en.wikipedia.org/wiki/15_puzzle).
In this project, [A* algorithm](http://theory.stanford.edu/~amitp/GameProgramming/AStarComparison.html) is used to solve the problem.
Each time through the main loop, A* examines the state $n$ sucht that it has the lowest value of $f(n) = g(n) + h(n)$.
$g(n)$ is the actual cost (in this case, the number of moves) of a state from the starting state.
$h(n)$ is the heuristic cost of a state to the goal, [Manhattan Distance](https://xlinux.nist.gov/dads/HTML/manhattanDistance.html) is used in this project. Then it will explore all possible movements (left, right, up, down),
and keep on until it reaches the goal.

## Requirements

The requirements are:

- CMake 3.11 or better; 3.14+ highly recommended
- A C++20 compatible compiler ([gcc](https://gcc.gnu.org/) or [llvm](https://llvm.org/))
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

To run the binary with example layout:

```bash
./build/apps/app
```

To run the binary with a custom puzzle layout (use 1 to 8 and 'x' or 'X' for the empty space):

```bash
./build/apps/app <puzzle>
```

To build and test:

```bash
cmake --build build && cmake --build build --target test
```

To build docs (requires Doxygen, output in `build/docs/html`):

```bash
cmake --build build --target docs
```

To build and run benchmark:

```bash
cmake --build build && ./build/bench/<name_of_benchmark>
```

To run the Unix performance analysis tool (tested only on Linux):

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=gprof && ./build/apps/app && gprof ./build/apps/app gmon.out > ./build/apps/analysis.txt
```

## Example Result

This is the default puzzle and its output:

<table>
  <tr>
    <td>5</td>
    <td>3</td>
    <td>6</td>
  </tr>
  <tr>
    <td>2</td>
    <td></td>
    <td>8</td>
  </tr>
  <tr>
    <td>4</td>
    <td>1</td>
    <td>7</td>
  </tr>
</table>

```
No additional argument is provided! An example puzzle layout will be used.
Done in: 67 µs  # of iterations: 65     Total moves: 14
Step: 0
5 3 6
2 x 8
4 1 7
Step: 1
5 3 6
2 1 8
4 x 7
Step: 2
5 3 6
2 1 8
4 7 x
Step: 3
5 3 6
2 1 x
4 7 8
Step: 4
5 3 x
2 1 6
4 7 8
Step: 5
5 x 3
2 1 6
4 7 8
Step: 6
5 1 3
2 x 6
4 7 8
Step: 7
5 1 3
x 2 6
4 7 8
Step: 8
x 1 3
5 2 6
4 7 8
Step: 9
1 x 3
5 2 6
4 7 8
Step: 10
1 2 3
5 x 6
4 7 8
Step: 11
1 2 3
x 5 6
4 7 8
Step: 12
1 2 3
4 5 6
x 7 8
Step: 13
1 2 3
4 5 6
7 x 8
Step: 14
1 2 3
4 5 6
7 8 x
Moves: ↑←↓↓→↑→↓←↑→↑←←
```

## Notes

### Hash Algorithm

A simple way to hash two values is using `boost::hash_combine` from the [Boost library](https://www.boost.org/).
Or as this [post](https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x) suggests, use the following:

```cpp
template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> h;
    seed ^= h(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    // seed ^= (std::hash<T>{}(u) << 1); // this MIGHT get the job done, it passess all the test cases
}
```

There is no significant performance difference between two approaches according to the benchmark that can be found in `bench/mathbenchlib`.
The archeive file size when using `boost::hash_combine` and that when using `hash_combine` are identical.

An even more simplified version as shown in the comment *MIGHT* work.
It passes all the test cases in the repo.
But it is not advised.

| benchmark       | op/s | ns/op |
| :-----------| :------------ | ----: |
| hash_vector | 74,615,800.46 | 13.40 |
| hash_range  | 90,301,886.39 | 11.07 |

### `const std::vector<T>& vec` vs. `std::span<T> s`

According to the benchmark `bench/mathbenchlib` powered by [nanobench](https://github.com/martinus/nanobench) and [Quick C++ Benchmark](https://quick-bench.com/),
there is no significant performance difference
between hashing a `const std::vector<T>& vec` and `std::span<T> s`.
The overhead of converting a `std::vector<T> vec` to `std::span<T> s` is minimal.
Since this project uses C++20, this is the way to go.

### Manhattan Distance Calculation

[Manhattan Distance](https://xlinux.nist.gov/dads/HTML/manhattanDistance.html) is used to calculate the heuristic value of a puzzle in a given state.

In our problem, $p_1$ represents the goal position and $p_2$ represents the current position of a piece of the puzzle and the formula is
$|x_1 - x_2| + |y_1 - y_2|$, where $x$ denotes the row position and $y$ denotes the column position.

There are three implementations, using a simple for-loop, using `std::accumulate`, and using `std::reduce`:

```cpp
int GetManhattanDistance(std::span<int> s)
{
    int manhattanDistance = 0;
    for (auto i = 0; i < constants::EIGHT_PUZZLE_NUM; ++i)
    {
        if (s[i] != constants::EMPTY)
        {
            int curRow = (s[i] - 1) / constants::EIGHT_PUZZLE_SIZE;
            int curCol = (s[i] - 1) % constants::EIGHT_PUZZLE_SIZE;

            int goalRow = i / constants::EIGHT_PUZZLE_SIZE;
            int goalCol = i % constants::EIGHT_PUZZLE_SIZE;

            manhattanDistance += (std::abs(goalRow - curRow) + std::abs(goalCol - curCol));
        }
    }

    return manhattanDistance;
}
```

```cpp
int GetManhattanDistanceAccumulate(std::span<int> s)
{
    auto v = std::views::iota(0, constants::EIGHT_PUZZLE_NUM);
    return std::accumulate(
        v.begin(),
        v.end(),
        0,
        [&](int acc, int i) {
            if (s[i] == constants::EMPTY)
            return acc;

            int curRow = (s[i] - 1) / constants::EIGHT_PUZZLE_SIZE;
            int curCol = (s[i] - 1) % constants::EIGHT_PUZZLE_SIZE;
            int goalRow = i / constants::EIGHT_PUZZLE_SIZE;
            int goalCol = i % constants::EIGHT_PUZZLE_SIZE;

            return acc + std::abs(goalRow - curRow) + std::abs(goalCol - curCol);
        }
    );
}
```

```cpp
int GetManhattanDistanceReduce(std::span<int> s)
{
    auto v = std::views::iota(0, constants::EIGHT_PUZZLE_NUM);
    return std::reduce(
        v.begin(),
        v.end(),
        0,
        [&](int acc, int i) {
            if (s[i] == constants::EMPTY)
                return acc;

            int curRow = (s[i] - 1) / constants::EIGHT_PUZZLE_SIZE;
            int curCol = (s[i] - 1) % constants::EIGHT_PUZZLE_SIZE;
            int goalRow = i / constants::EIGHT_PUZZLE_SIZE;
            int goalCol = i % constants::EIGHT_PUZZLE_SIZE;

            return acc + std::abs(goalRow - curRow) + std::abs(goalCol - curCol);
        }
    );
}
```

`std::reduce` utilizes parallelism which in theory be faster than `std::accumulate`.
In our case the order of the operations does not matter, therefore we can use `std::reduce`.
Nonetheless, based on the benchmark, the three different approaches do not have discernable difference in terms of speed.

| benchmark       | op/s | ns/op |
| :---------------| :------------- | ---: |
| for loop        | 160,295,728.06 | 6.24 |
| std::accumulate | 156,853,151.47 | 6.38 |
| std::reduce     | 157,072,439.95 | 6.37 |

## Reference
