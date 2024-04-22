#include <iostream> // std::cout
#include <span> // std::span
#include <algorithm> // std::ranges::find

#include "node/nodelib.hpp"
#include "constants/constantslib.hpp"
#include "math/mathlib.hpp"

Node::Node(std::vector<int> input) : state(input), depth(0)
{
    hashValue = hash_range(std::span(state));
    posX = std::ranges::find(input, constants::EMPTY) - input.begin();
    CalculateManhattanDistance();
}

Node::Node(std::vector<int> input, int posX, int depth) : state(input), posX(posX), depth(depth)
{
    hashValue = hash_range(std::span(input));
    CalculateManhattanDistance();
}

std::vector<int> Node::AvailableMoves() const
{
    std::vector<int> ret;

    auto xDv = std::div(posX, constants::EIGHT_PUZZLE_SIZE);
    int xRow = xDv.quot;
    int xCol = xDv.rem;

    // constants::RIGHT
    if (xCol + 1 < constants::EIGHT_PUZZLE_SIZE)
    {
        ret.push_back(constants::RIGHT);
    }

    // constants::UP
    if (xRow >= 1)
    {
        ret.push_back(constants::UP);
    }

    // constants::LEFT
    if (xCol >= 1)
    {
        ret.push_back(constants::LEFT);
    }

    // constants::DOWN
    if (xRow + 1 < constants::EIGHT_PUZZLE_SIZE)
    {
        ret.push_back(constants::DOWN);
    }


    return ret;
}

std::vector<Node> Node::GetChildrenNodes() const
{
    std::vector<Node> children;

    std::vector<int> moves = AvailableMoves();

    for(const int& move : moves)
    {
        auto [childState, childPosX] = GetNextState(move);
        children.emplace_back(childState, childPosX, depth + 1);
    }

    return children;
}

std::tuple<std::vector<int>, int> Node::GetNextState(int dir) const
{
    std::vector<int> newState = state;
    int newPosX = posX;

    // swaps the piece
    switch (dir)
    {
    case constants::LEFT:
        std::swap(newState[newPosX], newState[newPosX - 1]);
        newPosX -= 1;
        break;

    case constants::RIGHT:
        std::swap(newState[newPosX], newState[newPosX + 1]);
        newPosX += 1;
        break;

    case constants::UP:
        std::swap(newState[newPosX], newState[newPosX - constants::EIGHT_PUZZLE_SIZE]);
        newPosX -= constants::EIGHT_PUZZLE_SIZE;
        break;

    case constants::DOWN:
        std::swap(newState[newPosX], newState[newPosX + constants::EIGHT_PUZZLE_SIZE]);
        newPosX += constants::EIGHT_PUZZLE_SIZE;
        break;

    default:
        break;
    }

    return std::tuple<std::vector<int>, int>{newState, newPosX};
}

int Node::GetManhattanDistance() const
{
    return manhattanDistance;
}

std::size_t Node::GetHashValue() const
{
    return hashValue;
}

void Node::Print() const
{
    std::size_t cnt = 0;
    for (const auto& ele : state)
    {
        // prints "x" if the value if equals to "constants::EMPTY"
        if (ele != constants::EMPTY)
        {
            std::cout << (int)ele << " ";
        }
        else
        {
            std::cout << "x ";
        }

        // increments the value of cnt and then be checked
        if (++cnt % constants::EIGHT_PUZZLE_SIZE == 0)
        {
            std::cout << "\n";
        }
    }
}

bool Node::operator==(const Node &rhs) const
{
    return hashValue == rhs.GetHashValue();
}

bool Node::operator!=(const Node &rhs) const
{
    return hashValue != rhs.GetHashValue();
}

bool Node::IsSolved() const
{
    return (manhattanDistance == 0) ? true : false;
}

void Node::CalculateManhattanDistance()
{
    int ptr = 0;
    manhattanDistance = std::accumulate(state.begin(), state.end(), 0,
        [&](int s, int v)
        {
            int diff = 0;

            // checks if the element is valid
            if (v != constants::EMPTY)
            {
                // finds the goal coordinate of the element
                auto goalDv = std::div(v - 1, constants::EIGHT_PUZZLE_SIZE);
                int goalRow = goalDv.quot;
                int goalCol = goalDv.rem;

                // finds the current coordinate of the element
                auto curDv = std::div(ptr, constants::EIGHT_PUZZLE_SIZE);
                int curRow = curDv.quot;
                int curCol = curDv.rem;

                // find the Manhattan distance of the two
                diff = std::abs(goalCol - curCol) + std::abs(goalRow - curRow);
            }

            ++ptr;

            return s += diff;
        });
}

int Node::GetDepth() const
{
    return depth;
}