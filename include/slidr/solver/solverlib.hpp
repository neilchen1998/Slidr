#ifndef INCLUDE_SOLVER_SOLVERLIB_H_
#define INCLUDE_SOLVER_SOLVERLIB_H_

#include <cstddef>  // std::size_t
#include <vector>   // std::vector
#include <unordered_set>    // std::unordered_set
#include <queue>    // std::priority_queue
#include <tuple>    // std::tuple
#include <string>    // std::string
#include <memory>   // std::shared_ptr, std::make_shared
#include <type_traits>    // std::is_base_of
#include <algorithm>    // std::reverse
#include <concepts>     // requires
#include <utility>      // std::pair

#include <fmt/core.h>   // fmt::print
#include "absl/container/flat_hash_set.h"   // absl::flat_hash_set

#include "slidr/node/nodelib.hpp" // Node
#include "slidr/constants/constantslib.hpp"   // constants::RIGHT, constants::LEFT, etc.
#include "slidr/container/bucketqueuelib.hpp" // BucketQueueBase

/// @brief The concept of a set
/// @tparam T The type of the set
/// @tparam T::value_type The element
template<typename T>
concept SetLike = requires(T s, const typename T::value_type& v)
{
    // type requirements
    typename T::value_type;
    typename T::iterator;

    // compound requirements
    { s.insert(v) } -> std::same_as<std::pair<typename T::iterator, bool>>;
    { s.find(v) }  -> std::same_as<typename T::iterator>;
};

/// @brief The concept of a priority queue
/// @tparam T The type of the set
/// @tparam T::value_type The element
template<typename T>
concept PQLike = requires(T pq, const T const_pq, const typename T::value_type& v)
{
    // type requirements
    typename T::value_type; // T::value_type represents the type that this priority queue stores
    typename T::const_reference;  // const T::value_type

    // compound requirements
    { pq.empty() } -> std::same_as<bool>;
    { pq.size() } -> std::convertible_to<std::size_t>;
    { pq.push(v) } -> std::same_as<void>;   // lvalue
    { pq.push(std::move(v)) } -> std::same_as<void>;  // rvalue
    { pq.pop() } -> std::same_as<void>;
    { const_pq.top() } -> std::same_as<typename T::const_reference>;
};

namespace slidr
{
    using DefaultPQ = std::priority_queue<std::shared_ptr<Node>,  std::vector<std::shared_ptr<Node>>, NodeCmp>;

    template<typename PQLike = DefaultPQ, typename SetLike = absl::flat_hash_set<std::size_t>>
    class Solver
    {
    public:

        /// @brief The constructor
        /// @param initialLayout the initial layout of the puzzle (vector type)
        explicit Solver(std::vector<int> initialLayout, PQLike pq = PQLike()) : pq_(std::move(pq)), iter_(0)
        {
            std::shared_ptr<Node> n = std::make_shared<Node>(initialLayout);

            pq_.emplace(n);
        }

        /// @brief The constructor
        /// @param initialNode the initial layout of the puzzle (vector type)
        Solver(const Node& initialNode) : pq_(), iter_(0)
        {
            std::shared_ptr<Node> n = std::make_shared<Node>(initialNode);
            pq_.emplace(n);
        }

        /// @brief The default destructor
        ~Solver() = default;

        /// @brief Solves the puzzle
        /// @return { whether the puzzle is solved, the number of iterations the Solver took }
        std::tuple<bool, unsigned long> SolvePuzzle()
        {
            std::size_t i = 0;
            while (!pq_.empty() && i < 1'000'000)
            {
                // Get the top node
                curNode_ = pq_.top();

                // Check if we have solved the problem
                if (curNode_->IsSolved())
                {
                    GeneratePath();
                    return std::tuple{curNode_->IsSolved(), iter_};
                }

                pq_.pop();

                // Get all fessible children
                std::vector<Node> children = curNode_->GetChildNodes(curNode_->GetDepth(), curNode_);

                // Loop through each child
                for(const Node& child : children)
                {
                    auto curHashValue = child.GetHashValue();

                    // Check if we have seen this before
                    if (!visited_.count(curHashValue))
                    {
                        pq_.emplace(std::make_shared<Node>(child));
                        visited_.insert(curHashValue);

                        ++iter_;
                    }
                    else
                    {
                        continue;
                    }
                }

                ++i;
            }

            // If we reach here that means we have run out of moves and therefore
            // we cannot solve the puzzle.
            return std::tuple {false, iter_};
        }

        /// @brief Gets the optimal number of moves
        /// @return The move
        inline std::size_t GetNumOfMoves() const
        {
            // The path includes the start state
            return (path_.size() - 1);
        }

        /// @brief Gets the solution
        /// @return The solution in string
        inline std::string GetSolution() const
        {
            return solution_;
        }

        /// @brief Gets the solution
        /// @return The solution in string
        inline std::vector<short> GetSolutionDirection() const
        {
            return solutionDir_;
        }

        /// @brief Gets the path (all the nodes from the start to the end)
        /// @return The path
        inline std::vector<Node> GetPath() const
        {
            return path_;
        }

        /// @brief Print out the path (from the start node to the goal)
        void PrintPath() const
        {
            // Check if the puzzle is solved
            if (!curNode_->IsSolved())
            {
                fmt::print("The puzzle could not be solved!\n");
                return;
            }

            // Print out the path
            for (size_t i = 0; i < path_.size(); ++i)
            {
                fmt::print("Step: {}\n", i);
                path_[i].Print();
            }
        }

    private:

        /// @brief Generate the path by backtracking
        void GeneratePath()
        {
            std::vector<short> sol;

            // Start backtracking
            path_.push_back(*curNode_);
            sol.push_back(curNode_->GetMove());
            std::shared_ptr<const Node> p = curNode_->GetParent();
            while (p != nullptr)
            {
                path_.push_back(*p);
                sol.push_back(p->GetMove());
                p = p->GetParent();
            }

            std::reverse(path_.begin(), path_.end());

            // Pre-allocate memory for solution string
            solution_.reserve(sol.size() * sizeof("←"));

            // Reserve the capacity of the vector
            solutionDir_.reserve(sol.size());

            // Construct the solution
            auto itr = sol.crbegin();
            while (itr != sol.crend())
            {
                // Invert the direction
                switch (*itr)
                {
                case constants::RIGHT:
                    solution_ += "←";
                    break;

                case constants::UP:
                    solution_ += "↓";
                    break;

                case constants::LEFT:
                    solution_ += "→";
                    break;

                case constants::DOWN:
                    solution_ += "↑";
                    break;

                default:
                    break;
                }

                solutionDir_.push_back(*itr);

                ++itr;
            }
        }

    private:

        /// @brief the cache that stores all visited nodes
        SetLike visited_;

        /// @brief the priority queue that stores all candidate nodes
        PQLike pq_;

        /// @brief the current node
        /// NOTE: since top() returns a T& so this can not be replaced by a pointer
        std::shared_ptr<Node> curNode_;

        /// @brief the number of iterations
        unsigned long iter_;

        /// @brief the solution
        std::string solution_;

        /// @brief the solution (in direction)
        std::vector<short> solutionDir_;

        /// @brief the path
        std::vector<Node> path_;
    };
}   // slidr

#endif // INCLUDE_SOLVER_SOLVERLIB_H_
