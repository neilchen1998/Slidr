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

        // gets current depth
        int curDepth = curNode.GetDepth();

        // gets all fessible children
        std::vector<Node<GridSize>> children = curNode.GetChildrenNodes();

        // starts from the beginning and checks if we have visited it before
        for(Node<GridSize>& child : children)
        {
            auto curHashValue = child.GetHashValue();
            if (visited.count(curHashValue) == 0)
            {
                pq.push(child);
                parents[child] = curNode;

                visited.insert(curHashValue);
            }
            else if (child.GetDepth() > curDepth + 1)
            {
                child.UpdateDepth(curDepth + 1);
                pq.push(child);
                parents[child] = curNode;
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
