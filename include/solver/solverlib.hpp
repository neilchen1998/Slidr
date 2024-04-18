#ifndef INCLUDE_SOLVER_SOLVERLIB_H_
#define INCLUDE_SOLVER_SOLVERLIB_H_

#include <cstdlib>  // std::size_t
#include <vector>   // std::vector
#include <unordered_set>    // std::unordered_set
#include <queue>    // std::priority_queue
#include <tuple>    // std::tuple

#include "node/nodelib.hpp"

class Solver
{
public:
    /// @brief The constructor
    /// @param initialLayout the initial layout of the puzzle (vector type)
    Solver(std::vector<int> initialLayout);

    /// @brief The constructor
    /// @param initialNode the initial layout of the puzzle (vector type)
    Solver(const Node& initialNode);

    ~Solver() = default;

    /// @brief Solve the puzzle
    /// @return { whether the puzzle is solved, the number of steps the Solver took }
    std::tuple<bool, int> SolvePuzzle();

protected:

    /// @brief the compare function for the priority queue
    struct NodeCmp
    {
        bool operator()(const Node& lhs, const Node& rhs)
        {
            // checks if the two Nodes have different Manhattan value
            if (lhs != rhs)
            {
                // different Manhattan value, uses their values
                // since we are using a priority queue,
                // we prefer the Node with smaller Manhattan value
                return lhs > rhs;
            }
            else
            {
                // two Nodes have the same Manhattan value
                // we prefer the Node with high hash value since that indicates
                // the Node is closer to finish
                return lhs.GetCurrentHashValue() < rhs.GetCurrentHashValue();
            }
        }
    };

    /// @brief the cache that stores all visited nodes
    std::unordered_set<std::size_t> visited;

    /// @brief the priority queue that stores all candidate nodes
    std::priority_queue<Node, std::vector<Node>, NodeCmp> pq;

    /// @brief the current node
    Node curNode;

    /// @brief the number of steps
    int steps;
};

#endif // INCLUDE_SOLVER_SOLVERLIB_H_
