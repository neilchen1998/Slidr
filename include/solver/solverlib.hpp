#ifndef INCLUDE_SOLVER_SOLVERLIB_H_
#define INCLUDE_SOLVER_SOLVERLIB_H_

#include <cstdlib>  // std::size_t
#include <vector>   // std::vector
#include <unordered_set>    // std::unordered_set
#include <unordered_map>    // std::unordered_map
#include <queue>    // std::priority_queue
#include <tuple>    // std::tuple

#include "node/nodelib.hpp"

class Solver
{
public:
    /// @brief The constructor
    /// @param initialState the initial layout of the puzzle (vector type)
    Solver(std::vector<int> initialState);

    /// @brief The constructor
    /// @param initialNode the initial layout of the puzzle (vector type)
    Solver(const Node& initialNode);

    ~Solver() = default;

    /// @brief Solve the puzzle
    /// @return { whether the puzzle is solved, the number of iterations the Solver took }
    std::tuple<bool, int> SolvePuzzle();

    int GetDepth() const;

protected:

    /// @brief the compare function for the priority queue
    struct NodeCmp
    {
        bool operator()(const Node& lhs, const Node& rhs)
        {
            return lhs.GetManhattanDistance() + lhs.GetDepth() > rhs.GetManhattanDistance() + rhs.GetDepth();
        }
    };

    struct KeyHash
    {
        std::size_t operator()(const Node& k) const
        {
            return k.GetHashValue();
        }
    };

    struct KeyEqual
    {
        bool operator()(const Node& lhs, const Node& rhs) const
        {
            return lhs.GetHashValue() == rhs.GetHashValue();
        }
    };

    void Backtracking();

    /// @brief the cache that stores all visited nodes
    std::unordered_set<std::size_t> visited;

    /// @brief the map that contains nodes' parents
    std::unordered_map<Node, Node, KeyHash, KeyEqual> parents;

    /// @brief the priority queue that stores all candidate nodes
    std::priority_queue<Node, std::vector<Node>, NodeCmp> pq;

    /// @brief the start node
    Node startNode;

    /// @brief the current node
    Node curNode;

    /// @brief the number of iterations
    int iterations;

    /// @brief the depth (the least steps) to solve the puzzle
    int depth;
};

#endif // INCLUDE_SOLVER_SOLVERLIB_H_
