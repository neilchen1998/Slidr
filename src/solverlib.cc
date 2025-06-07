#include <cstddef>
#include <cstdlib>  // std::size_t
#include <vector>   // std::vector
#include <unordered_set>    // std::unordered_set
#include <queue>    // std::priority_queue
#include <tuple>    // std::tuple
#include <memory.h> // std::shared_ptr, std::make_shared
#include <algorithm>    // std::reverse

#include "node/nodelib.hpp"
#include "solver/solverlib.hpp"
#include "constants/constantslib.hpp"

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

        std::shared_ptr<const Node> p = std::make_shared<const Node>(curNode);

        // Check if we have solved the problem
        if (curNode.IsSolved())
        {
            GeneratePath();
            return std::tuple{curNode.IsSolved(), iter};
        }

        pq.pop();

        // Get all fessible children
        std::vector<Node> children = curNode.GetChildNodes(curNode.GetDepth(), p);

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
    return std::tuple{false, iter};
}

std::size_t Solver::GetNumOfMoves() const
{
    // The path includes the start state
    return (path.size() - 1);
}

std::string Solver::GetSolution() const
{
    return solution;
}

std::vector<Node> Solver::GetPath() const
{
    return path;
}

void Solver::GeneratePath()
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
