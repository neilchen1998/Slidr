#include <vector>   // std::vector
#include <random>   // std::mt19937
#include <span> // std::span
#include <ranges>   // std::views::iota
#include <algorithm>   // std::shuffle
#include <chrono>   // std::chrono::steady_clock::now
#include <fstream>  // std::ofstream
#include <nanobench.h>  // ankerl::nanobench::Bench

#include "constants/constantslib.hpp"   // constants::EIGHT_PUZZLE_SIZE

int GetManhattanDistance(std::span<int> s)
{
    int manhattanDistance = 0;
    for (auto i = 0; i < constants::EIGHT_PUZZLE_NUM; ++i)
    {
        if (s[i] != constants::EMPTY)
        {
            int curRow = (s[i] - 1) / constants::EIGHT_PUZZLE_SIZE;
            int curCol = (s[i] - 1) % constants::EIGHT_PUZZLE_SIZE;

            int goalRow = i / constants::EIGHT_PUZZLE_SIZE;
            int goalCol = i % constants::EIGHT_PUZZLE_SIZE;

            manhattanDistance += (std::abs(goalRow - curRow) + std::abs(goalCol - curCol));
        }
    }

    return manhattanDistance;
}


int GetManhattanDistanceAccumulate(std::span<int> s)
{
    auto v = std::views::iota(0, constants::EIGHT_PUZZLE_NUM);
    return std::accumulate(
        v.begin(),
        v.end(),
        0,
        [&](int acc, int i) {
            if (s[i] == constants::EMPTY)
            return acc;
            
            int curRow = (s[i] - 1) / constants::EIGHT_PUZZLE_SIZE;
            int curCol = (s[i] - 1) % constants::EIGHT_PUZZLE_SIZE;
            int goalRow = i / constants::EIGHT_PUZZLE_SIZE;
            int goalCol = i % constants::EIGHT_PUZZLE_SIZE;
            
            return acc + std::abs(goalRow - curRow) + std::abs(goalCol - curCol);
        }
    );
}

int GetManhattanDistanceReduce(std::span<int> s)
{
    auto v = std::views::iota(0, constants::EIGHT_PUZZLE_NUM);
    return std::reduce(
        v.begin(),
        v.end(),
        0,
        [&](int acc, int i) {
            if (s[i] == constants::EMPTY)
                return acc;

            int curRow = (s[i] - 1) / constants::EIGHT_PUZZLE_SIZE;
            int curCol = (s[i] - 1) % constants::EIGHT_PUZZLE_SIZE;
            int goalRow = i / constants::EIGHT_PUZZLE_SIZE;
            int goalCol = i % constants::EIGHT_PUZZLE_SIZE;

            return acc + std::abs(goalRow - curRow) + std::abs(goalCol - curCol);
        }
    );
}

int main()
{
    std::ofstream file("./build/benchmarks/node-results.csv");
    ankerl::nanobench::Bench bench;
    bench.title("Manhattan Distance Calculations");

    std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());

    auto range = std::views::iota(0, constants::EIGHT_PUZZLE_NUM);
    std::vector<int> vec(range.begin(), range.end());
    vec.back() = constants::EMPTY;

    std::shuffle(vec.begin(), vec.end(), gen);

    bench.run("GetManhattanDistance", [&] {
        auto ret = GetManhattanDistance(std::span(vec));
        ankerl::nanobench::doNotOptimizeAway(ret);
    });

    bench.run("GetManhattanDistanceAccumulate", [&] {
        auto ret = GetManhattanDistanceAccumulate(std::span(vec));
        ankerl::nanobench::doNotOptimizeAway(ret);
    });

    bench.run("GetManhattanDistanceReduce", [&] {
        auto ret = GetManhattanDistanceReduce(std::span(vec));
        ankerl::nanobench::doNotOptimizeAway(ret);
    });

    // Render the results to a csv file
    bench.render(ankerl::nanobench::templates::csv(), file);
}
