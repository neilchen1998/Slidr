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
    std::priority_queue<Node, std::vector<Node>, NodeCmp> GetPQ() const { return this->pq; }

    /// @brief Get the reference of the priority queue of Solver
    /// @return The reference
    std::priority_queue<Node, std::vector<Node>, NodeCmp> &GetPQ() { return this->pq; }
    Node GetStartNode () const { return this->startNode; }
    int GetIterations() const { return this->iterations; }
    std::vector<Node> GetSolution() const { return this->solution; }
};

const std::vector<int> goalState {1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY};

TEST_CASE( "Solver Constructor", "[main]" )
{
    std::vector<int> initialState {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};

    SECTION("Constructor with Vector", "[some_details]")
    {
        Solver s = Solver(initialState);
        // convert it to be of type Tester so we can get all its protected members
        Tester t = static_cast<const Tester&>(s);
        REQUIRE (t.GetVisited().empty());
    }

    SECTION("Constructor with Node", "[some_details]")
    {
        Node initalNode = Node(initialState);
        Solver s = Solver(initalNode);
        // convert it to be of type Tester so we can get all its protected members
        Tester t = static_cast<const Tester&>(s);
        REQUIRE (t.GetVisited().empty());
    }
}

TEST_CASE( "Solver Initialization", "[main]" )
{
    std::vector<int> initialState {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
    Solver s = Solver(initialState);
    Node actualNode = Node(initialState);

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
        REQUIRE (t.GetStartNode() == actualNode);
    }

    SECTION("Steps", "[some_details]")
    {
        REQUIRE (t.GetIterations() == 0);
    }
}

TEST_CASE( "Priority Queue", "[main]" )
{
    Node actualZero = Node(goalState);
    Node actualOne1 = Node({1, 2, 3, 4, 5, constants::EMPTY, 7, 8, 6});
    Node actualOne2 = Node({1, 2, 3, 4, 5, 6, 7, constants::EMPTY, 8});
    Node actualTwo = Node({1, 2, 3, 4, constants::EMPTY, 6, 7, 5, 8});

    SECTION("Three Nodes with Three Distinct Values", "[some_details]")
    {
        Solver s = Solver(goalState);
        Tester t = static_cast<const Tester&>(s);

        // gets the reference of the priority queue of the Solver instance
        auto& pq = t.GetPQ();

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

    SECTION("Two Nodes with Two Distinct Values", "[some_details]")
    {
        Solver s = Solver(goalState);
        Tester t = static_cast<const Tester&>(s);

        // gets the reference of the priority queue of the Solver instance
        auto& pq = t.GetPQ();

        // inject the values directly
        pq.push(actualOne1);
        pq.push(actualOne2);

        std::vector<Node> vec = GetContainer(pq);
        REQUIRE (vec.size() == 3);
        auto itr = vec.begin();
        REQUIRE (*itr++ == actualZero);
        bool statement2 = *itr == actualOne1 || *itr++ == actualOne2;
        REQUIRE (statement2);
        bool statement3 = *itr == actualOne1 || *itr++ == actualOne2;
        REQUIRE (statement3);
    }
}

TEST_CASE( "Can Solve Puzzles", "[main]" )
{
    SECTION("Puzzle 0", "[trivial case]")
    {
        Solver s = Solver(goalState);
        auto [isSolved, totalIterations] = s.SolvePuzzle();

        REQUIRE (isSolved);
        REQUIRE (totalIterations == 0);
    }

    SECTION("Puzzle 1", "[general case]")
    {
        std::vector<int> initialState {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
        Solver s = Solver(initialState);
        auto [isSolved, totalIterations] = s.SolvePuzzle();

        REQUIRE (isSolved);
    }

    SECTION("Puzzle 2", "[general case]")
    {
        std::vector<int> initialState {5, 3, 6, 2, constants::EMPTY, 8, 4, 1, 7};
        Solver s = Solver(initialState);
        auto [isSolved, totalIterations] = s.SolvePuzzle();

        REQUIRE (isSolved);
    }
}

TEST_CASE( "Solve Puzzles with Least Steps", "[main]" )
{
    // source: https://deniz.co/8-puzzle-solver/
    SECTION("Puzzle 0", "[trivial case]")
    {
        Solver s = Solver(goalState);
        auto [isSolved, totalIterations] = s.SolvePuzzle();

        REQUIRE (isSolved);
        REQUIRE (totalIterations == 0);
    }

    SECTION("Puzzle 1", "[general case]")
    {
        std::vector<int> initialState {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
        Solver s = Solver(initialState);
        auto [isSolved, totalIterations] = s.SolvePuzzle();

        REQUIRE (isSolved);
        REQUIRE (s.GetDepth() == 2);
    }

    SECTION("Puzzle 2", "[general case]")
    {
        std::vector<int> initialState {5, 3, 6, 2, constants::EMPTY, 8, 4, 1, 7};
        Solver s = Solver(initialState);
        auto [isSolved, totalIterations] = s.SolvePuzzle();

        std::vector<Node> solution = s.GetSolution();
        REQUIRE (solution.front() == Node(initialState));
        REQUIRE (solution.back() == Node(goalState));

        REQUIRE (isSolved);
        REQUIRE (s.GetDepth() == 14);
    }

    SECTION("Puzzle 3", "[general case]")
    {
        std::vector<int> initialState {4, 8, 7, 1, constants::EMPTY, 3, 6, 5, 2};
        Node start = Node(initialState);

        REQUIRE(start.GetManhattanDistance() == 16);

        Solver s = Solver(initialState);
        auto [isSolved, totalIterations] = s.SolvePuzzle();

        std::vector<Node> solution = s.GetSolution();
        REQUIRE (solution.front() == Node(initialState));
        REQUIRE (solution.back() == Node(goalState));

        REQUIRE (isSolved);
        REQUIRE (s.GetDepth() == 26);
    }

    SECTION("Puzzle 4", "[general case]")
    {
        std::vector<int> initialState {3, 7, 8, constants::EMPTY, 2, 1, 4, 6, 5};
        Node start = Node(initialState);

        REQUIRE(start.GetManhattanDistance() == 17);

        Solver s = Solver(initialState);
        auto [isSolved, totalIterations] = s.SolvePuzzle();

        std::vector<Node> solution = s.GetSolution();
        REQUIRE (solution.front() == Node(initialState));
        REQUIRE (solution.back() == Node(goalState));

        REQUIRE (isSolved);
        REQUIRE (s.GetDepth() == 23);
    }
}
