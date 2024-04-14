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
    Node(std::vector<int> input, int posX);
    ~Node() = default;

    std::vector<int> AvailableMoves() const;

    std::vector<Node> GetChildrenNodes() const;

    std::tuple<std::vector<int>, int> GetNextLayout(int dir) const;

    int GetCurrentManhattanDistance() const;

    std::size_t GetCurrentHashValue() const;

    void Print() const;

    bool operator<(const Node& rhs) const;

    bool operator>(const Node& rhs) const;

    bool operator==(const Node& rhs) const;

    bool operator!=(const Node& rhs) const;

    bool IsSolved() const;

private:
    void CalculateManhattanDistance();

protected:
    std::vector<int> layout;
    int posX;
    int manhattanDistance;
    std::size_t hashValue;
};

#endif // INCLUDE_NODE_NODELIB_H_
