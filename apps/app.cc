#include <iostream> // std::cerr
#include <stdlib.h> // EXIT_SUCCESS, EXIT_FAILURE
#include <cstdlib>  // std::size_t
#include <vector>   // std::vector
#include <queue>    // std::priority_queue
#include <tuple>    // std::tuple
#include <ranges>    // std::ranges
#include <random>   // std::random_device, std::mt19937, std::uniform_int_distribution

#include <boost/program_options.hpp>    // boost::program_options

#include "constants/constantslib.hpp"
#include "math/mathlib.hpp"
#include "pattern/patternlib.hpp"
#include "node/nodelib.hpp"
#include "solver/solverlib.hpp"
#include "terminal/terminallib.hpp"

const std::vector<int> FIFTEEN_GOAL_STATE {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, constants::EMPTY};

namespace po = boost::program_options;

template <int GridSize>
struct Tester : Node<GridSize>
{
    std::vector<int> GetState() const { return this->state; }

    int GetPosX() const { return this->posX; }
};

void SolveEightPuzzleProblem(const std::vector<int>& initialState)
{
    // the 8 puzzle problem
    std::cout << "=== 8 Puzzle Problem ===\n";
    Node<constants::EIGHT_PUZZLE_SIZE> n(initialState);
    Solver<constants::EIGHT_PUZZLE_SIZE> s = Solver(n);

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

    // only show the solution is the puzzle was solved
    if (isSolved && s.GetDepth())
    {
        std::cout << "Start:\n";
        n.Print();
        std::cout << "************" << std::endl;
        int i = 1;
        for (const auto& sol : solution | std::views::drop(1))  // drop the start state
        {
            std::cout << "Step " << i << ":\n";
            sol.Print();
            std::cout << "************\n";

            ++i;
        }

        std::cout << "Move sequence:\n";
        std::vector<int> sequence {s.GetSequence()};
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

    // only show the solution is the puzzle was solved
    if (isSolved && s.GetDepth())
    {
        std::cout << "Start:\n";
        n.Print();
        std::cout << "************" << std::endl;
        int i = 1;
        for (const auto& sol : solution | std::views::drop(1))  // drop the start state
        {
            std::cout << "Step " << i << ":\n";
            sol.Print();
            std::cout << "************\n";

            ++i;
        }

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

int main(int argc, char* argv[])
{
    // variables
    std::string input;
    std::string filename;
    unsigned int puzzleType;
    std::string feature;
    bool patternLibEnabled;

    // creates options descriptions and default values
    po::options_description desc("Options:");
    desc.add_options()
        ("help,h", "Display this information")
        ("input,i", po::value<std::string>(&input)->value_name("<INPUT_LAYOUT>")->default_value(""), "the layout of the puzzle")
        ("filename,fn", po::value<std::string>(&filename)->value_name("<PATTERN_FILENAME>")->default_value("/home/neil_poseidon/C++/8-Puzzle/training-patterns"), "the filename for the pattern library")
        ("feature,f", po::value<std::string>(&feature)->value_name("<FEATURE>")->default_value("solver"), "the feature of desired")
        ("pattern,p", po::value<bool>(&patternLibEnabled)->value_name("<FEATURE>")->default_value(false), "use pattern library")
        ("type,t", po::value<unsigned int>(&puzzleType)->value_name("<PUZZLE_TYPE>")->default_value(0), "the type of puzzle"); // (<long name>,<short name>, <argument(s)>, <description>)

    // creates the variables map and stores the inputs to the map
    po::variables_map vm;

    // makes "input" token be the positional option, i.e., token with no option name
    po::positional_options_description p;
    p.add("input", -1);

    // checks if the user inputs are valid
    try
    {
        // parses the arguments and writes the variables according to the variables map
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        po::notify(vm);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    // checks if the user selects --help
    if (vm.count("help"))
    {
        std::cout << desc << "\n";
        return EXIT_FAILURE;
    }

    // determines the feature
    if (feature == "solver")
    {
        // determine the puzzle type
        if (puzzleType == 8)
        {
            // parses the input
            auto layout = parse_string_for_8(input);
            if (!layout.has_value())
            {
                std::cerr << "Invalid input!\n" << std::endl;
                return EXIT_FAILURE;
            }

            SolveEightPuzzleProblem(layout.value());
        }
        else if (puzzleType == 15)
        {
            // parses the input
            auto layout = parse_string_for_15(input);
            if (!layout.has_value())
            {
                std::cerr << "Invalid input!\n" << std::endl;
                return EXIT_FAILURE;
            }

            // checks whether or not the pattern library will be used
            if (patternLibEnabled)
            {
                SolveFifteenPuzzleProblemsWithPattern(layout.value(), filename);
            }
            else
            {
                SolveFifteenPuzzleProblem(layout.value());
            }
        }
    }
    else if (feature == "generator")
    {
        GeneratePatternsForFifteenPuzzleProblem(200, 1200, filename);
    }

    // GeneratePatternsForFifteenPuzzleProblem(200, 1200, filename);
    // SolveFifteenPuzzleProblem({7, 2, 9, 6, 8, constants::EMPTY, 3, 13, 4, 1, 10, 5, 14, 15, 11, 12});
    // SolveFifteenPuzzleProblem({12, 11, 2, 15, 4, 1, 14, 3, 9, 6, 13, 7, 10, constants::EMPTY, 8, 5}, filename);
    // SolveFifteenPuzzleProblemsWithPattern({12, 11, 2, 15, 4, 1, 14, 3, 9, 6, 13, 7, 10, constants::EMPTY, 8, 5}, filename);



    return EXIT_SUCCESS;
}
