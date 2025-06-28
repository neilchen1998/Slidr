#ifndef INCLUDE_NODE_NODELIB_H_
#define INCLUDE_NODE_NODELIB_H_

#include <vector>   // std::vector
#include <cstddef>  // std::size_t
#include <tuple>    // std::tuple
#include <memory>   // std::shared_ptr

class Node
{
public:
    Node() = delete;
    Node(std::vector<int> input);
    Node(std::vector<int> input, int posX);
    Node(std::vector<int> input, int posX, unsigned long d, std::shared_ptr<const Node> p, short m);
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
    unsigned int GetManhattanDistance() const;

    /// @brief Gets the hash value of the node
    /// @return The hash value of the node
    std::size_t GetHashValue() const;

    /// @brief Gets the depth of the node
    /// @return The depth
    unsigned int GetDepth() const;

    /// @brief Gets the total cost of the node
    /// @return The total cost
    unsigned int GetTotalCost() const;

    /// @brief Prints the node
    void Print() const;

    /// @brief Compares if two nodes (puzzles) are identical
    /// @param rhs The right hand side node (puzzle)
    /// @return True if they are identical
    inline bool operator==(const Node &rhs) const
    {
        return state == rhs.state;
    }

    /// @brief Compares if two nodes (puzzles) are NOT identical
    /// @param rhs The right hand side node (puzzle)
    /// @return True if they are NOT identical
    inline bool operator!=(const Node &rhs) const
    {
        return !(*this == rhs);
    }

    /// @brief Returns if the puzzle is solved
    /// @return Is solved or not
    bool IsSolved() const;

    /// @brief Gets the pointer of its parent
    /// @return The pointer of its parent
    std::shared_ptr<const Node> GetParent() const;

    /// @brief Gets the move used to reach this node
    /// @return The move
    short GetMove() const;

private:
    /// @brief Calcualte the Manhattan distance
    void CalculateManhattanDistance();

protected:
    /// @brief The state of the node
    std::vector<int> state;

    /// @brief The position of The empty piece
    int posX;

    /// @brief The Manhattan distance
    unsigned int manhattanDistance;

    /// @brief The hash value
    std::size_t hashValue;

    /// @brief The depth of the node
    unsigned int depth;

    /// @brief The parent of this node
    std::shared_ptr<const Node> parent;

    /// @brief The move used to reach this node in terms of the empty space
    short move;
};

#endif // INCLUDE_NODE_NODELIB_H_
