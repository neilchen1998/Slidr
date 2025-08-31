#define CATCH_CONFIG_MAIN

#include <vector>    // std::vector
#include <ranges>    // std::ranges::input_range
#include <unordered_set>    // std::unordered_set
#include <catch2/catch_test_macros.hpp> // TEST_CASE, SECTION, REQUIRE
#include <catch2/matchers/catch_matchers_all.hpp>   // Catch::Matchers::Equals
#include "fmt/ranges.h" // fmt::println for vectors

#include "constants/constantslib.hpp"
#include "solver/solverlib.hpp"
#include "creator/creatorlib.hpp"

TEST_CASE( "Solvable Function", "[main]" )
{
    SECTION("Solvalbe", "")
    {
        std::vector<int> layout {1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY};
        bool isSolvable = creator::Solvable(layout);

        REQUIRE(isSolvable);
    }

    SECTION("Solvalbe", "")
    {
        std::vector<int> layout {2, 7, 5, 6, 4, 8, 1, 3, constants::EMPTY};
        bool isSolvable = creator::Solvable(layout);

        REQUIRE(isSolvable);
    }

    SECTION("Solvalbe", "")
    {
        std::vector<int> layout {4, 5, 7, 8, constants::EMPTY, 2, 1, 6, 3};
        bool isSolvable = creator::Solvable(layout);

        REQUIRE(isSolvable);
    }

    SECTION("Unsolvable", "")
    {
        std::vector<int> layout {7, 2, 4, 5, constants::EMPTY, 6, 3, 8, 1};
        bool isSolvable = creator::Solvable(layout);

        REQUIRE_FALSE(isSolvable);
    }

    SECTION("Unsolvable", "")
    {
        std::vector<int> layout {1, 2, 3, 4, 5, 6, 8, 7, constants::EMPTY};
        bool isSolvable = creator::Solvable(layout);

        REQUIRE_FALSE(isSolvable);
    }

    SECTION("Unsolvable", "")
    {
        std::vector<int> layout {2, 3, 6, 1, 8, 5, 4, 7};
        bool isSolvable = creator::Solvable(layout);

        REQUIRE_FALSE(isSolvable);
    }
}

TEST_CASE( "GetRandomLayout Function", "[main]" )
{
    for (size_t i = 0; i < 100; i++)
    {
        SECTION("", "[trivial case]")
        {
            std::vector<int> layout = creator::GetRandomLayout();
            slidr::Solver s {layout};

            auto [solved, _] = s.SolvePuzzle();

            REQUIRE(solved);
        }
    }
}
