#include <iostream> // std::cerr
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE

#include <cstdlib>  // std::size_t
#include <vector>   // std::vector
#include <queue>    // std::priority_queue
#include <tuple>    // std::tuple
#include <ranges>    // std::ranges
#include <random>   // std::random_device, std::mt19937, std::uniform_int_distribution

#include "constants/constantslib.hpp"
#include "math/mathlib.hpp"
#include "pattern/patternlib.hpp"
#include "node/nodelib.hpp"
#include "solver/solverlib.hpp"

const std::vector<int> FIFTEEN_GOAL_STATE {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, constants::EMPTY};

template <int GridSize>
struct Tester : Node<GridSize>
{
    std::vector<int> GetState() const { return this->state; }

    int GetPosX() const { return this->posX; }
};

void SolveEightPuzzleProblem()
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
    std::cout << "************" << std::endl;

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

void SolveFifteenPuzzleProblem(const std::vector<int>& initialState, const std::string& filename = "/home/neil_poseidon/C++/8-Puzzle/fifteen-puzzle-patterns.txt", bool write = false)
{
    // the 15 puzzle problem
    std::cout << "=== 15 Puzzle Problem ===\n";
    Node<constants::FIFTEEN_PUZZLE_SIZE> n(initialState);
    Solver<constants::FIFTEEN_PUZZLE_SIZE> s = Solver(n);

    std::cout << "Hash: " << n.GetHashValue() << "\n";

    auto [isSolved, iterations] = s.SolvePuzzle();
    auto solution = s.GetSolution();

    if (isSolved)
    {
        std::cout << "Solution found! Took " << iterations << " iteration(s)\n";
        std::cout << "Depth: " << s.GetDepth() << std::endl;
    }
    else
    {
        std::cout << "No solution was found. The given puzzle have odd number of inversions.\n";
    }

    std::cout << "Start:\n";
    n.Print();
    std::cout << "************" << std::endl;

    // only show the solution is the puzzle was solved
    if (isSolved)
    {
        // int i = 1;
        // for (const auto& sol : solution | std::views::drop(1))  // drop the start state
        // {
        //     std::cout << "Step " << i << ":\n";
        //     sol.Print();
        //     std::cout << "************\n";

        //     ++i;
        // }

        std::cout << "Move sequence:\n";
        std::vector<int> sequence {s.GetSequence()};
        if (write)
        {
            pattern::ExportSolution(n.GetHashValue(), sequence, filename);
        }
        int cnt = 1;
        for (const auto& seq : sequence)
        {
            std::cout << seq;
            if (cnt % 5 == 0)
            {
                std::cout << "\n";
            }

            ++cnt;
        }
        std::cout << "\n";
    }
}

void GeneratePatternsForFifteenPuzzleProblem(int low, int high, const std::string& filename = "/home/neil_poseidon/C++/8-Puzzle/fifteen-puzzle-patterns.txt")
{
    // auto generating patterns
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(low, high);
    const int N = distrib(gen);

    Node<constants::FIFTEEN_PUZZLE_SIZE> cur = FIFTEEN_GOAL_STATE;
    int i = 0;
    while (i < N)
    {
        std::vector<int> ava = cur.AvailableMoves();
        std::uniform_int_distribution<> distrib(0, ava.size() - 1);
        auto [state, posX] = cur.GetNextState(ava[distrib(gen)]);
        cur = Node<constants::FIFTEEN_PUZZLE_SIZE>(state, posX, i);
        ++i;
    }

    std::cout << "Result (" << N << "):\n";
    cur.Print();
    std::cout << std::flush;

    Solver<constants::FIFTEEN_PUZZLE_SIZE> s = Solver(cur);

    auto [isSolved, iterations] = s.SolvePuzzleWithPatterns(filename);

    if (isSolved)
    {
        std::cout << "Actual steps: " << s.GetDepth() << std::endl;
        std::vector<int> sequence = s.GetSequence();
        pattern::ExportSolution(cur.GetHashValue(), sequence, filename);
    }
}

void SolveFifteenPuzzleProblemsWithPattern(const std::vector<int>& initialState, const std::string& filename = "/home/neil_poseidon/C++/8-Puzzle/fifteen-puzzle-patterns.txt", bool write = false)
{
    // the 15 puzzle problem
    std::cout << "=== 15 Puzzle Problem (With Pattern) ===\n";
    Node<constants::FIFTEEN_PUZZLE_SIZE> n(initialState);
    Solver<constants::FIFTEEN_PUZZLE_SIZE> s = Solver(n);

    std::cout << "Hash: " << n.GetHashValue() << "\n";

    auto [isSolved, iterations] = s.SolvePuzzleWithPatterns(filename);
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
    std::cout << "************" << std::endl;

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
        std::cout << "Move sequence:\n";
        std::vector<int> sequence = s.GetSequence();
        if (write)
        {
            pattern::ExportSolution(n.GetHashValue(), sequence, filename);
        }
        int cnt = 1;
        for (const auto& seq : sequence)
        {
            std::cout << seq;
            if (cnt % 5 == 0)
            {
                std::cout << "\n";
            }

            ++cnt;
        }
        std::cout << "\n";
    }
}

const std::string filename("/home/neil_poseidon/C++/8-Puzzle/training-patterns");

int main(int argc, char* argv[])
{
    // GeneratePatternsForFifteenPuzzleProblem(200, 1200, filename);
    SolveFifteenPuzzleProblem({7, 2, 9, 6, 8, constants::EMPTY, 3, 13, 4, 1, 10, 5, 14, 15, 11, 12});
    // SolveFifteenPuzzleProblem({12, 11, 2, 15, 4, 1, 14, 3, 9, 6, 13, 7, 10, constants::EMPTY, 8, 5}, filename);
    // SolveFifteenPuzzleProblemsWithPattern({12, 11, 2, 15, 4, 1, 14, 3, 9, 6, 13, 7, 10, constants::EMPTY, 8, 5}, filename);

    return EXIT_SUCCESS;
}
