#define CATCH_CONFIG_MAIN

#include <cstddef>
#include <numeric>
#include <vector>   // std::vector
#include <span> // std::span
#include <algorithm> // std::shuffle
#include <random>   // std::mt19937_64
#include <cmath>    // std::sqrt
#include <catch2/catch_test_macros.hpp> // TEST_CASE, SECTION, REQUIRE
#include <catch2/catch_approx.hpp>  // Catch::Approx
#include <catch2/generators/catch_generators.hpp>   // GENERATE

#ifdef DEBUG
#include <fmt/core.h>
#endif

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/sum.hpp>
#include <boost/accumulators/statistics/variance.hpp> // Variance is used to derive standard deviation

#include "slidr/constants/constantslib.hpp"   // constants::EMPTY
#include "slidr/math/mathlib.hpp" // hash_combine_simple, hash_range, GetUniformIntDist

/// @brief Hashes a single arguments with an initial hash value
/// @tparam T The argument type
/// @param seed The initial hash value
/// @param u The argument
template <std::integral T>
inline void hash_combine_simple(std::size_t& seed, const T& u)
{
    seed ^= std::hash<T>{}(u) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

TEST_CASE( "Hash Combine", "[main]" )
{
    std::size_t h0 = GetUniformIntDist(1, constants::EMPTY);
    std::size_t h1 = h0;
    const std::size_t v = GetUniformIntDist(1, constants::EMPTY);
    const std::size_t u = GetUniformIntDist(1, constants::EMPTY);
    const std::size_t w = GetUniformIntDist(1, constants::EMPTY);
    const std::size_t x = GetUniformIntDist(1, constants::EMPTY);
    const std::size_t y = GetUniformIntDist(1, constants::EMPTY);
    const std::size_t z = GetUniformIntDist(1, constants::EMPTY);

    SECTION ( "Two parameters", "[main]" )
    {
        hash_combine(h0, u, v);

        hash_combine_simple(h1, u);
        hash_combine_simple(h1, v);

        REQUIRE (h0 == h1);
    }

    SECTION ( "Four parameters", "[main]" )
    {
        hash_combine(h0, u, v, w, x);

        hash_combine_simple(h1, u);
        hash_combine_simple(h1, v);
        hash_combine_simple(h1, w);
        hash_combine_simple(h1, x);

        REQUIRE (h0 == h1);
    }

    SECTION ( "Six parameters", "[main]" )
    {
        hash_combine(h0, u, v, w, x, y, z);

        hash_combine_simple(h1, u);
        hash_combine_simple(h1, v);
        hash_combine_simple(h1, w);
        hash_combine_simple(h1, x);
        hash_combine_simple(h1, y);
        hash_combine_simple(h1, z);

        REQUIRE (h0 == h1);
    }
}

TEST_CASE( "Hash Range Function", "[main]" )
{
    std::mt19937_64 gen(41);

    std::vector<int> v1 {constants::EMPTY, 1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> v2 {3, 1, constants::EMPTY, 2, 8, 7, 6, 5, 4};
    std::vector<int> v3 {v2};
    std::vector<int> v4 {v1};
    std::vector<int> v5 {v1};

    // Shuffle v4 and v5
    std::shuffle(v4.begin(), v4.end(), gen);
    std::shuffle(v5.begin(), v5.end(), gen);

    // Get their hash values
    std::size_t hash1 = hash_range(std::span(v1.begin(), v1.end()));
    std::size_t hash2 = hash_range(std::span(v2.begin(), v2.end()));
    std::size_t hash3 = hash_range(std::span(v3.begin(), v3.end()));
    std::size_t hash4 = hash_range(std::span(v4.begin(), v4.end()));
    std::size_t hash5 = hash_range(std::span(v5.begin(), v5.end()));

    SECTION ( "Different Node", "[main]" )
    {
        REQUIRE (hash1 != hash2);
        REQUIRE (hash4 != hash2);
        REQUIRE (hash4 != hash1);
        REQUIRE (hash4 != hash5);
    }

    SECTION ( "Same Node", "[main]" )
    {
        REQUIRE (hash1 == hash1);
        REQUIRE (hash2 == hash2);
        REQUIRE (hash3 == hash3);
        REQUIRE (hash4 == hash4);
        REQUIRE (hash2 == hash3);
    }
}

TEST_CASE( "Normal Distribution Function", "[main]" )
{
    using namespace boost::accumulators;

    struct NormalDistributionParams
    {
        float mean;
        float stddev;
    };

    constexpr size_t N = 1'000;

    // Create two sets of normal distributions
    // This test cases will be run twice, each time with different means and standard deviations
    auto curves = GENERATE(NormalDistributionParams{0.0f, 1.0f}, NormalDistributionParams{1.5f, 10.0f});

    // Get the parameters
    const float trueMean = curves.mean;
    const float trueStddev = curves.stddev;

    // Generate samples
    std::array<float, N> samples;
    for (auto& sample : samples)
    {
        sample = GetNormalFloatDist(trueMean, trueStddev);
    }

    // Calculate the sum and the variance
    accumulator_set<float, stats<tag::sum, tag::variance>> acc;
    std::for_each(samples.cbegin(), samples.cend(), [&](float sample)
    {
        acc(sample);
    });

    // Calculate the mean and the standard deviation
    double mu = sum(acc) / N;
    double sigma = std::sqrt(variance(acc));

    // Calculate the standard error of the mean (SEM) and the standard error of the standard deviation (SES)
    const float SEM = trueStddev / std::sqrt(N);
    const float SES = trueStddev / std::sqrt(2.0f * N);

    SECTION ( "Mean", "[main]" )
    {
        // 3 times the SEM should cover 99% of the cases
        REQUIRE (Catch::Approx(mu).margin(3 * SEM) == trueMean);
    }

    SECTION ( "Standard Deviation", "[main]" )
    {
        // 3 times the SES should cover 99% of the cases
        REQUIRE (Catch::Approx(sigma).margin(3 * SES) == trueStddev);
    }
}

TEST_CASE( "Uniform Real Distribution Function", "[main]" )
{
    using namespace boost::accumulators;

    struct UniformRealDistribution
    {
        float min;
        float max;
    };

    constexpr size_t N = 1'000;

    // Create two sets of normal distributions
    // This test cases will be run twice, each time with different means and standard deviations
    auto dists = GENERATE(UniformRealDistribution{-2.5f, 1.0f}, UniformRealDistribution{-15.2f, -2.7f}, UniformRealDistribution{5.4f, 6.7f});

    // Get the parameters
    const float min = dists.min;
    const float max = dists.max;
    const float trueMean = 0.5 * (max + min);
    const float trueStddev = std::sqrt(1 / 12.0f) * (max - min);

    // Generate samples
    std::array<float, N> samples;
    for (auto& sample : samples)
    {
        sample = GetUniformFloatDist(min, max);
    }

    // Calculate the sum and the variance
    accumulator_set<float, stats<tag::sum, tag::variance>> acc;
    std::for_each(samples.cbegin(), samples.cend(), [&](float sample)
    {
        acc(sample);
    });

    // Calculate the mean and the standard deviation
    double mu = sum(acc) / N;
    double sigma = std::sqrt(variance(acc));

    // Calculate the standard error of the mean (SEM) and the standard error of the standard deviation (SES)
    // NOTE: since there is no standard way of calculating those values for uniform distributions, we can use the law of big number
    // therefore these of a uniform distribution can be approximated to those of a standard distribution
    const float SEM = trueStddev / std::sqrt(N);
    const float SES = trueStddev / std::sqrt(2.0f * N);

    SECTION ( "Bounds", "[main]" )
    {
        for (const auto& sample : samples)
        {
            REQUIRE (sample >= min);
            REQUIRE (sample <= max);
        }
    }

    SECTION ( "Distribution", "[main]" )
    {
        #ifdef DEBUG
        const std::string info = fmt::format("min: {:.3f}\tmax:{:.3f}\tmu:{:.3f}\tsigma:{:.3f}\tSEM:{:.3f}\tSES:{:.3f}", min, max, mu, sigma, SEM, SES);
        INFO(info);
        #endif
        REQUIRE (Catch::Approx(mu).margin(3 * SEM) == trueMean);
        REQUIRE (Catch::Approx(sigma).margin(3 * SES) == trueStddev);
    }
}
