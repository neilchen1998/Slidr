#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <vector>   // std::vector
#include <string>   // std::string

#include "constants/constantslib.hpp"   // constants::EMPTY
#include "terminal/terminallib.hpp"

TEST_CASE( "Test Inputs from the Terminal <3>", "[terminal]" )
{

    SECTION("A valid input", "[foo]")
    {
        std::string test_input("1 2 3 4 5 6 7 8 x");
        auto ret = parse_string_for_8(test_input);

        REQUIRE(ret != std::nullopt);
        REQUIRE(ret.value() == std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY}));
    }

    SECTION("A valid input", "[foo]")
    {
        std::string test_input("1 2 #  3 4 5 6 7 8");
        auto ret = parse_string_for_8(test_input);

        REQUIRE(ret != std::nullopt);
        REQUIRE(ret.value() == std::vector<int>({1, 2, constants::EMPTY, 3, 4, 5, 6, 7, 8}));
    }

    SECTION("An invalid input (missing pieces)", "[foo]")
    {
        std::string test_input("1 2 3 4 5 6 7 x");
        auto ret = parse_string_for_8(test_input);

        REQUIRE(ret == std::nullopt);
    }

    SECTION("A valid input (an invalid piece)", "[foo]")
    {
        std::string test_input("1 2 3 4 5 6 7 8 255");
        auto ret = parse_string_for_8(test_input);

        REQUIRE(ret == std::nullopt);
    }

    SECTION("An invalid input (missing the empty pieces)", "[foo]")
    {
        std::string test_input("1 2 3 4 5 6 7 8");
        auto ret = parse_string_for_8(test_input);

        REQUIRE(ret == std::nullopt);
    }

    SECTION("An invalid input (duplicated pieces)", "[foo]")
    {
        std::string test_input("1 2 3 4 5 6 7 8 8");
        auto ret = parse_string_for_8(test_input);

        REQUIRE(ret == std::nullopt);
    }

    SECTION("An invalid input (no pieces)", "[foo]")
    {
        std::string test_input("");
        auto ret = parse_string_for_8(test_input);

        REQUIRE(ret == std::nullopt);
    }

    SECTION("An invalid input (excessive pieces)", "[foo]")
    {
        std::string test_input("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 15 15 15 15 15 15");
        auto ret = parse_string_for_8(test_input);

        REQUIRE(ret == std::nullopt);
    }
}

TEST_CASE( "Test Inputs from the Terminal <4>", "[terminal]" )
{

    SECTION("A valid input", "[foo]")
    {
        std::string test_input("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 x");
        auto ret = parse_string_for_15(test_input);

        REQUIRE(ret != std::nullopt);
        REQUIRE(ret.value() == std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, constants::EMPTY}));
    }

    SECTION("A valid input", "[foo]")
    {
        std::string test_input("1 2 3 4 5 # 7 8 9 10 11 12 13 14 15 6");
        auto ret = parse_string_for_15(test_input);

        REQUIRE(ret != std::nullopt);
        REQUIRE(ret.value() == std::vector<int>({1, 2, 3, 4, 5, constants::EMPTY, 7, 8, 9, 10, 11, 12, 13, 14, 15, 6}));
    }

    SECTION("An invalid input (missing pieces)", "[foo]")
    {
        std::string test_input("1 2 3 4 5 6 7 8 9 10");
        auto ret = parse_string_for_15(test_input);

        REQUIRE(ret == std::nullopt);
    }

    SECTION("A valid input (an invalid piece)", "[foo]")
    {
        std::string test_input("1 2 3 4 5 6 7 8 9 10 11 255 13 14 15 x");
        auto ret = parse_string_for_15(test_input);

        REQUIRE(ret == std::nullopt);
    }

    SECTION("An invalid input (missing the empty pieces)", "[foo]")
    {
        std::string test_input("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15");
        auto ret = parse_string_for_15(test_input);

        REQUIRE(ret == std::nullopt);
    }

    SECTION("An invalid input (duplicated pieces)", "[foo]")
    {
        std::string test_input("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 1");
        auto ret = parse_string_for_15(test_input);

        REQUIRE(ret == std::nullopt);
    }

    SECTION("An invalid input (no pieces)", "[foo]")
    {
        std::string test_input("");
        auto ret = parse_string_for_15(test_input);

        REQUIRE(ret == std::nullopt);
    }

    SECTION("An invalid input (excessive pieces)", "[foo]")
    {
        std::string test_input("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 15 15 15 15 15 15");
        auto ret = parse_string_for_15(test_input);

        REQUIRE(ret == std::nullopt);
    }
}
