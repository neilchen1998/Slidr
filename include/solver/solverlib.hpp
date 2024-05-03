#ifndef INCLUDE_SOLVER_SOLVERLIB_H_
#define INCLUDE_SOLVER_SOLVERLIB_H_

#include <cstdlib>  // std::size_t
#include <vector>   // std::vector
#include <unordered_set>    // std::unordered_set
#include <unordered_map>    // std::unordered_map
#include <queue>    // std::priority_queue
#include <tuple>    // std::tuple

#include "node/nodelib.hpp"

/// @brief the compare function for the priority queue
template <int GridSize>
struct NodeCmp
{
    bool operator()(const Node<GridSize>& lhs, const Node<GridSize>& rhs)
    {
        return lhs.GetTotalCost() > rhs.GetTotalCost();
    }
};

template <int GridSize>
struct KeyHash
{
    std::size_t operator()(const Node<GridSize>& k) const
    {
        return k.GetHashValue();
    }
};

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

    /// @brief Solve the puzzle
    /// @return { whether the puzzle is solved, the number of iterations the Solver took }
    std::tuple<bool, int> SolvePuzzle();

    int GetDepth() const;

    std::vector<Node<GridSize>> GetSolution() const;

protected:

    void Backtracking();

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

    std::unordered_map<std::size_t, int> depths;

    std::vector<Node<GridSize>> solution;
};

#endif // INCLUDE_SOLVER_SOLVERLIB_H_
