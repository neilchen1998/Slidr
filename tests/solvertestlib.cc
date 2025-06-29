#define CATCH_CONFIG_MAIN

#include <vector>    // std::vector
#include <ranges>    // std::ranges::input_range
#include <unordered_set>    // std::unordered_set
#include <catch2/catch_test_macros.hpp> // TEST_CASE, SECTION, REQUIRE
#include <catch2/matchers/catch_matchers_all.hpp>   // Catch::Matchers::Equals

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
    std::priority_queue<Node, std::vector<Node>, NodeCmp> GetPQ() const { return this->pq; }

    /// @brief Get the reference of the priority queue of Solver
    /// @return The reference of the priority queue
    std::priority_queue<Node, std::vector<Node>, NodeCmp> &GetPQ() { return this->pq; }
    Node GetCurrentNode () const { return this->curNode; }
    int Getteps() const { return this->iter; }
};

TEST_CASE( "Solver Constructor", "[main]" )
{
    std::vector<int> layout {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};

    SECTION("Constructor with Vector", "[some_details]")
    {
        Solver s = Solver(layout);
        // convert it to be of type Tester so we can get all its protected members
        Tester t = static_cast<const Tester&>(s);
        REQUIRE (t.GetVisited().empty());
    }

    SECTION("Constructor with Node", "[some_details]")
    {
        Node initalNode = Node(layout);
        Solver s = Solver(initalNode);
        // convert it to be of type Tester so we can get all its protected members
        Tester t = static_cast<const Tester&>(s);
        REQUIRE (t.GetVisited().empty());
    }
}

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
        REQUIRE (t.Getteps() == 0);
    }
}

TEST_CASE( "Priority Queue", "[main]" )
{
    Node node0 = Node({1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY});
    Node node1 = Node({1, 2, 3, 4, 5, 6, 7, constants::EMPTY, 8});
    Node node2 = Node({1, 2, 3, 4, 5, constants::EMPTY, 7, 8, 6});

    // Create two identical nodes but two different cost values
    std::vector<int> state {{1, 2, 3, constants::EMPTY, 4, 6, 7, 5, 8}};
    Node node3 = Node(state, 1);
    Node node4 = Node(state, 2);

    SECTION("Three Different Nodes with Three Distinct Manhattan Values", "[some_details]")
    {
        Solver s = Solver(node0);
        Tester t = static_cast<const Tester&>(s);

        // Get the reference of the priority queue of the Solver instance
        auto& pq = t.GetPQ();

        // Inject the values directly
        pq.push(node1);
        pq.push(node3);

        std::vector<Node> vec = GetContainer(pq);
        REQUIRE (vec.size() == 3);
        REQUIRE (vec.at(0) == node0);
        REQUIRE (vec.at(1) == node1);
        REQUIRE (vec.at(2) == node3);
    }

    SECTION("Two Identical Nodes with Two Cost Values", "[some_details]")
    {
        Solver s = Solver(node0);
        Tester t = static_cast<const Tester&>(s);

        // Get the reference of the priority queue of the Solver instance
        auto& pq = t.GetPQ();

        // Inject the values directly
        pq.push(node3);
        pq.push(node4);

        std::vector<Node> vec = GetContainer(pq);
        REQUIRE (vec.size() == 3);
        REQUIRE (vec.at(0) == node0);
        REQUIRE (vec.at(1) == node3);
        REQUIRE (vec.at(2) == node4);
    }
}

TEST_CASE( "Can Solve Puzzles", "[main]" )
{
    SECTION("Puzzle 0", "[trivial case]")
    {
        std::vector<int> layout {1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY};
        Solver s = Solver(layout);
        auto [isSolved, numOfIters] = s.SolvePuzzle();

        REQUIRE (isSolved);
        REQUIRE (numOfIters == 0);
    }

    SECTION("Puzzle 1", "[general case]")
    {
        std::vector<int> layout {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
        Solver s = Solver(layout);
        auto [isSolved, _] = s.SolvePuzzle();
        auto depth = s.GetNumOfMoves();
        auto solution = s.GetSolution();

        REQUIRE (isSolved);
        REQUIRE (depth == 2);
        REQUIRE (solution == "↑↑");
    }

    SECTION("Puzzle 2", "[general case]")
    {
        // 536208417
        std::vector<int> layout {5, 3, 6, 2, constants::EMPTY, 8, 4, 1, 7};
        Solver s = Solver(layout);
        auto [isSolved, _] = s.SolvePuzzle();
        auto depth = s.GetNumOfMoves();
        auto solution = s.GetSolution();

        REQUIRE (isSolved);
        REQUIRE (depth == 14);
        REQUIRE_THAT(solution, Catch::Matchers::Equals("↑←↓↓→→↑←↓→↑↑←←") || Catch::Matchers::Equals("↑←↓↓→↑→↓←↑→↑←←")); // there're two valid solutions so far
    }

    SECTION("Puzzle 3", "[general case]")
    {
        // 318652470
        std::vector<int> layout {3, 1, 8, 6, 5, 2, 4, 7, constants::EMPTY};
        Solver s = Solver(layout);
        auto [isSolved, _] = s.SolvePuzzle();
        auto depth = s.GetNumOfMoves();
        auto solution = s.GetSolution();

        REQUIRE (isSolved);
        REQUIRE (depth == 22);
        REQUIRE (solution == "↓→→↓←↑→↑←←↓↓→↑↑←↓↓→↑↑←");
    }
}
