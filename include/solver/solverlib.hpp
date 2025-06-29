#ifndef INCLUDE_SOLVER_SOLVERLIB_H_
#define INCLUDE_SOLVER_SOLVERLIB_H_

#include <cstddef>  // std::size_t
#include <vector>   // std::vector
#include <unordered_set>    // std::unordered_set
#include <queue>    // std::priority_queue
#include <tuple>    // std::tuple
#include <string>    // std::string
#include <memory> // std::shared_ptr, std::make_shared
#include <algorithm>    // std::reverse
#include <fmt/core.h>   // fmt::print

#include "node/nodelib.hpp" // Node
#include "solver/solverlib.hpp" // Solver
#include "constants/constantslib.hpp"   // constants::RIGHT, constants::LEFT, etc.s

using DefaultPQ = std::priority_queue<Node, std::vector<Node>, NodeCmp>;

template<typename PQ = DefaultPQ>
class Solver
{
public:

    Solver(PQ pq) : pq_(std::move(pq)) {}

    /// @brief The constructor
    /// @param initialLayout the initial layout of the puzzle (vector type)
    Solver(std::vector<int> initialLayout) : pq_()
    {
        pq_.push(Node(initialLayout));
    }

    /// @brief The constructor
    /// @param initialNode the initial layout of the puzzle (vector type)
    Solver(const Node& initialNode) : pq_()
    {
        pq_.push(initialNode);
    }

    ~Solver() = default;

    /// @brief Solves the puzzle
    /// @return { whether the puzzle is solved, the number of iterations the Solver took }
    std::tuple<bool, unsigned long> SolvePuzzle()
    {
        std::size_t i = 0;
        while (!pq_.empty() && i < 1'000'000)
        {
            // Get the top node
            curNode = pq_.top();

            std::shared_ptr<const Node> p = std::make_shared<const Node>(curNode);

            // Check if we have solved the problem
            if (curNode.IsSolved())
            {
                GeneratePath();
                return std::tuple{curNode.IsSolved(), iter};
            }

            pq_.pop();

            // Get all fessible children
            std::vector<Node> children = curNode.GetChildNodes(curNode.GetDepth(), p);

            // Loop through each child
            for(const Node& child : children)
            {
                auto curHashValue = child.GetHashValue();

                // Check if we have seen this before
                if (visited.count(curHashValue) == 0)
                {
                    pq_.push(child);
                    visited.insert(curHashValue);

                    ++iter;
                }
            }

            ++i;
        }

        // If we reach here that means we have run out of moves and therefore
        // we cannot solve the puzzle.
        return std::tuple{false, iter};
    }

    /// @brief Gets the optimal number of moves
    /// @return The move
    std::size_t GetNumOfMoves() const
    {
        // The path includes the start state
        return (path.size() - 1);
    }

    /// @brief Gets the solution
    /// @return The solution
    inline std::string GetSolution() const
    {
        return solution;
    }

    /// @brief Gets the path (all the nodes from the start to the end)
    /// @return The path
    inline std::vector<Node> GetPath() const
    {
        return path;
    }

    /// @brief Print out the path (from the start node to the goal)
    void PrintPath() const
    {
        // Check if the puzzle is solved
        if (!curNode.IsSolved())
        {
            fmt::print("The puzzle could not be solved!\n");
            return;
        }

        // Print out the path
        for (size_t i = 0; i < path.size(); ++i)
        {
            fmt::print("Step: {}\n", i);
            path[i].Print();
        }
    }

private:

    /// @brief Generate the path by backtracking
    void GeneratePath()
    {
        std::vector<short> sol;

        // Start backtracking
        path.push_back(curNode);
        sol.push_back(curNode.GetMove());
        std::shared_ptr<const Node> p = curNode.GetParent();
        while (p != nullptr)
        {
            path.push_back(*p);
            sol.push_back(p->GetMove());
            p = p->GetParent();
        }

        std::reverse(path.begin(), path.end());

        // Construct the solution
        auto itr = sol.crbegin();
        while (itr != sol.crend())
        {
            // Invert the direction
            switch (*itr)
            {
            case constants::RIGHT:
                solution += "←";
                break;

            case constants::UP:
                solution += "↓";
                break;

            case constants::LEFT:
                solution += "→";
                break;

            case constants::DOWN:
                solution += "↑";
                break;

            default:
                break;
            }

            ++itr;
        }
    }

protected:

    /// @brief the cache that stores all visited nodes
    std::unordered_set<std::size_t> visited;

    /// @brief the priority queue that stores all candidate nodes
    PQ pq_;

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
