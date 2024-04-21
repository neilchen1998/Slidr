#include <cstdlib>  // std::size_t
#include <vector>   // std::vector
#include <unordered_set>    // std::unordered_set
#include <queue>    // std::priority_queue
#include <tuple>    // std::tuple
#include <climits>  // INT_MAX

#include "constants/constantslib.hpp"
#include "math/mathlib.hpp"
#include "node/nodelib.hpp"
#include "solver/solverlib.hpp"

Solver::Solver(const std::vector<int> initialState) : visited(), startNode(Node(initialState)), iterations(0), depth(0)
{
    pq.push(Node(initialState));
}

Solver::Solver(const Node& initialNode) : visited(), startNode(initialNode), iterations(0), depth(0)
{
    pq.push(initialNode);
}

std::tuple<bool, int> Solver::SolvePuzzle()
{
    while (!pq.empty())
    {
        // gets the top node
        curNode = pq.top();

        // checks if we have solved the problem
        if (curNode.IsSolved())
        {
            Backtracking();

            return std::tuple{curNode.IsSolved(), iterations};
        }

        pq.pop();

        // gets all fessible children
        std::vector<Node> children = curNode.GetChildrenNodes();

        // starts from the beginning and checks if we have visited it before
        for(const Node& child : children)
        {
            auto curHashValue = child.GetHashValue();
            if (visited.count(curHashValue) == 0)
            {
                pq.push(child);
                parents[child] = curNode;

                visited.insert(curHashValue);
            }
        }

        ++iterations;
    }

    return std::tuple{false, INT_MAX};
}

void Solver::Backtracking()
{
    Node cur = curNode;

    depth = 0;
    while (cur != startNode)
    {
        cur = parents[cur];
        ++depth;
    }
}

int Solver::GetDepth() const
{
    return depth;
}
