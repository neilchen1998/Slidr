#include <vector>
#include <concepts>
#include <span>
#include <random>
#include <chrono>
#include <nanobench.h>
#include <boost/functional/hash.hpp>

#include "constants/constantslib.hpp"
#include "math/mathlib.hpp"

template <std::integral T>
inline std::size_t hash_vector(const std::vector<T>& vec)
{
    // Initialize hash value with the size of the span
    std::size_t h {vec.size()};

    // Loop through each element and hash with the element and its position
    for (std::size_t i {0}; i < vec.size(); ++i)
    {
        hash_combine(h, vec[i], i);
    }

    return h;
}

template <std::integral T, std::integral ... Args>
inline void boost_hash_combine(std::size_t& seed, const T& u, const Args&... v)
{
    // Hash the first argument
    boost::hash_combine(seed, u);

    // Hash the rest of the arguments
    (hash_combine(seed, v), ...);
}

template <std::integral T, std::integral ... Args>
inline void simple_hash_combine(std::size_t& seed, const T& u, const Args&... v)
{
    // Hash the first argument
    seed ^= (std::hash<T>{}(u) << 1);

    // Hash the rest of the arguments
    (hash_combine(seed, v), ...);
}

int main() {

    constexpr std::size_t N {constants::EIGHT_PUZZLE_NUM};
    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<int> vec(N);
    std::uniform_int_distribution<> distrib(1, 8);
    for (auto& v : vec)
    {
        v = distrib(gen);
    }

    ankerl::nanobench::Bench().run("hash_vector", [&] {
        auto ret = hash_vector(vec);
        ankerl::nanobench::doNotOptimizeAway(ret);
    });

    ankerl::nanobench::Bench().run("hash_range", [&] {
        auto ret = hash_range(std::span(vec));
        ankerl::nanobench::doNotOptimizeAway(ret);
    });

    ankerl::nanobench::Bench().run("hash_combine", [&] {
        std::size_t h = distrib(gen);
        hash_combine(h, distrib(gen), distrib(gen));
    });

    ankerl::nanobench::Bench().run("boost_hash_combine", [&] {
        std::size_t h = distrib(gen);
        boost_hash_combine(h, distrib(gen), distrib(gen));
    });

    ankerl::nanobench::Bench().run("simple_hash_combine", [&] {
        std::size_t h = distrib(gen);
        simple_hash_combine(h, distrib(gen), distrib(gen));
    });
}