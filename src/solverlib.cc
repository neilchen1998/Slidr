#include <cstdlib>  // std::size_t
#include <vector>   // std::vector
#include <unordered_set>    // std::unordered_set
#include <queue>    // std::priority_queue
#include <tuple>    // std::tuple
#include <climits>  // INT_MAX
#include <algorithm>  // std::ranges::reverse
#include <iostream> // std::cout

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
    solution.push_back(cur);

    depth = 0;
    while (cur != startNode)
    {
        cur = parents[cur];
        solution.push_back(cur);
        ++depth;
    }

    std::reverse(solution.begin(), solution.end());
}

int Solver::GetDepth() const
{
    return depth;
}

std::vector<Node> Solver::GetSolution() const
{
    // // DEBUG
    // int i = 0;
    // auto itr = solution.cbegin();
    // while (itr != solution.cend())
    // {
    //     std::cout << "Step " << i << ":\n";
    //     itr->Print();

    //     ++itr;
    //     ++i;
    // }

    return solution;
}
