#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <vector>   // std::vector
#include <span> // std::span

#include "math/mathlib.hpp"
#include "constants/constantslib.hpp"   // constants::EMPTY

TEST_CASE( "Hash Range Function", "[main]" )
{
    std::vector<int> v1 {constants::EMPTY, 1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> v2 {3, 1, constants::EMPTY, 2, 8, 7, 6, 5, 4};
    std::vector<int> v3 {3, 1, constants::EMPTY, 2, 8, 7, 6, 5, 4};

    std::size_t hashV1 = hash_range(std::span(v1.begin(), v1.end()));
    std::size_t hashV2 = hash_range(std::span(v2.begin(), v2.end()));
    std::size_t hashV3 = hash_range(std::span(v3.begin(), v3.end()));

    SECTION ( "Different Node", "[main]")
    {
        REQUIRE (hashV1 != hashV2);
    }

    SECTION ( "Same Node", "[main]")
    {
        REQUIRE (hashV2 == hashV3);
    }
}
