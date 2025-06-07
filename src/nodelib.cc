#include <iostream> // std::cout
#include <span> // std::span
#include <algorithm> // std::ranges::find

#include "node/nodelib.hpp"
#include "constants/constantslib.hpp"
#include "math/mathlib.hpp"

Node::Node(std::vector<int> input)
    : state(input),
      posX(std::ranges::find(input, constants::EMPTY) - input.begin()),
      hashValue(hash_range(std::span(state))),
      depth(0)
{
    CalculateManhattanDistance();
}

Node::Node(std::vector<int> input, unsigned long d)
    : state(input),
    posX(std::ranges::find(input, constants::EMPTY) - input.begin()),
    hashValue(hash_range(std::span(state))),
    depth(d)
{
    CalculateManhattanDistance();
}

Node::Node(std::vector<int> input, int posX) : state(input), posX(posX), depth(0)
{
    hashValue = hash_range(std::span(input));
    CalculateManhattanDistance();
}

Node::Node(std::vector<int> input, int posX, unsigned long d) : state(input), posX(posX), depth(d)
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

std::vector<Node> Node::GetChildrenNodes(unsigned long curDepth) const
{
    std::vector<Node> children;

    std::vector<int> moves = AvailableMoves();

    for(const int& move : moves)
    {
        auto [childLayout, childPosX] = GetNextLayout(move);
        children.emplace_back(childLayout, childPosX, curDepth + 1);
    }

    return children;
}

std::tuple<std::vector<int>, int> Node::GetNextLayout(int dir) const
{
    std::vector<int> newLayout = state;
    int newPosX = posX;

    // swaps the piece
    switch (dir)
    {
    case constants::LEFT:
        std::swap(newLayout[newPosX], newLayout[newPosX - 1]);
        newPosX -= 1;
        break;

    case constants::RIGHT:
        std::swap(newLayout[newPosX], newLayout[newPosX + 1]);
        newPosX += 1;
        break;

    case constants::UP:
        std::swap(newLayout[newPosX], newLayout[newPosX - constants::EIGHT_PUZZLE_SIZE]);
        newPosX -= constants::EIGHT_PUZZLE_SIZE;
        break;

    case constants::DOWN:
        std::swap(newLayout[newPosX], newLayout[newPosX + constants::EIGHT_PUZZLE_SIZE]);
        newPosX += constants::EIGHT_PUZZLE_SIZE;
        break;

    default:
        break;
    }

    return std::tuple<std::vector<int>, int>{newLayout, newPosX};
}

int Node::GetManhattanDistance() const
{
    return manhattanDistance;
}

std::size_t Node::GetHashValue() const
{
    return hashValue;
}

unsigned long Node::GetDepth() const
{
    return depth;
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
    return manhattanDistance == rhs.GetManhattanDistance();
}

bool Node::operator!=(const Node &rhs) const
{
    return manhattanDistance != rhs.GetManhattanDistance();
}

bool Node::IsSolved() const
{
    return (manhattanDistance == 0) ? true : false;
}

void Node::CalculateManhattanDistance()
{
    manhattanDistance = 0;
    for (auto i = 0; i < constants::EIGHT_PUZZLE_NUM; ++i)
    {
        if (state[i] != constants::EMPTY)
        {
            int curRow = (state[i] - 1) / constants::EIGHT_PUZZLE_SIZE;
            int curCol = (state[i] - 1) % constants::EIGHT_PUZZLE_SIZE;

            int goalRow = i / constants::EIGHT_PUZZLE_SIZE;
            int goalCol = i % constants::EIGHT_PUZZLE_SIZE;

            manhattanDistance += (std::abs(goalRow - curRow) + std::abs(goalCol - curCol));
        }
    }
}
