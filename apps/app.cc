#include <cstddef>
#include <iostream> // std::cerr
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
#include <vector>    // std::vector
#include <algorithm>    // std::ranges::equal
#include <chrono>   // std::chrono::high_resolution_clock, std::chrono::duration_cast

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

    std::cout << "duration: " << duration << "\t total iterations: " << totalIters << "\n";

    auto path = s.GetPath();
    for (size_t i = 0; i < path.size(); ++i)
    {
        std::cout << "Step " << i << ":\n";
        path[i].Print();
    }

    std::cout << "Moves: " << s.GetSolution() << std::endl;

    return EXIT_SUCCESS;
}
