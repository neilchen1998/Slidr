#include <vector>   // std::vector
#include <fstream>  // std::fstream
#include <nanobench.h>  // ankerl::nanobench::Bench

#include "solver/solverlib.hpp" // Solver
#include "constants/constantslib.hpp"   // constants::EMPTY

using BucketMinPQ = BucketQueue<std::shared_ptr<Node>, unsigned int, std::greater<Node>>;
using BucketMinPQ25 = BucketQueue<std::shared_ptr<Node>, unsigned int, std::greater<Node>, 25>;

int main()
{
    std::ofstream file("./build/benchmarks/solver-results.csv");
    ankerl::nanobench::Bench bench;

    auto bucket = BucketMinPQ();
    auto bucket25 = BucketMinPQ25();

    std::vector<int> layout0 {1, 7, constants::EMPTY, 8, 4, 3, 5, 2, 6};
    std::vector<int> layout1 {6, 3, 8, 2, 1, 7, constants::EMPTY, 5, 4};
    std::vector<int> layout2 {7, 4, 1, 5, 2, 3, 8, 6, constants::EMPTY};
    std::vector<int> layout3 {1, 2, 7, 4, constants::EMPTY, 5, 8, 3, 6};
    std::vector<int> layout4 {2, 3, 1, 4, constants::EMPTY, 8, 5, 7, 6};

    bench.minEpochIterations(10)
        .run("Priority Queue Solver", [&]
    {
        Solver(layout0).SolvePuzzle();
        Solver(layout1).SolvePuzzle();
        Solver(layout2).SolvePuzzle();
        Solver(layout3).SolvePuzzle();
        Solver(layout4).SolvePuzzle();
    });

    bench.minEpochIterations(10)
        .run("Bucket Queue Solver", [&]
    {
        Solver<BucketMinPQ>(layout0, bucket).SolvePuzzle();
        Solver<BucketMinPQ>(layout1, bucket).SolvePuzzle();
        Solver<BucketMinPQ>(layout2, bucket).SolvePuzzle();
        Solver<BucketMinPQ>(layout3, bucket).SolvePuzzle();
        Solver<BucketMinPQ>(layout4, bucket).SolvePuzzle();
    });

    bench.minEpochIterations(10)
        .run("Bucket Queue Solver (25)", [&]
    {
        Solver<BucketMinPQ25>(layout0, bucket25).SolvePuzzle();
        Solver<BucketMinPQ25>(layout1, bucket25).SolvePuzzle();
        Solver<BucketMinPQ25>(layout2, bucket25).SolvePuzzle();
        Solver<BucketMinPQ25>(layout3, bucket25).SolvePuzzle();
        Solver<BucketMinPQ25>(layout4, bucket25).SolvePuzzle();
    });


    // Render the results to a csv file
    bench.render(ankerl::nanobench::templates::csv(), file);
}
