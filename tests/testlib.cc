#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <vector>   // std::vector
#include <span> // std::span

#include "math/mathlib.hpp"

TEST_CASE( "Hash Range Function", "[main]" )
{
    std::vector<int> v1 {0xF, 1, 2, 3, 4, 5, 6, 7, 8};
    REQUIRE (hash_range(std::span(v1.begin(), v1.end())) == 4026151718875163160);

    std::vector<int> v2 {3, 1, 0xF, 2, 8, 7, 6, 5, 4};
    REQUIRE (hash_range(std::span(v2.begin(), v2.end())) == 2955272776919177114);
}