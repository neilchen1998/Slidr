#include <vector>   // std::vector
#include <random>   // std::mt19937
#include <span> // std::span
#include <nanobench.h>  // ankerl::nanobench::Bench
#include <ranges>   // std::views::iota
#include <algorithm>   // std::shuffle
#include <chrono>   // std::chrono::steady_clock::now

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

using BucketPQ = BucketQueue<Node, unsigned int, std::greater<Node>>;

int main()
{
    auto bucket = BucketPQ(50);

    std::vector<int> layout0 {1, 7, constants::EMPTY, 8, 4, 3, 5, 2, 6};
    std::vector<int> layout1 {6, 3, 8, 2, 1, 7, constants::EMPTY, 5, 4};
    std::vector<int> layout2 {7, 4, 1, 5, 2, 3, 8, 6, constants::EMPTY};

    ankerl::nanobench::Bench()
        .minEpochIterations(30)    
        .run("Priority Queue Solver", [&]
    {
        Solver(layout0).SolvePuzzle();
        Solver(layout1).SolvePuzzle();
        Solver(layout2).SolvePuzzle();
    });

    ankerl::nanobench::Bench()
        .minEpochIterations(30)    
        .run("Bucket Queue Solver", [&]
    {
        Solver<BucketPQ>(layout0, bucket).SolvePuzzle();
        Solver<BucketPQ>(layout1, bucket).SolvePuzzle();
        Solver<BucketPQ>(layout2, bucket).SolvePuzzle();
    });
}