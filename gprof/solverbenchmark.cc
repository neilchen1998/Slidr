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

int main(int argc, char* argv[])
{
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 100; ++i)
    {
        {
            std::vector<int> layout {1, 7, constants::EMPTY, 8, 4, 3, 5, 2, 6};
            Solver s = Solver(layout);
            auto [isSolved, totalIters] = s.SolvePuzzle();
        }

        {
            std::vector<int> layout {6, 3, 8, 2, 1, 7, constants::EMPTY, 5, 4};
            Solver s = Solver(layout);
            auto [isSolved, totalIters] = s.SolvePuzzle();
        }

        {
            std::vector<int> layout {7, 4, 1, 5, 2, 3, 8, 6, constants::EMPTY};
            Solver s = Solver(layout);
            auto [isSolved, totalIters] = s.SolvePuzzle();
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    fmt::print("Total time: {} ms\n", duration.count());

    return EXIT_SUCCESS;
}
