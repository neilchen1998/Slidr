#include <vector>   // std::vector
#include <fstream>  // std::ofstream
#include <nanobench.h>  // ankerl::nanobench::Bench

#include "slidr/solver/solverlib.hpp" // Solver
#include "slidr/constants/constantslib.hpp"   // constants::EMPTY

using BucketMinPQ = BucketQueue<std::shared_ptr<Node>, unsigned int, std::greater<Node>>;
using BucketMinPQ32 = BucketQueue<std::shared_ptr<Node>, unsigned int, std::greater<Node>, 32>;

int main()
{
    std::ofstream file("./build/benchmarks/solver-results.csv");
    ankerl::nanobench::Bench bench;

    auto bucket = BucketMinPQ();
    auto bucket32 = BucketMinPQ32();

    // easy puzzles
    std::vector<int> easy0 {1, 3, 5, 8, 7, 2, constants::EMPTY, 4, 6};  // 12
    std::vector<int> easy1 {7, 4, 1, 5, 2, 3, 8, 6, constants::EMPTY};  // 16
    std::vector<int> easy2 {2, 3, 1, 4, constants::EMPTY, 8, 5, 7, 6};  // 18

    std::vector<int> mid0 {1, 2, 7, 4, constants::EMPTY, 5, 8, 3, 6};  // 20
    std::vector<int> mid1 {1, 7, constants::EMPTY, 8, 4, 3, 5, 2, 6};  // 22
    std::vector<int> mid2 {7, 3, 2, 6, constants::EMPTY, 5, 8, 1 ,4};  // 24
    std::vector<int> mid3 {constants::EMPTY, 8, 4, 7, 6, 2, 1, 3, 5};  // 26

    // hard puzzles
    std::vector<int> hard0 {8, 6, 7, 2, 5, 4, 3, constants::EMPTY, 1};  // 31
    std::vector<int> hard1 {6, 4, 7, 8, 5, constants::EMPTY, 3, 2, 1};  // 31

    bench.minEpochIterations(10).title("Group 1: Easy Puzzles")
        .run("Priority Queue Solver", [&]
    {
        slidr::Solver(easy0).SolvePuzzle();
        slidr::Solver(easy1).SolvePuzzle();
        slidr::Solver(easy2).SolvePuzzle();
    })
        .run("Bucket Queue Solver", [&]
    {
        slidr::Solver<BucketMinPQ>(easy0, bucket).SolvePuzzle();
        slidr::Solver<BucketMinPQ>(easy1, bucket).SolvePuzzle();
        slidr::Solver<BucketMinPQ>(easy2, bucket).SolvePuzzle();
    })
        .run("Bucket Queue Solver (32)", [&]
    {
        slidr::Solver<BucketMinPQ32>(easy0, bucket32).SolvePuzzle();
        slidr::Solver<BucketMinPQ32>(easy1, bucket32).SolvePuzzle();
        slidr::Solver<BucketMinPQ32>(easy2, bucket32).SolvePuzzle();
    });

    bench.minEpochIterations(10).title("Group 2: Medium Puzzles")
        .run("Priority Queue Solver", [&]
    {
        slidr::Solver(mid0).SolvePuzzle();
        slidr::Solver(mid1).SolvePuzzle();
        slidr::Solver(mid2).SolvePuzzle();
        slidr::Solver(mid3).SolvePuzzle();
    })
        .run("Bucket Queue Solver", [&]
    {
        slidr::Solver<BucketMinPQ>(mid0, bucket).SolvePuzzle();
        slidr::Solver<BucketMinPQ>(mid1, bucket).SolvePuzzle();
        slidr::Solver<BucketMinPQ>(mid2, bucket).SolvePuzzle();
        slidr::Solver<BucketMinPQ>(mid3, bucket).SolvePuzzle();
    })
        .run("Bucket Queue Solver (32)", [&]
    {
        slidr::Solver<BucketMinPQ32>(mid0, bucket32).SolvePuzzle();
        slidr::Solver<BucketMinPQ32>(mid1, bucket32).SolvePuzzle();
        slidr::Solver<BucketMinPQ32>(mid2, bucket32).SolvePuzzle();
        slidr::Solver<BucketMinPQ32>(mid3, bucket32).SolvePuzzle();
    });

    bench.minEpochIterations(10).title("Group 3: Hard Puzzles")
        .run("Priority Queue Solver", [&]
    {
        slidr::Solver(hard0).SolvePuzzle();
        slidr::Solver(hard1).SolvePuzzle();
    })
        .run("Bucket Queue Solver", [&]
    {
        slidr::Solver<BucketMinPQ>(hard0, bucket).SolvePuzzle();
        slidr::Solver<BucketMinPQ>(hard1, bucket).SolvePuzzle();
    });

    // Render the results to a csv file
    bench.render(ankerl::nanobench::templates::csv(), file);
}
