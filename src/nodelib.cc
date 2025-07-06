#include <span> // std::span
#include <algorithm> // std::ranges::find
#include <memory> // std::shared_ptr, std::make_shared
#include <ranges>   // std::views::iota
#include <numeric>  // std::reduce
#include <initializer_list>  // std::reduce
#include <fmt/core.h>   // fmt::print

#include "math/mathlib.hpp" // hash_range
#include "node/nodelib.hpp" // Node
#include "constants/constantslib.hpp"   // constants::RIGHT, constants::LEFT, etc.

Node::Node(std::vector<int> input)
    : state_(input),
      posX_(std::ranges::find(input, constants::EMPTY) - input.begin()),
      hashValue_(hash_range(std::span(state_))),
      depth_(0),
      parent_(nullptr),
      move_(-1)
{
    CalculateManhattanDistance();
}

Node::Node(std::vector<int> input, int posX) : state_(input), posX_(posX), hashValue_(hash_range(std::span(state_))), depth_(0)
{
    CalculateManhattanDistance();
}

Node::Node(std::vector<int> input, int posX, unsigned long d, std::shared_ptr<const Node> p, short m) : state_(input), posX_(posX), hashValue_(hash_range(std::span(state_))), depth_(d), parent_(p), move_(m)
{
    CalculateManhattanDistance();
}

std::vector<short> Node::AvailableMoves() const
{
    std::vector<short> ret;
    ret.reserve(4);

    int xRow = posX_ / constants::EIGHT_PUZZLE_SIZE;
    int xCol = posX_ % constants::EIGHT_PUZZLE_SIZE;

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

std::vector<Node> Node::GetChildNodes(unsigned long curDepth, std::shared_ptr<const Node> p) const
{
    std::vector<Node> children;
    children.reserve(4);

    std::vector<short> moves = AvailableMoves();

    for(const short& move : moves)
    {
        auto [childLayout, childPosX] = GetNextLayout(move);
        children.emplace_back(childLayout, childPosX, curDepth + 1, p, move);
    }

    // NOTE: due to the advent of copy elision, this vector of Nodes will not be copied
    return children;
}

std::tuple<std::vector<int>, int> Node::GetNextLayout(short dir) const
{
    std::vector<int> newLayout = state_;
    int newPosX = posX_;

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

unsigned int Node::GetManhattanDistance() const noexcept
{
    return manhattanDistance_;
}

std::size_t Node::GetHashValue() const noexcept
{
    return hashValue_;
}

unsigned int Node::GetDepth() const noexcept
{
    return depth_;
}

unsigned int Node::GetTotalCost() const noexcept
{
    return GetManhattanDistance() + GetDepth();
}

void Node::Print() const
{
    std::size_t cnt = 0;
    for (const auto& ele : state_)
    {
        // prints "x" if the value if equals to "constants::EMPTY"
        if (ele != constants::EMPTY)
        {
            fmt::print("{} ", ele);
        }
        else
        {
            fmt::print("x ");
        }

        // increments the value of cnt and then be checked
        if (++cnt % constants::EIGHT_PUZZLE_SIZE == 0)
        {
            fmt::print("\n");
        }
    }
}

bool Node::IsSolved() const noexcept
{
    return (manhattanDistance_ == 0) ? true : false;
}

std::shared_ptr<const Node> Node::GetParent() const noexcept
{
    return parent_;
}

short Node::GetMove() const noexcept
{
    return move_;
}

void Node::CalculateManhattanDistance()
{
    manhattanDistance_ = std::reduce
    (
        std::views::iota(0, constants::EIGHT_PUZZLE_NUM).begin(),
        std::views::iota(0, constants::EIGHT_PUZZLE_NUM).end(),
        0,
        [&](int acc, int i)
        {
            if (state_[i] == constants::EMPTY)
                return acc;

            int curRow = (state_[i] - 1) / constants::EIGHT_PUZZLE_SIZE;
            int curCol = (state_[i] - 1) % constants::EIGHT_PUZZLE_SIZE;
            int goalRow = i / constants::EIGHT_PUZZLE_SIZE;
            int goalCol = i % constants::EIGHT_PUZZLE_SIZE;

            return acc + std::abs(goalRow - curRow) + std::abs(goalCol - curCol);
        }
    );
}

void Node::CalculateLinearConflict()
{

}
