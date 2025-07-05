#define CATCH_CONFIG_MAIN

#include <vector>    // std::vector
#include <ranges>    // std::ranges::input_range
#include <unordered_set>    // std::unordered_set
#include <catch2/catch_test_macros.hpp> // TEST_CASE, SECTION, REQUIRE
#include <catch2/matchers/catch_matchers_all.hpp>   // Catch::Matchers::Equals

#include "constants/constantslib.hpp"
#include "solver/solverlib.hpp"

TEST_CASE( "Priority Queue Solver", "[main]" )
{
    SECTION("Puzzle 0", "[trivial case]")
    {
        // 123456780
        std::vector<int> layout {1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY};
        Solver s = Solver(layout);
        auto [isSolved, numOfIters] = s.SolvePuzzle();

        REQUIRE (isSolved);
        REQUIRE (numOfIters == 0);
    }

    SECTION("Puzzle 1", "[general case]")
    {
        // 120453786
        std::vector<int> layout {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
        Solver s = Solver(layout);
        auto [isSolved, _] = s.SolvePuzzle();
        auto depth = s.GetNumOfMoves();
        auto solution = s.GetSolution();

        REQUIRE (isSolved);
        REQUIRE (depth == 2);
        REQUIRE (solution == "↑↑");
    }

    SECTION("Puzzle 2", "[general case]")
    {
        // 536208417
        std::vector<int> layout {5, 3, 6, 2, constants::EMPTY, 8, 4, 1, 7};
        Solver s = Solver(layout);
        auto [isSolved, _] = s.SolvePuzzle();
        auto depth = s.GetNumOfMoves();
        auto solution = s.GetSolution();

        REQUIRE (isSolved);
        REQUIRE (depth == 14);
        REQUIRE_THAT(solution, Catch::Matchers::Equals("↑←↓↓→→↑←↓→↑↑←←") || Catch::Matchers::Equals("↑←↓↓→↑→↓←↑→↑←←")); // there're two valid solutions so far
    }

    SECTION("Puzzle 3", "[general case]")
    {
        // 318652470
        std::vector<int> layout {3, 1, 8, 6, 5, 2, 4, 7, constants::EMPTY};
        Solver s = Solver(layout);
        auto [isSolved, _] = s.SolvePuzzle();
        auto depth = s.GetNumOfMoves();
        auto solution = s.GetSolution();

        REQUIRE (isSolved);
        REQUIRE (depth == 22);
        REQUIRE (solution == "↓→→↓←↑→↑←←↓↓→↑↑←↓↓→↑↑←");
    }

    SECTION("Puzzle 4", "[general case]")
    {
        // 231408576
        std::vector<int> layout {2, 3, 1, 4, constants::EMPTY, 8, 5, 7, 6};
        Solver s = Solver(layout);
        auto [isSolved, _] = s.SolvePuzzle();
        auto depth = s.GetNumOfMoves();
        auto solution = s.GetSolution();

        REQUIRE (isSolved);
        REQUIRE (depth == 18);
        REQUIRE (solution == "←↓→→↑↑←↓←↓→↑→↓←←↑↑");
    }

    SECTION("Puzzle 5", "[general case]")
    {
        // 127405836
        std::vector<int> layout {1, 2, 7, 4, constants::EMPTY, 5, 8, 3, 6};
        Solver s = Solver(layout);
        auto [isSolved, _] = s.SolvePuzzle();
        auto depth = s.GetNumOfMoves();
        auto solution = s.GetSolution();

        REQUIRE (isSolved);
        REQUIRE (depth == 20);
        REQUIRE (solution == "↑→↓↓←↑←↓→→↑←←↑→↓→↑←←");
    }
}

TEST_CASE( "Bucket Queue Solver", "[main]" )
{
    using BucketMinPQ = BucketQueue<std::shared_ptr<Node>, unsigned int, std::greater<Node>>;
    auto pq = BucketMinPQ(50);

    SECTION("Puzzle 0", "[trivial case]")
    {
        // 123456780
        std::vector<int> layout {1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY};
        auto s = Solver<BucketMinPQ>(layout, pq);
        auto [isSolved, numOfIters] = s.SolvePuzzle();

        REQUIRE (isSolved);
        REQUIRE (numOfIters == 0);
    }

    SECTION("Puzzle 1", "[general case]")
    {
        // 120453786
        std::vector<int> layout {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
        auto s = Solver<BucketMinPQ>(layout, pq);
        auto [isSolved, _] = s.SolvePuzzle();
        auto depth = s.GetNumOfMoves();
        auto solution = s.GetSolution();

        REQUIRE (isSolved);
        REQUIRE (depth == 2);
        REQUIRE (solution == "↑↑");
    }

    SECTION("Puzzle 2", "[general case]")
    {
        // 536208417
        std::vector<int> layout {5, 3, 6, 2, constants::EMPTY, 8, 4, 1, 7};
        auto s = Solver<BucketMinPQ>(layout, pq);
        auto [isSolved, _] = s.SolvePuzzle();
        auto depth = s.GetNumOfMoves();
        auto solution = s.GetSolution();

        REQUIRE (isSolved);
        REQUIRE (depth == 14);
        REQUIRE_THAT(solution, Catch::Matchers::Equals("↑←↓↓→→↑←↓→↑↑←←") || Catch::Matchers::Equals("↑←↓↓→↑→↓←↑→↑←←")); // there're two valid solutions so far
    }

    SECTION("Puzzle 3", "[general case]")
    {
        // 318652470
        std::vector<int> layout {3, 1, 8, 6, 5, 2, 4, 7, constants::EMPTY};
        auto s = Solver<BucketMinPQ>(layout, pq);
        auto [isSolved, _] = s.SolvePuzzle();
        auto depth = s.GetNumOfMoves();
        auto solution = s.GetSolution();

        REQUIRE (isSolved);
        REQUIRE (depth == 22);
        REQUIRE (solution == "↓→→↓←↑→↑←←↓↓→↑↑←↓↓→↑↑←");
    }

    SECTION("Puzzle 4", "[general case]")
    {
        // 231408576
        std::vector<int> layout {2, 3, 1, 4, constants::EMPTY, 8, 5, 7, 6};
        auto s = Solver<BucketMinPQ>(layout, pq);
        auto [isSolved, _] = s.SolvePuzzle();
        auto depth = s.GetNumOfMoves();
        auto solution = s.GetSolution();

        REQUIRE (isSolved);
        REQUIRE (depth == 18);
        REQUIRE (solution == "←↓→→↑↑←↓←↓→↑→↓←←↑↑");
    }

    SECTION("Puzzle 5", "[general case]")
    {
        // 127405836
        std::vector<int> layout {1, 2, 7, 4, constants::EMPTY, 5, 8, 3, 6};
        auto s = Solver<BucketMinPQ>(layout, pq);
        auto [isSolved, _] = s.SolvePuzzle();
        auto depth = s.GetNumOfMoves();
        auto solution = s.GetSolution();

        REQUIRE (isSolved);
        REQUIRE (depth == 20);
        REQUIRE (solution == "↑→↓↓←↑←↓→→↑←←↑→↓→↑←←");
    }
}
