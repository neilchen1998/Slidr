#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <vector>   // std::vector
#include <span> // std::span

#include "math/mathlib.hpp"
#include "constants/constantslib.hpp"   // constants::EMPTY

TEST_CASE( "Hash Range Function <8>", "[main]" )
{
    std::vector<int> v1 {constants::EMPTY, 1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> v2 {3, 1, constants::EMPTY, 2, 8, 7, 6, 5, 4};
    std::vector<int> v3 {3, 1, constants::EMPTY, 2, 8, 7, 6, 5, 4};

    std::size_t hashV1 = hash_range(v1);
    std::size_t hashV2 = hash_range(v2);
    std::size_t hashV3 = hash_range(v3);

    SECTION ( "Different Node", "[main]")
    {
        REQUIRE (hashV1 != hashV2);
    }

    SECTION ( "Same Node", "[main]")
    {
        REQUIRE (hashV2 == hashV3);
    }
}

TEST_CASE( "Hash Range Function <16>", "[main]" )
{
    std::vector<int> v1 {3, 1, 11, 10, 13, 9, 5, 4, 15, 8, constants::EMPTY, 7, 6, 2, 14, 12};
    std::vector<int> v2 {3, 1, 11, 10, 13, 9, 5, 4, 15, constants::EMPTY, 8, 7, 6, 2, 14, 12};
    std::vector<int> v3 {3, 1, 11, 10, 13, constants::EMPTY, 5, 4, 15, 9, 8, 7, 6, 2, 14, 12};

    std::size_t hash1 = hash_range(v1);
    std::size_t hash11 = hash_range(v1);
    std::size_t hash2 = hash_range(v2);
    std::size_t hash3 = hash_range(v3);

    SECTION ( "Different Node", "[main]")
    {
        REQUIRE (hash2 != hash1);
    }

    SECTION ( "Different Node", "[main]")
    {
        REQUIRE (hash3 != hash1);
    }

    SECTION ( "Same Node", "[main]")
    {
        REQUIRE (hash11 == hash1);
    }
}
