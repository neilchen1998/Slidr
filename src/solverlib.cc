#include <cstdlib>  // std::size_t
#include <vector>   // std::vector
#include <unordered_set>    // std::unordered_set
#include <queue>    // std::priority_queue
#include <tuple>    // std::tuple

#include "node/nodelib.hpp"
#include "solver/solverlib.hpp"

Solver::Solver(const std::vector<int> initialLayout) : visited(), curNode(Node(initialLayout)), iter(0)
{
    pq.push(Node(initialLayout));
}

Solver::Solver(const Node& initialNode) : visited(), curNode(initialNode), iter(0)
{
    pq.push(initialNode);
}

std::tuple<bool, unsigned long> Solver::SolvePuzzle()
{
    while (!pq.empty())
    {
        // Get the top node
        curNode = pq.top();

        // Check if we have solved the problem
        if (curNode.IsSolved())
        {
            optimalNumOfMoves = curNode.GetDepth();
            return std::tuple{curNode.IsSolved(), iter};
        }

        pq.pop();

        // Get all fessible children
        std::vector<Node> children = curNode.GetChildNodes(curNode.GetDepth());

        // Loop through each child
        for(const Node& child : children)
        {
            auto curHashValue = child.GetHashValue();

            // Check if we have seen this before
            if (visited.count(curHashValue) == 0)
            {
                pq.push(child);
                visited.insert(curHashValue);

                ++iter;
            }
        }
    }

    // If we reach here that means we have run out of moves and therefore
    // we cannot solve the puzzle.
    return std::tuple{false, -1};
}

int Solver::GetNumOfMoves() const
{
    return optimalNumOfMoves;
}
