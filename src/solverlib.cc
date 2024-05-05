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

template class Solver<constants::EIGHT_PUZZLE_SIZE>;
template class Solver<constants::FIFTEEN_PUZZLE_SIZE>;

template <int GridSize>
Solver<GridSize>::Solver(const std::vector<int> initialState) : visited(), startNode(Node<GridSize>(initialState)), iterations(0), depth(0)
{
    pq.push(Node<GridSize>(initialState));
}

template <int GridSize>
Solver<GridSize>::Solver(const Node<GridSize>& initialNode) : visited(), startNode(initialNode), iterations(0), depth(0)
{
    pq.push(initialNode);
}

template <int GridSize>
std::tuple<bool, int> Solver<GridSize>::SolvePuzzle()
{
    // first checks if the puzzle is solvable or not
    if (startNode.Insolvable())   return {false, INT_MAX};

    // keep solving until the priority queue is empty
    while (!pq.empty())
    {
        // gets the top node
        curNode = pq.top();
        pq.pop();

        // checks if we have solved the problem
        if (curNode.IsSolved())
        {
            Backtracking();

            return std::tuple{curNode.IsSolved(), iterations};
        }

        // gets the hash value of the current node
        std::size_t curNodeHashValue = curNode.GetHashValue();

        // prevents from visiting again and again
        if (visited.count(curNodeHashValue) != 0)   continue;

        // adds current node to the closed list
        visited.insert(curNodeHashValue);

        // gets current depth
        int curDepth = depths[curNodeHashValue];

        // gets all fessible children
        std::vector<Node<GridSize>> children = curNode.GetChildrenNodes();

        // starts from the beginning and checks if we have visited it before
        for(Node<GridSize>& child : children)
        {
            auto childHashValue = child.GetHashValue();
            if (visited.count(childHashValue) == 0)
            {
                if (depths.count(childHashValue) == 0 // checks if the child is in the open list
                    || curDepth + 1 < depths[child.GetHashValue()]) // checks if we need to update the open list
                {
                    pq.push(child);
                    parents[child] = curNode;
                    depths[child.GetHashValue()] = curDepth + 1;
                }
            }
        }

        ++iterations;
    }

    return std::tuple{false, INT_MAX};
}

template <int GridSize>
void Solver<GridSize>::Backtracking()
{
    Node<GridSize> cur = curNode;
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

template <int GridSize>
int Solver<GridSize>::GetDepth() const
{
    return depth;
}

template <int GridSize>
std::vector<Node<GridSize>> Solver<GridSize>::GetSolution() const
{
    return solution;
}

template <int GridSize>
std::vector<int> Solver<GridSize>::GetSequence()
{
    std::vector<int> ret(depth);
    int i = 0;
    auto cur = solution.begin();
    auto next = cur + 1;
    while (next != solution.end())
    {
        ret[i] = next->FindUndoMove(*cur);

        ++cur, ++next;
        ++i;
    }

    return ret;
}
