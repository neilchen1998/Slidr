#ifndef INCLUDE_SOLVER_SOLVERLIB_H_
#define INCLUDE_SOLVER_SOLVERLIB_H_


#include <cstdlib>  // std::size_t
#include <vector>   // std::vector
#include <unordered_set>    // std::unordered_set
#include <queue>    // std::priority_queue
#include <tuple>    // std::tuple

class Solver
{
public:
    Solver(std::vector<int> initialLayout);
    ~Solver() = default;

    std::tuple<bool, int> SolvePuzzle();

protected:

    struct NodeCmp
    {
        bool operator()(const Node& lhs, const Node& rhs)
        {
            if (lhs != rhs)
            {
                return lhs > rhs;
            }
            else
            {
                return lhs.GetCurrentHashValue() > rhs.GetCurrentHashValue();
            }
        }
    };

    std::unordered_set<std::size_t> visited;
    std::priority_queue<Node, std::vector<Node>, NodeCmp> pq;
    Node curNode;
    int steps;
};

#endif // INCLUDE_SOLVER_SOLVERLIB_H_
