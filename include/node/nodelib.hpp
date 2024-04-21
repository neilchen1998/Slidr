#ifndef INCLUDE_NODE_NODELIB_H_
#define INCLUDE_NODE_NODELIB_H_

#include <vector>   // std::vector
#include <cstdlib>  // std::size_t
#include <tuple>    // std::tuple

class Node
{
public:
    Node() = default;
    Node(std::vector<int> input);
    explicit Node(std::vector<int> input, int posX, int depth);
    ~Node() = default;

    std::vector<int> AvailableMoves() const;

    std::vector<Node> GetChildrenNodes() const;

    std::tuple<std::vector<int>, int> GetNextState(int dir) const;

    int GetCurrentManhattanDistance() const;

    std::size_t GetCurrentHashValue() const;

    void Print() const;

    bool operator<(const Node& rhs) const;

    bool operator>(const Node& rhs) const;

    bool operator==(const Node& rhs) const;

    bool operator!=(const Node& rhs) const;

    bool IsSolved() const;

    int GetDepth() const;

private:
    void CalculateManhattanDistance();

protected:
    /// @brief the state of the node
    std::vector<int> state;

    /// @brief the position of the empty piece
    int posX;

    /// @brief the Manhattan distance
    int manhattanDistance;

    /// @brief the hash value
    std::size_t hashValue;

    /// @brief the depth value
    int depth;
};

#endif // INCLUDE_NODE_NODELIB_H_
