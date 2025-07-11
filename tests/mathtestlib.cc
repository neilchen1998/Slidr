#define CATCH_CONFIG_MAIN

#include <vector>   // std::vector
#include <span> // std::span
#include <algorithm> // std::shuffle
#include <random>   // std::mt19937_64
#include <catch2/catch_test_macros.hpp> // TEST_CASE, SECTION, REQUIRE

#include "math/mathlib.hpp"
#include "constants/constantslib.hpp"   // constants::EMPTY

/// @brief Hashes a single arguments with an initial hash value
/// @tparam T The argument type
/// @param seed The initial hash value
/// @param u The argument
template <std::integral T>
inline void hash_combine_simple(std::size_t& seed, const T& u)
{
    seed ^= std::hash<T>{}(u) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

TEST_CASE( "Hash Combine", "[main]" )
{
    std::mt19937_64 gen(12);
    std::uniform_int_distribution<> distrib(1, constants::EMPTY);

    std::size_t h0 = distrib(gen), h1 = h0;
    const std::size_t v = distrib(gen);
    const std::size_t u = distrib(gen);
    const std::size_t w = distrib(gen);
    const std::size_t x = distrib(gen);
    const std::size_t y = distrib(gen);
    const std::size_t z = distrib(gen);

    SECTION ( "Two parameters", "[main]" )
    {
        hash_combine(h0, u, v);

        hash_combine_simple(h1, u);
        hash_combine_simple(h1, v);

        REQUIRE (h0 == h1);
    }

    SECTION ( "Four parameters", "[main]" )
    {
        hash_combine(h0, u, v, w, x);

        hash_combine_simple(h1, u);
        hash_combine_simple(h1, v);
        hash_combine_simple(h1, w);
        hash_combine_simple(h1, x);

        REQUIRE (h0 == h1);
    }

    SECTION ( "Six parameters", "[main]" )
    {
        hash_combine(h0, u, v, w, x, y, z);

        hash_combine_simple(h1, u);
        hash_combine_simple(h1, v);
        hash_combine_simple(h1, w);
        hash_combine_simple(h1, x);
        hash_combine_simple(h1, y);
        hash_combine_simple(h1, z);

        REQUIRE (h0 == h1);
    }
}

TEST_CASE( "Hash Range Function", "[main]" )
{
    std::mt19937_64 gen(41);

    std::vector<int> v1 {constants::EMPTY, 1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> v2 {3, 1, constants::EMPTY, 2, 8, 7, 6, 5, 4};
    std::vector<int> v3 {v2};
    std::vector<int> v4 {v1};
    std::vector<int> v5 {v1};

    // Shuffle v4 and v5
    std::shuffle(v4.begin(), v4.end(), gen);
    std::shuffle(v5.begin(), v5.end(), gen);

    // Get their hash values
    std::size_t hash1 = hash_range(std::span(v1.begin(), v1.end()));
    std::size_t hash2 = hash_range(std::span(v2.begin(), v2.end()));
    std::size_t hash3 = hash_range(std::span(v3.begin(), v3.end()));
    std::size_t hash4 = hash_range(std::span(v4.begin(), v4.end()));
    std::size_t hash5 = hash_range(std::span(v5.begin(), v5.end()));

    SECTION ( "Different Node", "[main]" )
    {
        REQUIRE (hash1 != hash2);
        REQUIRE (hash4 != hash2);
        REQUIRE (hash4 != hash1);
        REQUIRE (hash4 != hash5);
    }

    SECTION ( "Same Node", "[main]" )
    {
        REQUIRE (hash1 == hash1);
        REQUIRE (hash2 == hash2);
        REQUIRE (hash3 == hash3);
        REQUIRE (hash4 == hash4);
        REQUIRE (hash2 == hash3);
    }
}
