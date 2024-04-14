#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <vector>    // std::vector
#include <array>    // std::array
#include <algorithm>    // std::ranges::equal
#include <span> // std::span

#include "constants/constantslib.hpp"
#include "math/mathlib.hpp"
#include "node/nodelib.hpp"

struct Tester : Node
{
    std::vector<int> GetLayout() const { return this-> layout; }

    int GetPosX() const { return this->posX; }
};

TEST_CASE( "Node Initialization", "[main]" )
{
    SECTION("Unsolved", "[some_details]")
    {
        std::vector<int> layout {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
        Node n(layout);

        // tests all its members upon initialization
        REQUIRE (std::ranges::equal(static_cast<const Tester&>(n).GetLayout(), layout));
        REQUIRE (static_cast<const Tester&>(n).GetPosX() == 2);
        REQUIRE (n.GetCurrentManhattanDistance() == 2);
        REQUIRE (n.GetCurrentHashValue() == hash_range(std::span(layout)));
        REQUIRE (n.IsSolved() == false);
    }

    SECTION("Solved", "[some_details]")
    {
        std::vector<int> layout {1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY};
        Node n(layout);

        // tests all its members upon initialization
        REQUIRE (std::ranges::equal(static_cast<const Tester&>(n).GetLayout(), layout));
        REQUIRE (static_cast<const Tester&>(n).GetPosX() == 8);
        REQUIRE (n.GetCurrentManhattanDistance() == 0);
        REQUIRE (n.GetCurrentHashValue() == hash_range(std::span(layout)));
        REQUIRE (n.IsSolved());
    }
}

TEST_CASE( "Available Moves", "[main]" )
{
    // initializes all possible positions that the empty puzzle can be in
    Node middle({1, 2, 3, 4, constants::EMPTY, 6, 7, 5, 8});
    Node topLeft({constants::EMPTY, 2, 3, 4, 1, 6, 7, 5, 8});
    Node topRight({1, 2, constants::EMPTY, 4, 3, 6, 7, 5, 8});
    Node middleLeft({1, 2, 3, constants::EMPTY, 4, 6, 7, 5, 8});
    Node middleRight({1, 2, 3, 4, 6, constants::EMPTY, 7, 5, 8});
    Node bottomLeft({1, 2, 3, 4, 7, 6, constants::EMPTY, 5, 8});
    Node bottomRight({1, 2, 3, 4, 8, 6, 7, 5, constants::EMPTY});
    Node centerTop({1, constants::EMPTY, 3, 4, 2, 6, 7, 5, 8});
    Node centerBottom({1, 2, 3, 4, 5, 6, 7, constants::EMPTY, 8});

    // grabs the available moves and sorts it
    auto movesMiddle = middle.AvailableMoves();
    auto movesTopLeft = topLeft.AvailableMoves();
    auto movesTopRight = topRight.AvailableMoves();
    auto movesMiddleLeft = middleLeft.AvailableMoves();
    auto movesMiddleRight = middleRight.AvailableMoves();
    auto movesBottomLeft = bottomLeft.AvailableMoves();
    auto movesBottomRight = bottomRight.AvailableMoves();
    auto movesCenterTop = centerTop.AvailableMoves();
    auto movesCenterBottom = centerBottom.AvailableMoves();

    // grabs the true available moves and sorts it
    constexpr std::array acutalMovesMiddle {constants::RIGHT, constants::UP, constants::LEFT, constants::DOWN};
    constexpr std::array acutalMovesTopLeft {constants::RIGHT, constants::DOWN};
    constexpr std::array acutalMovesTopRight {constants::LEFT, constants::DOWN};
    constexpr std::array acutalMovesMiddleLeft {constants::RIGHT, constants::UP, constants::DOWN};
    constexpr std::array acutalMovesMiddleRight {constants::UP, constants::LEFT, constants::DOWN};
    constexpr std::array acutalMovesBottomLeft {constants::RIGHT, constants::UP};
    constexpr std::array acutalMovesBottomRight {constants::UP, constants::LEFT};
    constexpr std::array acutalMovesCenterTop {constants::RIGHT, constants::LEFT, constants::DOWN};
    constexpr std::array acutalMovesCenterBottom {constants::RIGHT, constants::UP, constants::LEFT};

    // asserts the available moves from all 9 positions
    REQUIRE (std::ranges::equal(movesMiddle, acutalMovesMiddle));
    REQUIRE (std::ranges::equal(movesTopLeft, acutalMovesTopLeft));
    REQUIRE (std::ranges::equal(movesTopRight, acutalMovesTopRight));
    REQUIRE (std::ranges::equal(movesMiddleLeft, acutalMovesMiddleLeft));
    REQUIRE (std::ranges::equal(movesMiddleRight, acutalMovesMiddleRight));
    REQUIRE (std::ranges::equal(movesBottomLeft, acutalMovesBottomLeft));
    REQUIRE (std::ranges::equal(movesBottomRight, acutalMovesBottomRight));
    REQUIRE (std::ranges::equal(movesCenterTop, acutalMovesCenterTop));
    REQUIRE (std::ranges::equal(movesCenterBottom, acutalMovesCenterBottom));
}

TEST_CASE( "Get Next Layout", "[main]" )
{
    // initializes the start layout
    Node middle({3, 6, 4, 8, constants::EMPTY, 5, 7, 2, 1});
    constexpr int acutalPosX = 4;

    // grabs the available moves
    auto movesMiddle = middle.AvailableMoves();

    // the actual layouts after the moves
    constexpr std::array actualRightLayout {3, 6, 4, 8, 5, constants::EMPTY, 7, 2, 1};
    constexpr std::array actualUpLayout {3, constants::EMPTY, 4, 8, 6, 5, 7, 2, 1};
    constexpr std::array actualLeftLayout {3, 6, 4, constants::EMPTY, 8, 5, 7, 2, 1};
    constexpr std::array actualDownLayout {3, 6, 4, 8, 2, 5, 7, constants::EMPTY, 1};

    // the actual positions of X after the moves
    constexpr int actualRightPosX = acutalPosX + 1;
    constexpr int actualUpPosX = acutalPosX - constants::EIGHT_PUZZLE_SIZE;
    constexpr int actualLeftPosX = acutalPosX - 1;
    constexpr int actualDownPosX = acutalPosX + constants::EIGHT_PUZZLE_SIZE;

    // test cases
    auto itr = movesMiddle.begin();
    SECTION("Right", "[some_details]")
    {
        auto [childLayout, childPosX] = middle.GetNextLayout(*itr);

        REQUIRE (std::ranges::equal(childLayout, actualRightLayout));
        REQUIRE (childPosX == actualRightPosX);
    }

    ++itr;
    SECTION("Up", "[some_details]")
    {
        auto [childLayout, childPosX] = middle.GetNextLayout(*itr);

        REQUIRE (std::ranges::equal(childLayout, actualUpLayout));
        REQUIRE (childPosX == actualUpPosX);

    }

    ++itr;
    SECTION("Left", "[some_details]")
    {
        auto [childLayout, childPosX] = middle.GetNextLayout(*itr);

        REQUIRE (std::ranges::equal(childLayout, actualLeftLayout));
        REQUIRE (childPosX == actualLeftPosX);

    }

    ++itr;
    SECTION("Down", "[some_details]")
    {
        auto [childLayout, childPosX] = middle.GetNextLayout(*itr);

        REQUIRE (std::ranges::equal(childLayout, actualDownLayout));
        REQUIRE (childPosX == actualDownPosX);
    }
}

TEST_CASE( "Operators", "[main]" )
{
    std::vector<int> layout1 {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
    Node n1(layout1);

    std::vector<int> layout2 {1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY};
    Node n2(layout2);

    SECTION("Less Than", "[some_details]")
    {
        REQUIRE ((n1 < n2) == false);
        REQUIRE ((n2 < n1));
    }

    SECTION("Greater Than", "[some_details]")
    {
        REQUIRE ((n1 > n2));
        REQUIRE ((n2 > n1) == false);
    }
}
