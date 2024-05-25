#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <vector>    // std::vector
#include <array>    // std::array
#include <algorithm>    // std::ranges::equal
#include <span> // std::span

#include "constants/constantslib.hpp"
#include "math/mathlib.hpp"
#include "node/nodelib.hpp"

template <int GridSize>
struct Tester : Node<GridSize>
{
    std::vector<int> GetState() const { return this->state; }

    int GetPosX() const { return this->posX; }
};

TEST_CASE( "Node<3> Initialization", "[main]" )
{
    constexpr int GridSize = constants::EIGHT_PUZZLE_SIZE;
    SECTION("Unsolved", "[some_details]")
    {
        std::vector<int> state {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
        Node<GridSize> n(state);

        // tests all its members upon initialization
        REQUIRE (std::ranges::equal(static_cast<const Tester<GridSize>&>(n).GetState(), state));
        REQUIRE (static_cast<const Tester<GridSize>&>(n).GetPosX() == 2);
        REQUIRE (n.GetManhattanDistance() == 2);
        REQUIRE (n.GetHashValue() == hash_range(std::span(state)));
        REQUIRE (n.IsSolved() == false);
    }

    SECTION("Solved", "[some_details]")
    {
        std::vector<int> state {1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY};
        Node<GridSize> n(state);

        // tests all its members upon initialization
        REQUIRE (std::ranges::equal(static_cast<const Tester<GridSize>&>(n).GetState(), state));
        REQUIRE (static_cast<const Tester<GridSize>&>(n).GetPosX() == 8);
        REQUIRE (n.GetManhattanDistance() == 0);
        REQUIRE (n.GetHashValue() == hash_range(std::span(state)));
        REQUIRE (n.IsSolved());
    }
}

TEST_CASE( "Node<4> Initialization", "[main]" )
{
    constexpr int GridSize = constants::FIFTEEN_PUZZLE_SIZE;
    SECTION("Unsolved", "[some_details]")
    {
        std::vector<int> state {14, 8, 4, 9, 1, 6, 5, constants::EMPTY, 12, 13, 3, 15, 7, 2, 11, 10};
        Node<GridSize> n(state);

        // tests all its members upon initialization
        REQUIRE (std::ranges::equal(static_cast<const Tester<GridSize>&>(n).GetState(), state));
        REQUIRE (static_cast<const Tester<GridSize>&>(n).GetPosX() == 7);
        REQUIRE (n.GetManhattanDistance() == 36);
        REQUIRE (n.GetHashValue() == hash_range(std::span(state)));
        REQUIRE (n.IsSolved() == false);
    }

    SECTION("Solved", "[some_details]")
    {
        std::vector<int> state {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, constants::EMPTY};
        Node<GridSize> n(state);

        // tests all its members upon initialization
        REQUIRE (std::ranges::equal(static_cast<const Tester<GridSize>&>(n).GetState(), state));
        REQUIRE (static_cast<const Tester<GridSize>&>(n).GetPosX() == 15);
        REQUIRE (n.GetManhattanDistance() == 0);
        REQUIRE (n.GetHashValue() == hash_range(std::span(state)));
        REQUIRE (n.IsSolved());
    }
}

TEST_CASE( "Available Moves <3>", "[main]" )
{
    constexpr int GridSize = constants::EIGHT_PUZZLE_SIZE;

    // initializes all possible positions that the empty puzzle can be in
    Node<GridSize> middle({1, 2, 3, 4, constants::EMPTY, 6, 7, 5, 8});
    Node<GridSize> topLeft({constants::EMPTY, 2, 3, 4, 1, 6, 7, 5, 8});
    Node<GridSize> topRight({1, 2, constants::EMPTY, 4, 3, 6, 7, 5, 8});
    Node<GridSize> middleLeft({1, 2, 3, constants::EMPTY, 4, 6, 7, 5, 8});
    Node<GridSize> middleRight({1, 2, 3, 4, 6, constants::EMPTY, 7, 5, 8});
    Node<GridSize> bottomLeft({1, 2, 3, 4, 7, 6, constants::EMPTY, 5, 8});
    Node<GridSize> bottomRight({1, 2, 3, 4, 8, 6, 7, 5, constants::EMPTY});
    Node<GridSize> centerTop({1, constants::EMPTY, 3, 4, 2, 6, 7, 5, 8});
    Node<GridSize> centerBottom({1, 2, 3, 4, 5, 6, 7, constants::EMPTY, 8});

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

TEST_CASE( "Available Moves <4>", "[main]" )
{
    constexpr int GridSize = constants::FIFTEEN_PUZZLE_SIZE;

    // initializes all possible positions that the empty puzzle can be in
    Node<GridSize> middle({1, 2, 3, 4, 5, constants::EMPTY, 7, 8, 9, 10, 11, 12, 13, 14, 15, 6});
    Node<GridSize> topLeft({constants::EMPTY, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1});
    Node<GridSize> topRight({1, 2, 3, constants::EMPTY, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 4});
    Node<GridSize> middleLeft({1, 2, 3, 4, constants::EMPTY, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 5});
    Node<GridSize> middleRight({1, 2, 3, 4, 5, 6, 7, constants::EMPTY, 9, 10, 11, 12, 13, 14, 15, 8});
    Node<GridSize> bottomLeft({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, constants::EMPTY, 14, 15, 13});
    Node<GridSize> bottomRight({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, constants::EMPTY});
    Node<GridSize> centerTop({1, constants::EMPTY, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 2});
    Node<GridSize> centerBottom({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, constants::EMPTY, 15, 14});

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

TEST_CASE( "Get Next State <3>", "[main]" )
{
    constexpr int GridSize = constants::EIGHT_PUZZLE_SIZE;

    // initializes the start state
    Node<GridSize> middle({3, 6, 4, 8, constants::EMPTY, 5, 7, 2, 1});
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
        auto [childState, childPosX] = middle.GetNextState(*itr);

        REQUIRE (std::ranges::equal(childState, actualRightLayout));
        REQUIRE (childPosX == actualRightPosX);
    }

    ++itr;
    SECTION("Up", "[some_details]")
    {
        auto [childState, childPosX] = middle.GetNextState(*itr);

        REQUIRE (std::ranges::equal(childState, actualUpLayout));
        REQUIRE (childPosX == actualUpPosX);

    }

    ++itr;
    SECTION("Left", "[some_details]")
    {
        auto [childState, childPosX] = middle.GetNextState(*itr);

        REQUIRE (std::ranges::equal(childState, actualLeftLayout));
        REQUIRE (childPosX == actualLeftPosX);

    }

    ++itr;
    SECTION("Down", "[some_details]")
    {
        auto [childState, childPosX] = middle.GetNextState(*itr);

        REQUIRE (std::ranges::equal(childState, actualDownLayout));
        REQUIRE (childPosX == actualDownPosX);
    }
}

TEST_CASE( "Get Next State <4>", "[main]" )
{
    constexpr int GridSize = constants::FIFTEEN_PUZZLE_SIZE;

    // initializes the start state
    Node<GridSize> middle({1, 2, 3, 4, 5, constants::EMPTY, 7, 8, 9, 10, 11, 12, 13, 14, 15, 6});
    constexpr int acutalPosX = 5;

    // grabs the available moves
    auto movesMiddle = middle.AvailableMoves();

    // the actual layouts after the moves
    constexpr std::array actualRightLayout {1, 2, 3, 4, 5, 7, constants::EMPTY, 8, 9, 10, 11, 12, 13, 14, 15, 6};
    constexpr std::array actualUpLayout {1, constants::EMPTY, 3, 4, 5, 2, 7, 8, 9, 10, 11, 12, 13, 14, 15, 6};
    constexpr std::array actualLeftLayout {1, 2, 3, 4, constants::EMPTY, 5, 7, 8, 9, 10, 11, 12, 13, 14, 15, 6};
    constexpr std::array actualDownLayout {1, 2, 3, 4, 5, 10, 7, 8, 9, constants::EMPTY, 11, 12, 13, 14, 15, 6};

    // the actual positions of X after the moves
    constexpr int actualRightPosX = acutalPosX + 1;
    constexpr int actualUpPosX = acutalPosX - constants::FIFTEEN_PUZZLE_SIZE;
    constexpr int actualLeftPosX = acutalPosX - 1;
    constexpr int actualDownPosX = acutalPosX + constants::FIFTEEN_PUZZLE_SIZE;

    // test cases
    auto itr = movesMiddle.begin();
    SECTION("Right", "[some_details]")
    {
        auto [childState, childPosX] = middle.GetNextState(*itr);

        REQUIRE (std::ranges::equal(childState, actualRightLayout));
        REQUIRE (childPosX == actualRightPosX);
    }

    ++itr;
    SECTION("Up", "[some_details]")
    {
        auto [childState, childPosX] = middle.GetNextState(*itr);

        REQUIRE (std::ranges::equal(childState, actualUpLayout));
        REQUIRE (childPosX == actualUpPosX);

    }

    ++itr;
    SECTION("Left", "[some_details]")
    {
        auto [childState, childPosX] = middle.GetNextState(*itr);

        REQUIRE (std::ranges::equal(childState, actualLeftLayout));
        REQUIRE (childPosX == actualLeftPosX);

    }

    ++itr;
    SECTION("Down", "[some_details]")
    {
        auto [childState, childPosX] = middle.GetNextState(*itr);

        REQUIRE (std::ranges::equal(childState, actualDownLayout));
        REQUIRE (childPosX == actualDownPosX);
    }
}

TEST_CASE( "Operators <3>", "[main]" )
{
    constexpr int GridSize = constants::EIGHT_PUZZLE_SIZE;

    std::vector<int> layout1 {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
    Node<GridSize> n1(layout1);

    std::vector<int> layout2 {1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY};
    Node<GridSize> n2(layout2);

    SECTION("Equal To", "[some_details]")
    {
        REQUIRE ((n2 == n1) == false);
    }

    SECTION("Not Equal To", "[some_details]")
    {
        REQUIRE ((n2 != n1));
    }
}

TEST_CASE( "Operators <4>", "[main]" )
{
    constexpr int GridSize = constants::FIFTEEN_PUZZLE_SIZE;

    std::vector<int> layout1 {1, 2, 3, 4, 5, 6, 7, 5, 9, 10, 11, 12, 13, 8, 14, 15, constants::EMPTY};
    Node<GridSize> n1(layout1);

    std::vector<int> layout2 {1, 2, 3, 4, 5, 6, 7, 5, 9, 10, 11, constants::EMPTY, 13, 14, 15, 12, 8};
    Node<GridSize> n2(layout2);

    SECTION("Equal To", "[some_details]")
    {
        REQUIRE ((n2 == n1) == false);
    }

    SECTION("Not Equal To", "[some_details]")
    {
        REQUIRE ((n2 != n1));
    }
}

TEST_CASE( "Calculate the Number of Inversions <3>", "[main]" )
{
    constexpr int GridSize = constants::EIGHT_PUZZLE_SIZE;

    SECTION("Even Number of Inversions", "[some_details]")
    {
        std::vector<int> layout {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
        Node<GridSize> n(layout);
        REQUIRE (n.GetInversion() == 4);
    }

    SECTION("Odd Number of Inversions", "[some_details]")
    {
        std::vector<int> layout {8, 1, 2, constants::EMPTY, 4, 3, 7, 6, 5};
        Node<GridSize> n(layout);
        REQUIRE (n.GetInversion() == 11);
    }
}

TEST_CASE( "Calculate the Number of Inversions <4>", "[main]" )
{
    constexpr int GridSize = constants::FIFTEEN_PUZZLE_SIZE;

    SECTION("Even Number of Inversions", "[some_details]")
    {
        std::vector<int> layout {14, 8, 4, 9, 1, 6, 5, constants::EMPTY, 12, 13, 3, 15, 7, 2, 11, 10};
        Node<GridSize> n(layout);
        REQUIRE (n.GetInversion() == 51);
    }

    SECTION("Odd Number of Inversions", "[some_details]")
    {
        std::vector<int> layout {14, 8, 4, 9, 1, 6, 5, 10, 12, 13, 3, 15, 7, 2, 11, constants::EMPTY};
        Node<GridSize> n(layout);
        REQUIRE (n.GetInversion() == 50);
    }
}

TEST_CASE( "Calculate If the Puzzle is Insolvable <4>", "[main]" )
{
    constexpr int GridSize = constants::FIFTEEN_PUZZLE_SIZE;

    SECTION("Solvable", "[some_details]")
    {
        std::vector<int> layout {7, 2, 9, 6, 8, constants::EMPTY, 3, 13, 4, 1, 10, 5, 14, 15, 11, 12};
        Node<GridSize> n(layout);
        REQUIRE (n.Insolvable() == false);
    }

    SECTION("Insolvable", "[some_details]")
    {
        std::vector<int> layout {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, constants::EMPTY};
        Node<GridSize> n(layout);
        REQUIRE (n.Insolvable());
    }
}

TEST_CASE( "Calculate the Depth <3>", "[main]" )
{
    constexpr int GridSize = constants::EIGHT_PUZZLE_SIZE;

    std::vector<int> state {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};

    SECTION("Depth 0", "[some_details]")
    {
        Node<GridSize> n(state, 2, 0);
        std::vector<Node<GridSize>> childredNodes = n.GetChildrenNodes();
        auto itr = childredNodes.begin();

        REQUIRE (itr++->GetDepth() == 1);
        REQUIRE (itr->GetDepth() == 1);
    }

    SECTION("Depth 99", "[some_details]")
    {
        Node<GridSize> n(state, 2, 99);
        std::vector<Node<GridSize>> childredNodes = n.GetChildrenNodes();
        auto itr = childredNodes.begin();

        REQUIRE (itr++->GetDepth() == 100);
        REQUIRE (itr->GetDepth() == 100);
    }

    SECTION("Depth of a Child", "[some_details]")
    {
        constexpr int parentDepth = 45;
        Node<GridSize> n(state, 2, parentDepth);
        constexpr int childrenDepth = parentDepth + 1;
        constexpr int grandchildrenDepth = parentDepth + 2;
        std::vector<Node<GridSize>> childredNodes = n.GetChildrenNodes();
        auto itr = childredNodes.begin();

        REQUIRE (itr->GetDepth() == childrenDepth);
        REQUIRE (itr++->GetChildrenNodes().front().GetDepth() == grandchildrenDepth);
        REQUIRE (itr->GetDepth() == childrenDepth);
        REQUIRE (itr++->GetChildrenNodes().front().GetDepth() == grandchildrenDepth);
    }
}

TEST_CASE( "Calculate the Depth <4>", "[main]" )
{
    constexpr int GridSize = constants::FIFTEEN_PUZZLE_SIZE;

    std::vector<int> state {14, 8, 4, 9, 1, 6, 5, 10, 12, 13, 3, 15, 7, 2, 11, constants::EMPTY};

    SECTION("Depth 0", "[some_details]")
    {
        Node<GridSize> n(state, 2, 0);
        std::vector<Node<GridSize>> childredNodes = n.GetChildrenNodes();
        auto itr = childredNodes.begin();

        REQUIRE (itr++->GetDepth() == 1);
        REQUIRE (itr->GetDepth() == 1);
    }

    SECTION("Depth 99", "[some_details]")
    {
        Node<GridSize> n(state, 2, 99);
        std::vector<Node<GridSize>> childredNodes = n.GetChildrenNodes();
        auto itr = childredNodes.begin();

        REQUIRE (itr++->GetDepth() == 100);
        REQUIRE (itr->GetDepth() == 100);
    }

    SECTION("Depth of a Child", "[some_details]")
    {
        constexpr int parentDepth = 45;
        Node<GridSize> n(state, 2, parentDepth);
        constexpr int childrenDepth = parentDepth + 1;
        constexpr int grandchildrenDepth = parentDepth + 2;
        std::vector<Node<GridSize>> childredNodes = n.GetChildrenNodes();
        auto itr = childredNodes.begin();

        REQUIRE (itr->GetDepth() == childrenDepth);
        REQUIRE (itr++->GetChildrenNodes().front().GetDepth() == grandchildrenDepth);
        REQUIRE (itr->GetDepth() == childrenDepth);
        REQUIRE (itr++->GetChildrenNodes().front().GetDepth() == grandchildrenDepth);
    }
}

TEST_CASE( "Get Total Cost <3>", "[main]" )
{
    constexpr int GridSize = constants::EIGHT_PUZZLE_SIZE;

    SECTION("State 1", "[some_details]")
    {
        std::vector<int> layout {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
        Node<GridSize> n(layout);
        REQUIRE (n.GetTotalCost() == n.GetManhattanDistance() + n.GetDepth());
    }

    SECTION("State 2", "[some_details]")
    {
        std::vector<int> layout {8, 1, 2, constants::EMPTY, 4, 3, 7, 6, 5};
        Node<GridSize> n(layout);
        REQUIRE (n.GetTotalCost() == n.GetManhattanDistance() + n.GetDepth());
    }
}

TEST_CASE( "Get Total Cost <4>", "[main]" )
{
    constexpr int GridSize = constants::FIFTEEN_PUZZLE_SIZE;

    SECTION("State 1", "[some_details]")
    {
        std::vector<int> layout {14, 8, 4, 9, 1, 6, 5, constants::EMPTY, 12, 13, 3, 15, 7, 2, 11, 10};
        Node<GridSize> n(layout);
        REQUIRE (n.GetTotalCost() == n.GetManhattanDistance() + n.GetDepth());
    }

    SECTION("State 2", "[some_details]")
    {
        std::vector<int> layout {14, 8, 4, 9, 1, 6, 5, 10, 12, 13, 3, 15, 7, 2, 11, constants::EMPTY};
        Node<GridSize> n(layout);
        REQUIRE (n.GetTotalCost() == n.GetManhattanDistance() + n.GetDepth());
    }
}

TEST_CASE( "Find the Move Between Two States <3>", "[main]" )
{
    constexpr int GridSize = constants::EIGHT_PUZZLE_SIZE;
    std::vector<int> layout {8, 1, 2, 4, constants::EMPTY, 3, 7, 6, 5};
    Node<GridSize> n(layout);

    std::vector<Node<GridSize>> children = n.GetChildrenNodes();
    auto itr = children.begin();

    SECTION("Right", "[some_details]")
    {
        int dir = itr->FindUndoMove(n);
        REQUIRE(dir == constants::RIGHT);
    }

    ++itr;
    SECTION("Up", "[some_details]")
    {
        int dir = itr->FindUndoMove(n);
        REQUIRE(dir == constants::UP);
    }

    ++itr;
    SECTION("Left", "[some_details]")
    {
        int dir = itr->FindUndoMove(n);
        REQUIRE(dir == constants::LEFT);
    }

    ++itr;
    SECTION("Down", "[some_details]")
    {
        int dir = itr->FindUndoMove(n);
        REQUIRE(dir == constants::DOWN);
    }
}
