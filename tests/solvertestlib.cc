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

// /// @brief Get the underlying container of an iteralbe type
// /// @tparam Adaptor the data type of the input
// /// @param adaptor An iterable data structure
// /// @return The underlying container of the input
// template<typename Adaptor>
// requires (std::ranges::input_range<typename Adaptor::container_type>)   // makes sure Adaptor is iterable
// inline std::vector<typename Adaptor::value_type> GetContainer(const Adaptor& adaptor)
// {
//     struct Printer : Adaptor // to access protected Adaptor::Container c (protected inheritance)
//     {
//         std::vector<typename Adaptor::value_type> GetContainer() const { return this->c; }
//     };

//     return static_cast<const Printer&>(adaptor).GetContainer();
// }

// /// @brief Tester inherits all the protected members of Solver
// struct Tester : Solver<constants::EIGHT_PUZZLE_SIZE>
// {
//     std::unordered_set<std::size_t> GetVisited() const { return this->visited; }

//     /// @brief Get a copy of the priority queue of Solver
//     /// @return A copy of the priority queue
//     std::priority_queue<Node<constants::EIGHT_PUZZLE_SIZE>, std::vector<Node<constants::EIGHT_PUZZLE_SIZE>>, NodeCmp> GetPQ() const { return this->pq; }

//     /// @brief Get the reference of the priority queue of Solver
//     /// @return The reference
//     std::priority_queue<Node<constants::EIGHT_PUZZLE_SIZE>, std::vector<Node<constants::EIGHT_PUZZLE_SIZE>>, NodeCmp> &GetPQ() { return this->pq; }
//     Node<constants::EIGHT_PUZZLE_SIZE> GetStartNode () const { return this->startNode; }
//     int GetIterations() const { return this->iterations; }
//     std::vector<Node<constants::EIGHT_PUZZLE_SIZE>> GetSolution() const { return this->solution; }
// };

const std::vector<int> EIGHT_GOAL_STATE {1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY};
const std::vector<int> FIFTEEN_GOAL_STATE {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, constants::EMPTY};

// TEST_CASE( "Solver Constructor", "[main]" )
// {
//     std::vector<int> initialState {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};

//     SECTION("Constructor with Vector", "[some_details]")
//     {
//         Solver<constants::EIGHT_PUZZLE_SIZE> s = Solver<constants::EIGHT_PUZZLE_SIZE>(initialState);
//         // convert it to be of type Tester so we can get all its protected members
//         Tester t = static_cast<const Tester&>(s);
//         REQUIRE (t.GetVisited().empty());
//     }

//     SECTION("Constructor with Node", "[some_details]")
//     {
//         Node<constants::EIGHT_PUZZLE_SIZE> initalNode = Node<constants::EIGHT_PUZZLE_SIZE>(initialState);
//         Solver<constants::EIGHT_PUZZLE_SIZE> s = Solver<constants::EIGHT_PUZZLE_SIZE>(initalNode);
//         // convert it to be of type Tester so we can get all its protected members
//         Tester t = static_cast<const Tester&>(s);
//         REQUIRE (t.GetVisited().empty());
//     }
// }

// TEST_CASE( "Solver Initialization", "[main]" )
// {
//     std::vector<int> initialState {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
//     Solver<constants::EIGHT_PUZZLE_SIZE> s = Solver<constants::EIGHT_PUZZLE_SIZE><constants::EIGHT_PUZZLE_SIZE>(initialState);
//     Node<constants::EIGHT_PUZZLE_SIZE> actualNode = Node<constants::EIGHT_PUZZLE_SIZE>(initialState);

//     // convert it to be of type Tester so we can get all its protected members
//     Tester t = static_cast<const Tester&>(s);

//     SECTION("Visited", "[some_details]")
//     {
//         REQUIRE (t.GetVisited().empty());
//     }

//     SECTION("Priority Queue", "[some_details]")
//     {
//         auto pq = t.GetPQ();
//         REQUIRE (pq.empty() == false);

//         std::vector<Node<constants::EIGHT_PUZZLE_SIZE>> vec = GetContainer(pq);
        
//         REQUIRE (vec.size() == 1);
//         REQUIRE (vec.front() == actualNode);
//     }

//     SECTION("Current Node", "[some_details]")
//     {
//         REQUIRE (t.GetStartNode() == actualNode);
//     }

//     SECTION("Steps", "[some_details]")
//     {
//         REQUIRE (t.GetIterations() == 0);
//     }
// }

// TEST_CASE( "Priority Queue", "[main]" )
// {
//     Node<constants::EIGHT_PUZZLE_SIZE> actualZero = Node<constants::EIGHT_PUZZLE_SIZE>(EIGHT_GOAL_STATE);
//     Node<constants::EIGHT_PUZZLE_SIZE> actualOne1 = Node<constants::EIGHT_PUZZLE_SIZE>({1, 2, 3, 4, 5, constants::EMPTY, 7, 8, 6});
//     Node<constants::EIGHT_PUZZLE_SIZE> actualOne2 = Node<constants::EIGHT_PUZZLE_SIZE>({1, 2, 3, 4, 5, 6, 7, constants::EMPTY, 8});
//     Node<constants::EIGHT_PUZZLE_SIZE> actualTwo = Node<constants::EIGHT_PUZZLE_SIZE>({1, 2, 3, 4, constants::EMPTY, 6, 7, 5, 8});

//     SECTION("Three Nodes with Three Distinct Values", "[some_details]")
//     {
//         Solver<constants::EIGHT_PUZZLE_SIZE> s = Solver<constants::EIGHT_PUZZLE_SIZE>(EIGHT_GOAL_STATE);
//         Tester t = static_cast<const Tester&>(s);

//         // gets the reference of the priority queue of the Solver instance
//         auto& pq = t.GetPQ();

//         // inject the values directly
//         pq.push(actualOne1);
//         pq.push(actualTwo);

//         std::vector<Node<constants::EIGHT_PUZZLE_SIZE>> vec = GetContainer(pq);
//         REQUIRE (vec.size() == 3);
//         auto itr = vec.begin();
//         REQUIRE (*itr++ == actualZero);
//         REQUIRE (*itr++ == actualOne1);
//         REQUIRE (*itr == actualTwo);
//     }

//     SECTION("Two Nodes with Two Distinct Values", "[some_details]")
//     {
//         Solver<constants::EIGHT_PUZZLE_SIZE> s = Solver<constants::EIGHT_PUZZLE_SIZE>(EIGHT_GOAL_STATE);
//         Tester t = static_cast<const Tester&>(s);

//         // gets the reference of the priority queue of the Solver instance
//         auto& pq = t.GetPQ();

//         // inject the values directly
//         pq.push(actualOne1);
//         pq.push(actualOne2);

//         std::vector<Node<constants::EIGHT_PUZZLE_SIZE>> vec = GetContainer(pq);
//         REQUIRE (vec.size() == 3);
//         auto itr = vec.begin();
//         REQUIRE (*itr++ == actualZero);
//         bool statement2 = *itr == actualOne1 || *itr++ == actualOne2;
//         REQUIRE (statement2);
//         bool statement3 = *itr == actualOne1 || *itr++ == actualOne2;
//         REQUIRE (statement3);
//     }
// }

TEST_CASE( "Trivial 8 Puzzle Problems", "[main]" )
{
    SECTION("Puzzle 1", "[finished]")
    {
        Solver<constants::EIGHT_PUZZLE_SIZE> s = Solver<constants::EIGHT_PUZZLE_SIZE>(EIGHT_GOAL_STATE);
        auto [isSolved, totalIterations] = s.SolvePuzzle();

        REQUIRE (isSolved);
        REQUIRE (totalIterations == 0);
    }

    SECTION("Puzzle 2", "[unsolvable]")
    {
        std::vector<int> initialState {8, 1, 2, constants::EMPTY, 4, 3, 7, 6, 5};
        Solver<constants::EIGHT_PUZZLE_SIZE> s = Solver<constants::EIGHT_PUZZLE_SIZE>(initialState);
        auto [isSolved, totalIterations] = s.SolvePuzzle();

        REQUIRE (isSolved == false);
        REQUIRE (totalIterations == INT_MAX);
    }
}

TEST_CASE( "Trivial 15 Puzzle Problems", "[main]" )
{
    SECTION("Puzzle 1", "[finished]")
    {
        Solver<constants::FIFTEEN_PUZZLE_SIZE> s = Solver<constants::FIFTEEN_PUZZLE_SIZE>(FIFTEEN_GOAL_STATE);
        auto [isSolved, totalIterations] = s.SolvePuzzle();

        REQUIRE (isSolved);
        REQUIRE (totalIterations == 0);
    }

    SECTION("Puzzle 2", "[unsolvable]")
    {
        std::vector<int> initialState {15, 14, 8, 12, 10, 11, 9, 13, 2, 6, 5, 1, 3, 7, 4, constants::EMPTY};
        Solver<constants::FIFTEEN_PUZZLE_SIZE> s = Solver<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
        auto [isSolved, totalIterations] = s.SolvePuzzle();

        REQUIRE (isSolved == false);
        REQUIRE (totalIterations == INT_MAX);
    }
}

TEST_CASE( "Solve 8 Puzzle Problem with Least Steps", "[main]" )
{
    // source: https://deniz.co/8-puzzle-solver/

    SECTION("Puzzle 1", "[general case]")
    {
        std::vector<int> initialState {1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6};
        Solver<constants::EIGHT_PUZZLE_SIZE> s = Solver<constants::EIGHT_PUZZLE_SIZE>(initialState);
        auto [isSolved, totalIterations] = s.SolvePuzzle();

        REQUIRE (isSolved);
        REQUIRE (s.GetDepth() == 2);
    }

    SECTION("Puzzle 2", "[general case]")
    {
        std::vector<int> initialState {5, 3, 6, 2, constants::EMPTY, 8, 4, 1, 7};
        Solver<constants::EIGHT_PUZZLE_SIZE> s = Solver<constants::EIGHT_PUZZLE_SIZE>(initialState);
        auto [isSolved, totalIterations] = s.SolvePuzzle();

        std::vector<Node<constants::EIGHT_PUZZLE_SIZE>> solution = s.GetSolution();
        REQUIRE (solution.front() == Node<constants::EIGHT_PUZZLE_SIZE>(initialState));
        REQUIRE (solution.back() == Node<constants::EIGHT_PUZZLE_SIZE>(EIGHT_GOAL_STATE));

        REQUIRE (isSolved);
        REQUIRE (s.GetDepth() == 14);
    }

    SECTION("Puzzle 3", "[general case]")
    {
        std::vector<int> initialState {4, 8, 7, 1, constants::EMPTY, 3, 6, 5, 2};
        Node<constants::EIGHT_PUZZLE_SIZE> start = Node<constants::EIGHT_PUZZLE_SIZE>(initialState);

        REQUIRE(start.GetManhattanDistance() == 16);

        Solver<constants::EIGHT_PUZZLE_SIZE> s = Solver<constants::EIGHT_PUZZLE_SIZE>(initialState);
        auto [isSolved, totalIterations] = s.SolvePuzzle();

        std::vector<Node<constants::EIGHT_PUZZLE_SIZE>> solution = s.GetSolution();
        REQUIRE (solution.front() == Node<constants::EIGHT_PUZZLE_SIZE>(initialState));
        REQUIRE (solution.back() == Node<constants::EIGHT_PUZZLE_SIZE>(EIGHT_GOAL_STATE));

        REQUIRE (isSolved);
        REQUIRE (s.GetDepth() == 26);
    }

    SECTION("Puzzle 4", "[general case]")
    {
        std::vector<int> initialState {3, 7, 8, constants::EMPTY, 2, 1, 4, 6, 5};
        Node<constants::EIGHT_PUZZLE_SIZE> start = Node<constants::EIGHT_PUZZLE_SIZE>(initialState);

        REQUIRE(start.GetManhattanDistance() == 17);

        Solver<constants::EIGHT_PUZZLE_SIZE> s = Solver<constants::EIGHT_PUZZLE_SIZE>(initialState);
        auto [isSolved, totalIterations] = s.SolvePuzzle();

        std::vector<Node<constants::EIGHT_PUZZLE_SIZE>> solution = s.GetSolution();
        REQUIRE (solution.front() == Node<constants::EIGHT_PUZZLE_SIZE>(initialState));
        REQUIRE (solution.back() == Node<constants::EIGHT_PUZZLE_SIZE>(EIGHT_GOAL_STATE));

        REQUIRE (isSolved);
        REQUIRE (s.GetDepth() == 23);
    }
}

TEST_CASE( "Solve 15 Puzzle Problem with Least Steps", "[main]" )
{
    SECTION("Puzzle 0", "[trivial case]")
    {
        Solver<constants::FIFTEEN_PUZZLE_SIZE> s = Solver<constants::FIFTEEN_PUZZLE_SIZE>(FIFTEEN_GOAL_STATE);
        auto [isSolved, _] = s.SolvePuzzle();

        REQUIRE (isSolved);
        REQUIRE (s.GetDepth() == 0);
    }

    SECTION("Puzzle 1", "[general case]")
    {
        std::vector<int> initialState {7, 2, 9, 6, 8, constants::EMPTY, 3, 13, 4, 1, 10, 5, 14, 15, 11, 12};
        auto n = Node<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
        Solver<constants::FIFTEEN_PUZZLE_SIZE> s = Solver<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
        auto [isSolved, _] = s.SolvePuzzle();

        std::vector<Node<constants::FIFTEEN_PUZZLE_SIZE>> solution = s.GetSolution();

        REQUIRE (n.GetManhattanDistance() == 36);
        REQUIRE (isSolved);
        bool solutionStart = isSolved && solution.front() == Node<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
        REQUIRE (solutionStart);
        bool solutionEnd = isSolved && solution.back() == Node<constants::FIFTEEN_PUZZLE_SIZE>(FIFTEEN_GOAL_STATE);
        REQUIRE (solutionEnd);
        REQUIRE (s.GetDepth() == 48);
    }

    SECTION("Puzzle 2", "[general case]")
    {
        std::vector<int> initialState {14, 7, 9, 13, constants::EMPTY, 2, 11, 8, 15, 1, 4, 10, 6, 3, 5, 12};
        auto n = Node<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
        Solver<constants::FIFTEEN_PUZZLE_SIZE> s = Solver<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
        auto [isSolved, _] = s.SolvePuzzle();

        std::vector<Node<constants::FIFTEEN_PUZZLE_SIZE>> solution = s.GetSolution();

        REQUIRE (n.GetManhattanDistance() == 41);
        REQUIRE (isSolved);
        bool solutionStart = isSolved && solution.front() == Node<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
        REQUIRE (solutionStart);
        bool solutionEnd = isSolved && solution.back() == Node<constants::FIFTEEN_PUZZLE_SIZE>(FIFTEEN_GOAL_STATE);
        REQUIRE (solutionEnd);
        REQUIRE (s.GetDepth() == 51);
    }

    SECTION("Puzzle 3", "[general case]")
    {
        std::vector<int> initialState {3, 1, 11, 10, 13, 8, 5, 12, 15, 2, 7, 9, 6, constants::EMPTY, 4, 14};
        auto n = Node<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
        Solver<constants::FIFTEEN_PUZZLE_SIZE> s = Solver<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
        auto [isSolved, _] = s.SolvePuzzle();

        std::vector<Node<constants::FIFTEEN_PUZZLE_SIZE>> solution = s.GetSolution();

        REQUIRE (n.GetManhattanDistance() == 34);
        REQUIRE (isSolved);
        bool solutionStart = isSolved && solution.front() == Node<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
        REQUIRE (solutionStart);
        bool solutionEnd = isSolved && solution.back() == Node<constants::FIFTEEN_PUZZLE_SIZE>(FIFTEEN_GOAL_STATE);
        REQUIRE (solutionEnd);
        REQUIRE (s.GetDepth() == 52);
    }

    SECTION("Puzzle 4", "[general case]")
    {
        std::vector<int> initialState {13, 4, 2, 3, 12, 6, 5, 9, 14, 10, 1, 8, constants::EMPTY, 7, 11, 15};
        auto n = Node<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
        Solver<constants::FIFTEEN_PUZZLE_SIZE> s = Solver<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
        auto [isSolved, _] = s.SolvePuzzle();

        std::vector<Node<constants::FIFTEEN_PUZZLE_SIZE>> solution = s.GetSolution();

        REQUIRE (n.GetManhattanDistance() == 29);
        REQUIRE (isSolved);
        bool solutionStart = isSolved && solution.front() == Node<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
        REQUIRE (solutionStart);
        bool solutionEnd = isSolved && solution.back() == Node<constants::FIFTEEN_PUZZLE_SIZE>(FIFTEEN_GOAL_STATE);
        REQUIRE (solutionEnd);
        REQUIRE (s.GetDepth() == 47);
    }

    // SECTION("Puzzle 5", "[hard case]")
    // {
    //     std::vector<int> initialState {8, 9, 13, 4, 15, 14, 6, 11, 7, 2, constants::EMPTY, 12, 5, 3, 10, 1};
    //     auto n = Node<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
    //     Solver<constants::FIFTEEN_PUZZLE_SIZE> s = Solver<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
    //     auto [isSolved, _] = s.SolvePuzzle();

    //     std::vector<Node<constants::FIFTEEN_PUZZLE_SIZE>> solution = s.GetSolution();

    //     REQUIRE (isSolved);
    //     bool solutionStart = isSolved && solution.front() == Node<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
    //     REQUIRE (solutionStart);
    //     bool solutionEnd = isSolved && solution.back() == Node<constants::FIFTEEN_PUZZLE_SIZE>(FIFTEEN_GOAL_STATE);
    //     REQUIRE (solutionEnd);
    //     REQUIRE (s.GetDepth() == 58);
    // }

    SECTION("Puzzle 6", "[general case]")   
    {
        std::vector<int> initialState {10, 13, 5, 4, 6, constants::EMPTY, 15, 14, 3, 11, 9, 8, 7, 1, 12, 2};
        auto n = Node<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
        Solver<constants::FIFTEEN_PUZZLE_SIZE> s = Solver<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
        auto [isSolved, _] = s.SolvePuzzle();

        std::vector<Node<constants::FIFTEEN_PUZZLE_SIZE>> solution = s.GetSolution();

        REQUIRE (isSolved);
        bool solutionStart = isSolved && solution.front() == Node<constants::FIFTEEN_PUZZLE_SIZE>(initialState);
        REQUIRE (solutionStart);
        bool solutionEnd = isSolved && solution.back() == Node<constants::FIFTEEN_PUZZLE_SIZE>(FIFTEEN_GOAL_STATE);
        REQUIRE (solutionEnd);
        REQUIRE (s.GetDepth() == 50);
    }
}
