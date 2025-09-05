#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
#include <vector>    // std::vector
#include <algorithm>    // std::ranges::equal
#include <optional> // std::optional
#include <chrono>   // std::chrono::high_resolution_clock, std::chrono::duration_cast

#include <fmt/core.h>   // fmt::print

#include "slidr/solver/solverlib.hpp" // Solver
#include "slidr/constants/constantslib.hpp"   // constants::EMPTY
#include "slidr/prompt/promptlib.hpp" // prompt::parse_string_to_layout

int main(int argc, char* argv[])
{
    std::vector<int> layout0 {1, 7, constants::EMPTY, 8, 4, 3, 5, 2, 6};
    std::vector<int> layout1 {6, 3, 8, 2, 1, 7, constants::EMPTY, 5, 4};
    std::vector<int> layout2 {7, 4, 1, 5, 2, 3, 8, 6, constants::EMPTY};
    std::vector<int> layout3 {1, 2, 7, 4, constants::EMPTY, 5, 8, 3, 6};
    std::vector<int> layout4 {2, 3, 1, 4, constants::EMPTY, 8, 5, 7, 6};

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 100; ++i)
    {
        Solver(layout0).SolvePuzzle();
        Solver(layout1).SolvePuzzle();
        Solver(layout2).SolvePuzzle();
        Solver(layout3).SolvePuzzle();
        Solver(layout4).SolvePuzzle();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    fmt::print("Total time: {} ms\n", duration.count());

    return EXIT_SUCCESS;
}
