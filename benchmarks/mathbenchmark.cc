#include <vector>   // std::vector
#include <random>   // std::mt19937
#include <span> // std::span
#include <nanobench.h>  // ankerl::nanobench::Bench
#include <fstream>  // std::ofstream
#include <boost/functional/hash.hpp>    // boost::hash_combine

#include "constants/constantslib.hpp"   // constants::EMPTY, etc.
#include "math/mathlib.hpp" // hash_combine, hash_range

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

template <std::integral T, std::integral... Args>
inline void boost_hash_combine(std::size_t& seed, const T& u, const Args&... v)
{
    // Hash the first argument
    boost::hash_combine(seed, u);

    // Hash the rest of the arguments
    (boost::hash_combine(seed, v), ...);
}

template <std::integral T, std::integral... Args>
inline void simple_hash_combine(std::size_t& seed, const T& u, const Args&... v)
{
    // Hash the first argument
    seed ^= (std::hash<T>{}(u) << 1);

    // Hash the rest of the arguments
    (hash_combine(seed, v), ...);
}

int main()
{
    std::ofstream file("./build/benchmarks/math-results.csv");
    ankerl::nanobench::Bench bench;

    // Generate the seed, the generator, and the distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, constants::EMPTY);
    
    // Generate 3 values
    std::size_t h = distrib(gen);
    std::size_t u = distrib(gen);
    std::size_t v = distrib(gen);
    
    // Generate the vector
    constexpr std::size_t N {constants::EIGHT_PUZZLE_NUM};
    std::vector<int> vec(N);
    for (auto& v : vec)
    {
        v = distrib(gen);
    }

    bench.title("Hash & Combine Two Values")
        .run("hash_combine", [&]
    {
        hash_combine(h, u, v);
        ankerl::nanobench::doNotOptimizeAway(h);
    })
        .run("boost_hash_combine", [&]
    {
        boost_hash_combine(h, u, v);
        ankerl::nanobench::doNotOptimizeAway(h);
    })
        .run("simple_hash_combine", [&]
    {
        simple_hash_combine(h, u, v);
        ankerl::nanobench::doNotOptimizeAway(h);
    });

    bench.title("Hash A Vector")
        .run("hash_vector", [&]
    {
        auto ret = hash_vector(vec);
        ankerl::nanobench::doNotOptimizeAway(ret);
    })
        .run("hash_range", [&]
    {
        auto ret = hash_range(std::span(vec));
        ankerl::nanobench::doNotOptimizeAway(ret);
    });

    // Render the results to a csv file
    bench.render(ankerl::nanobench::templates::csv(), file);
}
