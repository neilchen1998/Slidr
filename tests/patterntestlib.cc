#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <vector>   // std::vector
#include <string>   // std::string
#include <utility>  // std::pair

#include "pattern/patternlib.hpp"
#include "math/mathlib.hpp"
#include "constants/constantslib.hpp"   // constants::EMPTY

TEST_CASE( "Hash Range Function <8>", "[main]" )
{
    const std::string filename("/home/neil_poseidon/C++/8-Puzzle/tests/fifteen-puzzle-patterns.txt");

    const std::vector<int> trueSolution0 {1, 1, 0, 3, 0, 1, 2, 3, 3, 2, 1, 1, 0, 1, 2, 2, 3, 0, 0, 3, 2, 1, 0, 0, 1, 2, 2, 2, 3, 0, 0, 1, 2, 3, 3, 0, 0, 3, 2, 1, 1, 0, 3, 3, 2, 1, 1, 0, 1, 2, 3, 0, 3, 3};

    const std::vector<int> trueSolution1 {2, 3, 0, 0, 0, 1, 2, 1, 0, 3, 2, 2, 2, 3, 0 , 0, 0, 1, 2, 2, 1, 2, 3, 3 ,0, 0, 0, 1, 2, 1, 2, 3, 2, 3, 0, 0, 3, 2, 2, 1, 0, 1, 0, 1, 0 , 3, 3, 3};

    const std::vector<int> trueSolution2 {1, 0, 0, 0, 3, 2, 2, 3, 2, 1, 0, 1, 0, 3, 3, 3, 2, 1, 1, 1, 2, 3, 0, 3, 0, 3, 2, 2, 1, 1, 0, 1, 0, 3, 3, 0, 1 ,1 ,2, 3, 2, 3, 3, 2, 1, 1, 0, 3, 0, 0 ,3};

    const std::size_t trueHash0 = 63216040904800;
    const std::size_t trueHash1 = 63193060526287;
    const std::size_t trueHash2 = 63217678687805;

    auto sols = pattern::LoadSolution(filename);

    SECTION("Puzzle 0", "[general case]")
    {
        REQUIRE(sols.count(trueHash0) != 0);
        REQUIRE(sols[trueHash0] == trueSolution0);
    }

    SECTION("Puzzle 1", "[general case]")
    {
        REQUIRE(sols.count(trueHash1) != 0);
        REQUIRE(sols[trueHash1] == trueSolution1);
    }

    SECTION("Puzzle 2", "[general case]")
    {
        REQUIRE(sols.count(trueHash2) != 0);
        REQUIRE(sols[trueHash2] == trueSolution2);
    }
}
