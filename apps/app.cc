#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
#include <vector>    // std::vector
#include <algorithm>    // std::ranges::equal
#include <chrono>   // std::chrono::high_resolution_clock, std::chrono::duration_cast
#include <fmt/core.h>   // fmt::print

#include "constants/constantslib.hpp"
#include "solver/solverlib.hpp"

int main(int argc, char* argv[])
{

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> layout {5, 3, 6, 2, constants::EMPTY, 8, 4, 1, 7};

    Solver s = Solver(layout);
    auto [isSolved, totalIters] = s.SolvePuzzle();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    fmt::print("duration: {} µs\t # of iterations: {}\n", duration.count(), totalIters);
    s.PrintPath();

    fmt::print("Moves: {}\n", s.GetSolution());

    return EXIT_SUCCESS;
}
