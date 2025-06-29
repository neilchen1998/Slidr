#define CATCH_CONFIG_MAIN

#include <vector>   // std::vector
#include <span> // std::span
#include <algorithm> // std::shuffle
#include <random>   // std::mt19937_64
#include <catch2/catch.hpp> // TEST_CASE, SECTION, REQUIRE

#include "math/mathlib.hpp"
#include "constants/constantslib.hpp"   // constants::EMPTY

TEST_CASE( "Hash Range Function", "[main]" )
{
    std::mt19937_64 g(41);

    std::vector<int> v1 {constants::EMPTY, 1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> v2 {3, 1, constants::EMPTY, 2, 8, 7, 6, 5, 4};
    std::vector<int> v3 {v2};
    std::vector<int> v4 {v1};
    std::vector<int> v5 {v1};

    // Shuffle v4 and v5
    std::shuffle(v4.begin(), v4.end(), g);
    std::shuffle(v5.begin(), v5.end(), g);

    // Get their hash values
    std::size_t hash1 = hash_range(std::span(v1.begin(), v1.end()));
    std::size_t hash2 = hash_range(std::span(v2.begin(), v2.end()));
    std::size_t hash3 = hash_range(std::span(v3.begin(), v3.end()));
    std::size_t hash4 = hash_range(std::span(v4.begin(), v4.end()));
    std::size_t hash5 = hash_range(std::span(v5.begin(), v5.end()));

    SECTION ( "Different Node", "[main]")
    {
        REQUIRE (hash1 != hash2);
        REQUIRE (hash4 != hash2);
        REQUIRE (hash4 != hash1);
        REQUIRE (hash4 != hash5);
    }

    SECTION ( "Same Node", "[main]")
    {
        REQUIRE (hash1 == hash1);
        REQUIRE (hash2 == hash2);
        REQUIRE (hash3 == hash3);
        REQUIRE (hash4 == hash4);
        REQUIRE (hash2 == hash3);
    }
}
