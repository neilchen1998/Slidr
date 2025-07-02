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
    {
        std::vector<int> layout {1, 7, constants::EMPTY, 8, 4, 3, 5, 2, 6};
        Solver s = Solver(layout);
        auto [isSolved, totalIters] = s.SolvePuzzle();

        fmt::print("# of iterations: {}\tTotal moves: {}\n", totalIters, s.GetNumOfMoves());
        s.PrintPath();

        fmt::print("Moves: {}\n", s.GetSolution());
    }
    return EXIT_SUCCESS;
}
