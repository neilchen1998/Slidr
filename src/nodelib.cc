#include <iostream> // std::cout
#include <span> // std::span
#include <algorithm> // std::ranges::find
#include <ranges> // std::ranges

#include "node/nodelib.hpp"
#include "constants/constantslib.hpp"
#include "math/mathlib.hpp"

template class Node<constants::EIGHT_PUZZLE_SIZE>;
template class Node<constants::FIFTEEN_PUZZLE_SIZE>;

template <int GameType>
Node<GameType>::Node(std::vector<int> input) : state(input), depth(0), inversion(0)
{
    hashValue = hash_range(std::span(state));
    posX = std::ranges::find(input, constants::EMPTY) - input.begin();
    CalculateManhattanDistance();
    CalculateInversion();
}

template <int GameType>
Node<GameType>::Node(std::vector<int> input, int posX, int depth) : state(input), posX(posX), depth(depth), inversion(0)
{
    hashValue = hash_range(std::span(input));
    CalculateManhattanDistance();
    CalculateInversion();
}

template <int GameType>
std::vector<int> Node<GameType>::AvailableMoves() const
{
    std::vector<int> ret;

    auto xDv = std::div(posX, GameType);
    int xRow = xDv.quot;
    int xCol = xDv.rem;

    // constants::RIGHT
    if (xCol + 1 < GameType)
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
    if (xRow + 1 < GameType)
    {
        ret.push_back(constants::DOWN);
    }

    return ret;
}

template <int GameType>
std::vector<Node<GameType>> Node<GameType>::GetChildrenNodes() const
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

template <int GameType>
std::tuple<std::vector<int>, int> Node<GameType>::GetNextState(int dir) const
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
        std::swap(newState[newPosX], newState[newPosX - GameType]);
        newPosX -= GameType;
        break;

    case constants::DOWN:
        std::swap(newState[newPosX], newState[newPosX + GameType]);
        newPosX += GameType;
        break;

    default:
        break;
    }

    return std::tuple<std::vector<int>, int>{newState, newPosX};
}

template <int GameType>
int Node<GameType>::GetManhattanDistance() const
{
    return manhattanDistance;
}

template <int GameType>
std::size_t Node<GameType>::GetHashValue() const
{
    return hashValue;
}

template <>
void Node<constants::EIGHT_PUZZLE_SIZE>::Print() const
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

template <>
void Node<constants::FIFTEEN_PUZZLE_SIZE>::Print() const
{
    std::size_t cnt = 0;
    for (const auto& ele : state)
    {
        // prints "x" if the value if equals to "constants::EMPTY"
        if (ele < 10)
        {
            std::cout << " " << (int)ele << " ";
        }
        else if (ele != constants::EMPTY)
        {
            std::cout << (int)ele << " ";
        }
        else
        {
            std::cout << " x ";
        }

        // increments the value of cnt and then be checked
        if (++cnt % constants::FIFTEEN_PUZZLE_SIZE == 0)
        {
            std::cout << "\n";
        }
    }
}

template <int GameType>
bool Node<GameType>::operator==(const Node &rhs) const
{
    return hashValue == rhs.GetHashValue();
}

template <int GameType>
bool Node<GameType>::operator!=(const Node &rhs) const
{
    return hashValue != rhs.GetHashValue();
}

template <int GameType>
bool Node<GameType>::IsSolved() const
{
    return (manhattanDistance == 0) ? true : false;
}

template <int GameType>
void Node<GameType>::CalculateManhattanDistance()
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
                auto goalDv = std::div(v - 1, GameType);
                int goalRow = goalDv.quot;
                int goalCol = goalDv.rem;

                // finds the current coordinate of the element
                auto curDv = std::div(ptr, GameType);
                int curRow = curDv.quot;
                int curCol = curDv.rem;

                // find the Manhattan distance of the two
                diff = std::abs(goalCol - curCol) + std::abs(goalRow - curRow);
            }

            ++ptr;

            return s += diff;
        });
}

template <int GameType>
void Node<GameType>::CalculateInversion()
{
    // loop through the entire vector
    auto right = state.cbegin();
    while (right != state.cend())
    {
        // disregard 'empty' element
        if (*right != constants::EMPTY)
        {
            // count the number of inversions between the first element to the current one
            inversion += std::ranges::count_if(state.cbegin(), right, [&](int i)
            {
                // only cares when the element is greater than the current one and disregard 'empty' element
                return i > *right && i != constants::EMPTY;
            });
        }
        
        ++right;
    }
}

template <int GameType>
int Node<GameType>::GetDepth() const
{
    return depth;
}

template <int GameType>
int Node<GameType>::GetInversion() const
{
    return inversion;
}

template <int GameType>
void Node<GameType>::UpdateDepth(int newDepth)
{
    depth = newDepth;
}

template <int GameType>
int Node<GameType>::GetTotalCost() const
{
    return GetManhattanDistance() + GetDepth();
}

template <>
int Node<constants::FIFTEEN_PUZZLE_SIZE>::GetTotalCost() const
{
    int ret = (GetManhattanDistance() + GetDepth());

    // // approach 1
    // constexpr std::array cache {1, 2, 3, 4, 5, 6, 7, 8};
    // if (std::ranges::equal(state | std::ranges::views::take(8), cache))
    // {
    //     ret -= 10;
    // }
    // else if (std::ranges::equal(state | std::ranges::views::take(4), cache | std::ranges::views::take(4)))
    // {
    //     ret -= 5;
    // }

    // // // approach 2
    // // if (SecondStageCompleted())
    // // {
    // //     ret -= 10;
    // // }
    // // else if (FirstStageCompleted())
    // // {
    // //     ret -= 5;
    // // }

    return ret;
}

template <>
bool Node<constants::EIGHT_PUZZLE_SIZE>::Insolvable() const
{
    return (GetInversion() % 2) ? true : false;
}

/// @brief Checks whether the given puzzle is insolvable or not
/// @return the puzzle is insolvable
template <>
bool Node<constants::FIFTEEN_PUZZLE_SIZE>::Insolvable() const
{
    // source: https://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/#

    // whether the number of the inversion is even
    bool condition1 = GetInversion() % 2;

    // whether the empty puzzle is located in the an even row (counted from the bottom)
    int ptr = std::ranges::find(state, constants::EMPTY) - state.begin();
    int curRow = std::div(ptr, constants::FIFTEEN_PUZZLE_SIZE).quot;
    bool condition2 = (constants::EMPTY - curRow) % 2;

    return condition1 ^ condition2;
}
