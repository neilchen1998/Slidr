#ifndef INCLUDE_SOLVER_SOLVERLIB_H_
#define INCLUDE_SOLVER_SOLVERLIB_H_

#include <cstdlib>  // std::size_t
#include <vector>   // std::vector
#include <unordered_set>    // std::unordered_set
#include <unordered_map>    // std::unordered_map
#include <queue>    // std::priority_queue
#include <tuple>    // std::tuple

#include "node/nodelib.hpp"

/// @brief The compare function for the priority queue
/// @tparam GridSize the size of the node
template <int GridSize>
struct NodeCmp
{
    bool operator()(const Node<GridSize>& lhs, const Node<GridSize>& rhs)
    {
        return lhs.GetTotalCost() > rhs.GetTotalCost();
    }
};

/// @brief Gets the hash of the node
/// @tparam GridSize the size of the node
template <int GridSize>
struct KeyHash
{
    std::size_t operator()(const Node<GridSize>& k) const
    {
        return k.GetHashValue();
    }
};

/// @brief Checks if two nodes are identical
/// @tparam GridSize the size of the node
template <int GridSize>
struct KeyEqual
{
    bool operator()(const Node<GridSize>& lhs, const Node<GridSize>& rhs) const
    {
        return lhs.GetHashValue() == rhs.GetHashValue();
    }
};

template <int GridSize>
class Solver
{
public:
    /// @brief The constructor
    /// @param initialState the initial layout of the puzzle (vector type)
    Solver(std::vector<int> initialState);

    /// @brief The constructor
    /// @param initialNode the initial layout of the puzzle (vector type)
    Solver(const Node<GridSize>& initialNode);

    ~Solver() = default;

    /// @brief Solves the puzzle
    /// @return { whether the puzzle is solved, the number of iterations the Solver took }
    std::tuple<bool, int> SolvePuzzle();

    /// @brief Solves the puzzle with help from patterns
    /// @return { whether the puzzle is solved, the number of iterations the Solver took }
    std::tuple<bool, int> SolvePuzzleWithPatterns();

    /// @brief Gets the depth of the node
    /// @return the depth of the node
    int GetDepth() const;

    /// @brief Get the step-by-step solution to the problem
    /// @return the step-by-step solution (in node format)
    std::vector<Node<GridSize>> GetSolution() const;

    /// @brief Gets the move sequence of 'x'
    /// @return the move sequence
    std::vector<int> GetSequence();

protected:

    /// @brief Simple backtrack
    void Backtracking();

    /// @brief Backtrack with the help of patterns
    void BacktrackingWithPatterns();

    /// @brief the cache that stores all visited nodes
    std::unordered_set<std::size_t> visited;

    /// @brief the map that contains nodes' parents
    std::unordered_map<Node<GridSize>, Node<GridSize>, KeyHash<GridSize>, KeyEqual<GridSize>> parents;

    /// @brief the priority queue that stores all candidate nodes
    std::priority_queue<Node<GridSize>, std::vector<Node<GridSize>>, NodeCmp<GridSize>> pq;

    /// @brief the start node
    Node<GridSize> startNode;

    /// @brief the current node
    Node<GridSize> curNode;

    /// @brief the number of iterations
    int iterations;

    /// @brief the depth (the least steps) to solve the puzzle
    int depth;

    /// @brief The depths of all nodes (it also serves as the OPEN list)
    std::unordered_map<std::size_t, int> depths;

    /// @brief The step-by-step solution to the problem
    std::vector<Node<GridSize>> solution;

    /// @brief Patterns {node hash, solution (in move direction format)}
    std::unordered_map<std::size_t, std::vector<int>> patterns;
};

#endif // INCLUDE_SOLVER_SOLVERLIB_H_
