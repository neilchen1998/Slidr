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
    // Check if there is an additional argument (the total # of arguments should be 2)
    if (argc > 2)
    {
        fmt::print("Provide the puzzle!\nThe puzzle should only contains numbers from 1 to 8 and use 'x' or 'X' to denote the empty piece.\n");
        return EXIT_FAILURE;
    }

    // Check if an additional input is provided
    // otherwise an example input is used
    std::vector<int> layout;
    if (argc == 2)
    {
        auto res = prompt::parse_string_to_layout(argv[1]);
        if (!res)
        {
            fmt::print("Provide the puzzle!\nThe puzzle should only contains numbers from 1 to 8 and use 'x' or 'X' to denote the empty piece.\n");
            return EXIT_FAILURE;
        }

        layout = res.value();
    }
    else
    {
        fmt::print("No additional argument is provided! An example puzzle layout will be used.\n");
        layout = {5, 3, 6, 2, constants::EMPTY, 8, 4, 1, 7};
    }

    auto start = std::chrono::high_resolution_clock::now();
    Solver s = Solver(layout);
    auto [isSolved, totalIters] = s.SolvePuzzle();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    fmt::print("Done in: {} µs\t# of iterations: {}\tTotal moves: {}\n", duration.count(), totalIters, s.GetNumOfMoves());
    s.PrintPath();

    fmt::print("Moves: {}\n", s.GetSolution());

    return EXIT_SUCCESS;
}
