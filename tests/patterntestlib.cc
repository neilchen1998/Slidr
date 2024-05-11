#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <vector>   // std::vector
#include <string>   // std::string

#include "pattern/patternlib.hpp"
#include "math/mathlib.hpp"
#include "constants/constantslib.hpp"   // constants::EMPTY

const std::string filename("/home/neil_poseidon/C++/8-Puzzle/tests/fifteen-puzzle-patterns-testing.txt");

const std::vector<int> trueSolution0 {1, 1, 0, 3, 0, 1, 2, 3, 3, 2, 1, 1, 0, 1, 2, 2, 3, 0, 0, 3, 2, 1, 0, 0, 1, 2, 2, 2, 3, 0, 0, 1, 2, 3, 3, 0, 0, 3, 2, 1, 1, 0, 3, 3, 2, 1, 1, 0, 1, 2, 3, 0, 3, 3};
const std::vector<int> trueSolution1 {2, 3, 0, 0, 0, 1, 2, 1, 0, 3, 2, 2, 2, 3, 0 , 0, 0, 1, 2, 2, 1, 2, 3, 3 ,0, 0, 0, 1, 2, 1, 2, 3, 2, 3, 0, 0, 3, 2, 2, 1, 0, 1, 0, 1, 0 , 3, 3, 3};
const std::vector<int> trueSolution2 {1, 0, 0, 0, 3, 2, 2, 3, 2, 1, 0, 1, 0, 3, 3, 3, 2, 1, 1, 1, 2, 3, 0, 3, 0, 3, 2, 2, 1, 1, 0, 1, 0, 3, 3, 0, 1 ,1 ,2, 3, 2, 3, 3, 2, 1, 1, 0, 3, 0, 0 ,3};
const std::vector<int> trueSolution3 {0, 1, 1, 2, 2, 3, 3, 0, 0, 1, 2, 1, 1, 2, 3, 2, 3, 0, 3, 0, 1, 0, 1, 2, 2, 2, 3, 0, 1, 0, 1, 0, 3, 3, 2, 2, 3, 0, 1, 1, 2, 3, 0, 1, 0, 3, 3};

const std::size_t trueHash0 = 63216040904800;
const std::size_t trueHash1 = 63193060526287;
const std::size_t trueHash2 = 63217678687805;
const std::size_t trueHash3 = 62960857729273;

TEST_CASE( "Export Solutions <8>", "[main]" )
{
    pattern::ExportSolution(trueHash0, trueSolution0, filename, false);
    pattern::ExportSolution(trueHash1, trueSolution1, filename);
    pattern::ExportSolution(trueHash2, trueSolution2, filename);
    pattern::ExportSolution(trueHash3, trueSolution3, filename);
}

TEST_CASE( "Load Solutions <8>", "[main]" )
{
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

    SECTION("Puzzle 3", "[general case]")
    {
        REQUIRE(sols.count(trueHash3) != 0);
        REQUIRE(sols[trueHash3] == trueSolution3);
    }
}
