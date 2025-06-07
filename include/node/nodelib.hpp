#ifndef INCLUDE_NODE_NODELIB_H_
#define INCLUDE_NODE_NODELIB_H_

#include <vector>   // std::vector
#include <cstdlib>  // std::size_t
#include <tuple>    // std::tuple

class Node
{
public:
    Node() = delete;
    Node(std::vector<int> input);
    Node(std::vector<int> input, unsigned long d);
    Node(std::vector<int> input, int posX);
    Node(std::vector<int> input, int posX, unsigned long d);
    ~Node() = default;

    std::vector<int> AvailableMoves() const;

    std::vector<Node> GetChildrenNodes(unsigned long) const;

    std::tuple<std::vector<int>, int> GetNextLayout(int dir) const;

    int GetManhattanDistance() const;

    std::size_t GetHashValue() const;

    /// @brief Gets the depth of the node
    /// @return The depth
    unsigned long GetDepth() const;

    void Print() const;

    bool operator==(const Node& rhs) const;

    bool operator!=(const Node& rhs) const;

    bool IsSolved() const;

private:
    void CalculateManhattanDistance();

protected:
    /// @brief The state of the node
    std::vector<int> state;

    /// @brief The position of The empty piece
    int posX;

    /// @brief The Manhattan distance
    int manhattanDistance;

    /// @brief The hash value
    std::size_t hashValue;

    /// @brief The depth of the node
    unsigned long depth;
};

#endif // INCLUDE_NODE_NODELIB_H_
