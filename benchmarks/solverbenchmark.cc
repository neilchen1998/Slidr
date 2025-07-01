#include <vector>   // std::vector
#include <random>   // std::mt19937
#include <span> // std::span
#include <nanobench.h>  // ankerl::nanobench::Bench
#include <ranges>   // std::views::iota
#include <algorithm>   // std::shuffle
#include <chrono>   // std::chrono::steady_clock::now
#include <fstream>  // std::fstream

#include "constants/constantslib.hpp"
#include "node/nodelib.hpp"

#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
#include <vector>    // std::vector
#include <algorithm>    // std::ranges::equal
#include <optional> // std::optional
#include <chrono>   // std::chrono::high_resolution_clock, std::chrono::duration_cast
#include <fmt/core.h>   // fmt::print
#include <random>

#include "solver/solverlib.hpp" // Solver
#include "constants/constantslib.hpp"   // constants::EMPTY
#include "prompt/promptlib.hpp" // prompt::parse_string_to_layout

using BucketPQ = BucketQueue<std::shared_ptr<Node>, unsigned int, std::greater<Node>>;

int main()
{
    std::ofstream file("./build/benchmarks/solver-results.csv");
    ankerl::nanobench::Bench bench;

    auto bucket = BucketPQ(50);

    std::vector<int> layout0 {1, 7, constants::EMPTY, 8, 4, 3, 5, 2, 6};
    std::vector<int> layout1 {6, 3, 8, 2, 1, 7, constants::EMPTY, 5, 4};
    std::vector<int> layout2 {7, 4, 1, 5, 2, 3, 8, 6, constants::EMPTY};
    std::vector<int> layout3 {1, 2, 7, 4, constants::EMPTY, 5, 8, 3, 6};
    std::vector<int> layout4 {2, 3, 1, 4, constants::EMPTY, 8, 5, 7, 6};

    bench.minEpochIterations(10)
        .run("Priority Queue Solver", [&]
    {
        Solver(layout0).SolvePuzzle();
        Solver(layout1).SolvePuzzle();
        Solver(layout2).SolvePuzzle();
        Solver(layout3).SolvePuzzle();
        Solver(layout4).SolvePuzzle();
    });

    bench.minEpochIterations(10)
        .run("Bucket Queue Solver", [&]
    {
        Solver<BucketPQ>(layout0, bucket).SolvePuzzle();
        Solver<BucketPQ>(layout1, bucket).SolvePuzzle();
        Solver<BucketPQ>(layout2, bucket).SolvePuzzle();
        Solver<BucketPQ>(layout3, bucket).SolvePuzzle();
        Solver<BucketPQ>(layout4, bucket).SolvePuzzle();
    });

    // Render the results to a csv file
    bench.render(ankerl::nanobench::templates::csv(), file);
}
