#include <iostream> // std::cerr
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE

#include <cstdlib>  // std::size_t
#include <vector>   // std::vector
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

        auto [isSolved, iterations] = s.SolvePuzzle();

        if (isSolved)
        {
            std::cout << "Solution found! Took " << iterations << " iteration(s)\n";
        }
        else
        {
            std::cout << "No solution was found. The given puzzle have odd number of inversions.\n";
        }

        auto solution = s.GetSolution();

        std::cout << "Start:\n";
        n.Print();
        std::cout << "*****\n";

        // only show the solution is the puzzle was solved
        if (isSolved)
        {
            int i = 1;
            for (const auto& sol : solution | std::views::drop(1))  // drop the start state
            {
                std::cout << "Step " << i << ":\n";
                sol.Print();
                std::cout << "*****\n";

                ++i;
            }
        }
    }

    {
        // the 15 puzzle problem
        std::cout << "=== 15 Puzzle Problem ===\n";
        std::vector<int> initialState {10, 13, 5, 4, 6, constants::EMPTY, 15, 14, 3, 11, 9, 8, 7, 1, 12, 2};
        Node<constants::FIFTEEN_PUZZLE_SIZE> n(initialState);
        Solver<constants::FIFTEEN_PUZZLE_SIZE> s = Solver(n);

        auto [isSolved, iterations] = s.SolvePuzzle();
        auto solution = s.GetSolution();

        if (isSolved)
        {
            std::cout << "Solution found! Took " << iterations << " iteration(s)\n";
        }
        else
        {
            std::cout << "No solution was found. The given puzzle have odd number of inversions.\n";
        }

        std::cout << "Start:\n";
        n.Print();
        std::cout << "************\n";

        // only show the solution is the puzzle was solved
        if (isSolved)
        {
            int i = 1;
            for (const auto& sol : solution | std::views::drop(1))  // drop the start state
            {
                std::cout << "Step " << i << ":\n";
                sol.Print();
                std::cout << "************\n";

                ++i;
            }
        }
    }

    return EXIT_SUCCESS;
}
