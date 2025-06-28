#include <vector>   // std::vector
#include <random>   // std::mt19937
#include <span> // std::span
#include <nanobench.h>  // ankerl::nanobench::Bench
#include <ranges>   // std::views::iota
#include <algorithm>   // std::shuffle
#include <chrono>   // std::chrono::steady_clock::now

#include "constants/constantslib.hpp"
#include "node/nodelib.hpp"

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

int main() {
    
    constexpr std::size_t N {constants::EIGHT_PUZZLE_NUM};
    std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());

    auto range = std::views::iota(0, constants::EIGHT_PUZZLE_NUM);
    std::vector<int> vec(range.begin(), range.end());
    vec.back() = constants::EMPTY;

    std::shuffle(vec.begin(), vec.end(), gen);

    ankerl::nanobench::Bench().run("GetManhattanDistance", [&] {
        auto ret = GetManhattanDistance(std::span(vec));
        ankerl::nanobench::doNotOptimizeAway(ret);
    });

    ankerl::nanobench::Bench().run("GetManhattanDistanceAccumulate", [&] {
        auto ret = GetManhattanDistanceAccumulate(std::span(vec));
        ankerl::nanobench::doNotOptimizeAway(ret);
    });

    ankerl::nanobench::Bench().run("GetManhattanDistanceReduce", [&] {
        auto ret = GetManhattanDistanceReduce(std::span(vec));
        ankerl::nanobench::doNotOptimizeAway(ret);
    });
}