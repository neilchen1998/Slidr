#include <cstdlib>  // std::size_t
#include <vector>   // std::vector
#include <unordered_set>    // std::unordered_set
#include <queue>    // std::priority_queue
#include <tuple>    // std::tuple

#include "constants/constantslib.hpp"
#include "math/mathlib.hpp"
#include "node/nodelib.hpp"
#include "solver/solverlib.hpp"

Solver::Solver(const std::vector<int> initialLayout) : visited(), curNode(Node(initialLayout)), steps(0)
{
    pq.push(Node(initialLayout));
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
            curNode.Print();
            return std::tuple{curNode.IsSolved(), steps};
        }

        pq.pop();

        // gets all fessible children
        std::vector<Node> children = curNode.GetChildrenNodes();

        // starts from the beginning and checks if we have visited it before
        for(const Node& child : children)
        {
            auto curHashValue = child.GetCurrentHashValue();
            if (visited.count(curHashValue) == 0)
            {
                pq.push(child);
                visited.insert(curHashValue);
            }
        }

        ++steps;
    }

    curNode.Print();

    return std::tuple{curNode.IsSolved(), steps};
}
