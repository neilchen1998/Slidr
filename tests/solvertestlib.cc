#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <vector>    // std::vector
#include <array>    // std::array
#include <algorithm>    // std::ranges::equal
#include <span> // std::span
#include <concepts> // std::integral

#include "constants/constantslib.hpp"
#include "math/mathlib.hpp"
#include "node/nodelib.hpp"
#include "solver/solverlib.hpp"

/// @brief Get the underlying container of an iteralbe type
/// @tparam Adaptor the data type of the input
/// @param adaptor An iterable data structure
/// @return The underlying container of the input
template<typename Adaptor>
requires (std::ranges::input_range<typename Adaptor::container_type>)   // makes sure Adaptor is iterable
inline std::vector<typename Adaptor::value_type> GetContainer(const Adaptor& adaptor)
{
    struct Printer : Adaptor // to access protected Adaptor::Container c (protected inheritance)
    {
        std::vector<typename Adaptor::value_type> GetContainer() const { return this->c; }
    };

    return static_cast<const Printer&>(adaptor).GetContainer();
}

/// @brief Tester inherits all the protected members of Solver
struct Tester : Solver
{
    std::unordered_set<std::size_t> GetVisited() const { return this->visited; }

    /// @brief Get a copy of the priority queue of Solver
    /// @return A copy of the priority queue
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> GetPQ() const { return this->pq; }

    /// @brief Get the reference of the priority queue of Solver
    /// @return The reference
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> &GetPQ() { return this->pq; }
    Node GetCurrentNode () const { return this->curNode; }
    int GetSteps() const { return this->steps; }
};

TEST_CASE( "Solver Initialization", "[main]" )
{
    std::vector<int> layout {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
    Solver s = Solver(layout);
    Node actualNode = Node(layout);

    // convert it to be of type Tester so we can get all its protected members
    Tester t = static_cast<const Tester&>(s);

    SECTION("Visited", "[some_details]")
    {
        REQUIRE (t.GetVisited().empty());
    }

    SECTION("Priority Queue", "[some_details]")
    {
        auto pq = t.GetPQ();
        REQUIRE (pq.empty() == false);

        std::vector<Node> vec = GetContainer(pq);
        
        REQUIRE (vec.size() == 1);
        REQUIRE (vec.front() == actualNode);
    }

    SECTION("Current Node", "[some_details]")
    {
        REQUIRE (t.GetCurrentNode() == actualNode);
    }

    SECTION("Steps", "[some_details]")
    {
        REQUIRE (t.GetSteps() == 0);
    }
}

TEST_CASE( "Priority Queue", "[main]" )
{
    Node actualZero = Node({1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY});
    Node actualOne1 = Node({1, 2, 3, 4, 5, constants::EMPTY, 7, 8, 6});
    Node actualOne2 = Node({1, 2, 3, 4, 5, 6, 7, constants::EMPTY, 8});
    Node actualTwo = Node({1, 2, 3, 4, constants::EMPTY, 6, 7, 5, 8});

    SECTION("Three Nodes with Three Distinct Values", "[some_details]")
    {
        Solver s = Solver({1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY});
        Tester t = static_cast<const Tester&>(s);

        // gets the reference of the priority queue of the Solver instance
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>>& pq = t.GetPQ();

        // inject the values directly
        pq.push(actualOne1);
        pq.push(actualTwo);

        std::vector<Node> vec = GetContainer(pq);
        REQUIRE (vec.size() == 3);
        auto itr = vec.begin();
        REQUIRE (*itr++ == actualZero);
        REQUIRE (*itr++ == actualOne1);
        REQUIRE (*itr == actualTwo);
    }
}
