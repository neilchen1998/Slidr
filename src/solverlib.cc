#include <cstdlib>  // std::size_t
#include <vector>   // std::vector
#include <tuple>    // std::tuple
#include <climits>  // INT_MAX
#include <algorithm>  // std::reverse

#if DEBUG
#include <iostream> // std::cout
#endif

#include "constants/constantslib.hpp"
#include "pattern/patternlib.hpp"
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

            return std::tuple {curNode.IsSolved(), iterations};
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

    return std::tuple {false, INT_MAX};
}

template <int GridSize>
std::tuple<bool, int> Solver<GridSize>::SolvePuzzleWithPatterns(const std::string& filename)
{
    // first checks if the puzzle is solvable or not
    if (startNode.Insolvable())   return {false, INT_MAX};

    // loads patterns
    patterns = pattern::LoadSolution(filename);

    // keep solving until the priority queue is empty
    while (!pq.empty())
    {
        // gets the top node
        curNode = pq.top();
        pq.pop();

        // checks if we have solved the problem
        if (curNode.IsSolved())
        {
            #if DEBUG
                std::cout << "Found a solution. Start backtracking..." << std::endl;
            #endif

            Backtracking();

            return std::tuple {curNode.IsSolved(), iterations};
        }

        // gets the hash value of the current node
        std::size_t curNodeHashValue = curNode.GetHashValue();

        // checks if it exists in the patterns
        if (patterns.count(curNodeHashValue) != 0)
        {
            #if DEBUG
                std::cout << std::hex << curNodeHashValue << "\n";
                std::cout << "Found a solution using patterns. Start backtracking..." << std::endl;
            #endif

            BacktrackingWithPatterns();

            return std::tuple{true, iterations};
        }

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
void Solver<GridSize>::BacktrackingWithPatterns()
{
    Node<GridSize> cur = curNode;
    std::size_t queryHash = curNode.GetHashValue();
    solution.push_back(cur);

    depth = 0;
    while (cur != startNode)
    {
        cur = parents[cur];
        solution.push_back(cur);
        ++depth;
    }

    std::reverse(solution.begin(), solution.end());

    std::vector<int> sol = patterns[queryHash];

    #if DEBUG
        std::cout << "Retrieving solution from patterns..." << std::endl;

        int cnt = 0;
        std::for_each(sol.cbegin(), sol.cend(), [&](const auto& s)
        {
            ++cnt;
            std::cout << s;
            if (cnt % 5 == 0)   std::cout << "\n";
        });
        std::cout << std::flush;
    #endif

    cur = curNode;
    for(const int& move : sol)
    {
        auto [childState, childPosX] = cur.GetNextState(move);
        solution.emplace_back(childState, childPosX, depth + 1);
        cur = Node<GridSize>(childState, childPosX, depth + 1);
        ++depth;
    }
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
    auto next = solution.begin() + 1;
    while (next != solution.end())
    {
        ret[i] = next->FindUndoMove(*cur);

        ++cur, ++next;
        ++i;
    }

    return ret;
}
