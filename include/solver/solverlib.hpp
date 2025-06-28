#ifndef INCLUDE_SOLVER_SOLVERLIB_H_
#define INCLUDE_SOLVER_SOLVERLIB_H_

#include <cstddef>  // std::size_t
#include <vector>   // std::vector
#include <unordered_set>    // std::unordered_set
#include <queue>    // std::priority_queue
#include <tuple>    // std::tuple
#include <string>    // std::string

#include "node/nodelib.hpp" // Node

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

    /// @brief Solves the puzzle
    /// @return { whether the puzzle is solved, the number of iterations the Solver took }
    std::tuple<bool, unsigned long> SolvePuzzle();

    /// @brief Gets the optimal number of moves
    /// @return The move
    std::size_t GetNumOfMoves() const;

    /// @brief Gets the solution
    /// @return The solution
    std::string GetSolution() const;

    /// @brief Gets the path (all the nodes from the start to the end)
    /// @return The path
    std::vector<Node> GetPath() const;

    /// @brief Print out the path (from the start node to the goal)
    void PrintPath() const;

protected:

    /// @brief the compare function for the priority queue
    struct NodeCmp
    {
        bool operator()(const Node& lhs, const Node& rhs)
        {
            // Check if the two nodes are identical
            if (lhs != rhs)
            {
                // Check if the two nodes have the same total cost (f value)
                // if so then we prefer the node that has a lower Manhattan distance (h value)
                if (lhs.GetTotalCost() == rhs.GetTotalCost())
                {
                    return lhs.GetManhattanDistance() > rhs.GetManhattanDistance();
                }

                return lhs.GetTotalCost() > rhs.GetTotalCost();
            }

            // If they are identical, then we use the hash value for comparison.
            // Since this is for the min. priority queue, we return true if the lhs is greater than the rhs.
            return lhs.GetDepth() > rhs.GetDepth();
        }
    };

    /// @brief Generate the path by backtracking
    void GeneratePath();

protected:

    /// @brief the cache that stores all visited nodes
    std::unordered_set<std::size_t> visited;

    /// @brief the priority queue that stores all candidate nodes
    std::priority_queue<Node, std::vector<Node>, NodeCmp> pq;

    /// @brief the current node
    Node curNode;

    /// @brief the number of iterations
    unsigned long iter;

    /// @brief the solution
    std::string solution;

    /// @brief the path
    std::vector<Node> path;
};

#endif // INCLUDE_SOLVER_SOLVERLIB_H_
