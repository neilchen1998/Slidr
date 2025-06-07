#include <cstddef>
#include <iostream> // std::cerr
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE

#include <vector>    // std::vector
#include <algorithm>    // std::ranges::equal
#include <chrono>   // std::chrono::high_resolution_clock, std::chrono::duration_cast
#include <random>

#include "constants/constantslib.hpp"
#include "solver/solverlib.hpp"

int main(int argc, char* argv[])
{
    unsigned int seed = 41;
    std::default_random_engine rng(seed);

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> layout {3, 1, 8, 6, 5, 2, 4, 7, constants::EMPTY};

    Solver s = Solver(layout);
    auto [isSolved, totalSteps] = s.SolvePuzzle();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "duration: " << duration / 100 << "\n";

    auto path = s.GetPath();
    for (size_t i = 0; i < path.size(); ++i)
    {
        std::cout << "Step " << i << ":\n";
        path[i].Print();
    }

    return EXIT_SUCCESS;
}
