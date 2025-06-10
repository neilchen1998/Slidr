#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <vector>    // std::vector
#include <ranges>    // std::ranges::input_range
#include <unordered_set>    // std::unordered_set
#include <optional> // std::optional
#include <string_view>  // std::string_view

#include <iostream>

#include "constants/constantslib.hpp"
#include "math/mathlib.hpp"
#include "node/nodelib.hpp"
#include "solver/solverlib.hpp"
#include "prompt/promptlib.hpp"

TEST_CASE( "Solver Constructor", "[main]" )
{
    SECTION("Valid Input", "1")
    {
        std::string_view input {"12345678x"};
        std::vector<int> vec {1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY};
        auto layout = prompt::parse_string_to_layout(input);

        REQUIRE(layout.has_value());
        REQUIRE(layout.value() == vec);
    }

    SECTION("Valid Input", "2")
    {
        std::string_view input {"123X56784"};
        std::vector<int> vec {1, 2, 3, constants::EMPTY, 5, 6, 7, 8, 4};
        auto layout = prompt::parse_string_to_layout(input);

        REQUIRE(layout.has_value());
        REQUIRE(layout.value() == vec);
    }

    SECTION("Invalid Input", "not enough elements")
    {
        std::string_view input {"123456"};
        auto layout = prompt::parse_string_to_layout(input);

        REQUIRE(layout == std::nullopt);
    }

    SECTION("Invalid Input", "invalid value")
    {
        std::string_view input {"123456.8x"};
        auto layout = prompt::parse_string_to_layout(input);

        REQUIRE(layout == std::nullopt);
    }

    SECTION("Invalid Input", "invalid value")
    {
        std::string_view input {"1A345678X"};
        auto layout = prompt::parse_string_to_layout(input);

        REQUIRE(layout == std::nullopt);
    }

    SECTION("Invalid Input", "duplicated values")
    {
        std::string_view input {"12345688x"};
        std::vector<int> vec {1, 2, 3, 4, 5, 6, 8, 8, constants::EMPTY};
        auto layout = prompt::parse_string_to_layout(input);
        bool isValid = prompt::validate_puzzle(std::span(layout.value()));

        REQUIRE(layout.has_value());
        REQUIRE(layout.value() == vec);
        REQUIRE(isValid == false);
    }
}
