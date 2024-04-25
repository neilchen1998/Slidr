#include <iostream> // std::cerr
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE

#include <cstdlib>  // std::size_t
#include <array>    // std::array
#include <vector>   // std::vector
#include <unordered_set>    // std::unordered_set
#include <unordered_map>    // std::unordered_map
#include <queue>    // std::priority_queue
#include <tuple>    // std::tuple
#include <ranges>    // std::ranges

#include "constants/constantslib.hpp"
#include "math/mathlib.hpp"
#include "node/nodelib.hpp"
#include "solver/solverlib.hpp"

int main(int argc, char* argv[])
{
    {
        // the 8 puzzle problem
        std::cout << "=== 8 Puzzle Problem ===\n";
        std::vector<int> state {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
        Node<constants::EIGHT_PUZZLE_SIZE> n(state);
        Solver<constants::EIGHT_PUZZLE_SIZE> s = Solver(n);

        s.SolvePuzzle();
        auto solution = s.GetSolution();

        std::cout << "Start:\n";
        n.Print();
        std::cout << "*****\n";

        int i = 1;
        for (const auto& sol : solution | std::views::drop(1))
        {
            std::cout << "Step " << i << ":\n";
            sol.Print();
            std::cout << "*****\n";

            ++i;
        }
    }

    {
        // the 15 puzzle problem
        std::cout << "=== 15 Puzzle Problem ===\n";
        std::vector<int> state {2, 6, 1, 11, 12, 13, constants::EMPTY, 8, 3, 14, 15, 10, 4, 5, 7, 9};
        Node<constants::FIFTEEN_PUZZLE_SIZE> n(state);
        Solver<constants::FIFTEEN_PUZZLE_SIZE> s = Solver(n);

        s.SolvePuzzle();
        auto solution = s.GetSolution();

        std::cout << "Start:\n";
        n.Print();
        std::cout << "************\n";

        int i = 1;
        for (const auto& sol : solution | std::views::drop(1))
        {
            std::cout << "Step " << i << ":\n";
            sol.Print();
            std::cout << "************\n";

            ++i;
        }
    }

    return EXIT_SUCCESS;
}
