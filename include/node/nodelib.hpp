#ifndef INCLUDE_NODE_NODELIB_H_
#define INCLUDE_NODE_NODELIB_H_

#include <vector>   // std::vector
#include <cstdlib>  // std::size_t
#include <tuple>    // std::tuple
#include <memory.h> // std::shared_ptr

class Node
{
public:
    Node() = delete;
    Node(std::vector<int> input);
    Node(std::vector<int> input, unsigned long d);
    Node(std::vector<int> input, int posX);
    Node(std::vector<int> input, int posX, unsigned long d);
    Node(std::vector<int> input, int posX, unsigned long d, std::shared_ptr<const Node> p);
    ~Node() = default;

    /// @brief Gets all the available moves
    /// @return A vectors contains all the available moves
    std::vector<int> AvailableMoves() const;

    /// @brief Gets all child nodes
    /// @param  The depth of the parent
    /// @return A vector of all child nodes
    std::vector<Node> GetChildNodes(unsigned long d, std::shared_ptr<const Node> p) const;

    std::tuple<std::vector<int>, int> GetNextLayout(int dir) const;

    /// @brief Gets the Manhattan distance of the puzzle (l-2 distance)
    /// @return The manhattan distance
    int GetManhattanDistance() const;

    /// @brief Gets the hash value of the node
    /// @return The hash value of the node
    std::size_t GetHashValue() const;

    /// @brief Gets the depth of the node
    /// @return The depth
    unsigned long GetDepth() const;

    /// @brief Prints the node
    void Print() const;

    bool operator==(const Node& rhs) const;

    bool operator!=(const Node& rhs) const;

    /// @brief Returns if the puzzle is solved
    /// @return Is solved or not
    bool IsSolved() const;

    std::shared_ptr<const Node> GetParent() const;

private:
    /// @brief Calcualte the Manhattan distance
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

    /// @brief The parent of this node
    std::shared_ptr<const Node> parent;
};

#endif // INCLUDE_NODE_NODELIB_H_
