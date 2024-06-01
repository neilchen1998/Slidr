#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <vector>   // std::vector
#include <string>   // std::string
#include <iostream> // std::cin
#include <sstream>  // std::cin

#include "pattern/patternlib.hpp"
#include "math/mathlib.hpp"
#include "constants/constantslib.hpp"   // constants::EMPTY
#include "terminal/terminallib.hpp"

TEST_CASE( "Test Inputs from the Terminal <3>", "[terminal]" )
{

    SECTION("A valid input", "[foo]")
    {
        std::istringstream test_input("1 2 3 4 5 6 7 8 x");
        auto cinOld = std::cin.rdbuf(test_input.rdbuf());
        auto ret = try_read_from_terminal_for_8();

        std::cin.rdbuf(cinOld);
        REQUIRE(ret != std::nullopt);
        REQUIRE(ret.value() == std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY}));
    }

    SECTION("An invalid input (missing pieces)", "[foo]")
    {
        std::istringstream test_input("1 2 3 4 5 6 7 x");
        auto cinOld = std::cin.rdbuf(test_input.rdbuf());
        auto ret = try_read_from_terminal_for_8();

        std::cin.rdbuf(cinOld);
        REQUIRE(ret == std::nullopt);
    }

    SECTION("A valid input (an invalid piece)", "[foo]")
    {
        std::istringstream test_input("1 2 3 4 5 6 7 8 255");
        auto cinOld = std::cin.rdbuf(test_input.rdbuf());
        auto ret = try_read_from_terminal_for_8();

        std::cin.rdbuf(cinOld);
        REQUIRE(ret == std::nullopt);
    }

    SECTION("An invalid input (missing the empty pieces)", "[foo]")
    {
        std::istringstream test_input("1 2 3 4 5 6 7 8");
        auto cinOld = std::cin.rdbuf(test_input.rdbuf());
        auto ret = try_read_from_terminal_for_8();

        std::cin.rdbuf(cinOld);
        REQUIRE(ret == std::nullopt);
    }

    SECTION("An invalid input (duplicated pieces)", "[foo]")
    {
        std::istringstream test_input("1 2 3 4 5 6 7 8 8");
        auto cinOld = std::cin.rdbuf(test_input.rdbuf());
        auto ret = try_read_from_terminal_for_8();

        std::cin.rdbuf(cinOld);
        REQUIRE(ret == std::nullopt);
    }

    SECTION("An invalid input (no pieces)", "[foo]")
    {
        std::istringstream test_input("");
        auto cinOld = std::cin.rdbuf(test_input.rdbuf());
        auto ret = try_read_from_terminal_for_8();

        std::cin.rdbuf(cinOld);
        REQUIRE(ret == std::nullopt);
    }

    SECTION("An invalid input (excessive pieces)", "[foo]")
    {
        std::istringstream test_input("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 15 15 15 15 15 15");
        auto cinOld = std::cin.rdbuf(test_input.rdbuf());
        auto ret = try_read_from_terminal_for_8();

        std::cin.rdbuf(cinOld);
        REQUIRE(ret == std::nullopt);
    }
}

TEST_CASE( "Test Inputs from the Terminal <4>", "[terminal]" )
{

    SECTION("A valid input", "[foo]")
    {
        std::istringstream test_input("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 x");
        auto cinOld = std::cin.rdbuf(test_input.rdbuf());
        auto ret = try_read_from_terminal_for_15();

        std::cin.rdbuf(cinOld);
        REQUIRE(ret != std::nullopt);
        REQUIRE(ret.value() == std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, constants::EMPTY}));
    }

    SECTION("An invalid input (missing pieces)", "[foo]")
    {
        std::istringstream test_input("1 2 3 4 5 6 7 8 9 10");
        auto cinOld = std::cin.rdbuf(test_input.rdbuf());
        auto ret = try_read_from_terminal_for_15();

        std::cin.rdbuf(cinOld);
        REQUIRE(ret == std::nullopt);
    }

    SECTION("A valid input (an invalid piece)", "[foo]")
    {
        std::istringstream test_input("1 2 3 4 5 6 7 8 9 10 11 255 13 14 15 x");
        auto cinOld = std::cin.rdbuf(test_input.rdbuf());
        auto ret = try_read_from_terminal_for_15();

        std::cin.rdbuf(cinOld);
        REQUIRE(ret == std::nullopt);
    }

    SECTION("An invalid input (missing the empty pieces)", "[foo]")
    {
        std::istringstream test_input("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15");
        auto cinOld = std::cin.rdbuf(test_input.rdbuf());
        auto ret = try_read_from_terminal_for_15();

        std::cin.rdbuf(cinOld);
        REQUIRE(ret == std::nullopt);
    }

    SECTION("An invalid input (duplicated pieces)", "[foo]")
    {
        std::istringstream test_input("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 1");
        auto cinOld = std::cin.rdbuf(test_input.rdbuf());
        auto ret = try_read_from_terminal_for_15();

        std::cin.rdbuf(cinOld);
        REQUIRE(ret == std::nullopt);
    }

    SECTION("An invalid input (no pieces)", "[foo]")
    {
        std::istringstream test_input("");
        auto cinOld = std::cin.rdbuf(test_input.rdbuf());
        auto ret = try_read_from_terminal_for_15();

        std::cin.rdbuf(cinOld);
        REQUIRE(ret == std::nullopt);
    }

    SECTION("An invalid input (excessive pieces)", "[foo]")
    {
        std::istringstream test_input("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 15 15 15 15 15 15");
        auto cinOld = std::cin.rdbuf(test_input.rdbuf());
        auto ret = try_read_from_terminal_for_15();

        std::cin.rdbuf(cinOld);
        REQUIRE(ret == std::nullopt);
    }
}
