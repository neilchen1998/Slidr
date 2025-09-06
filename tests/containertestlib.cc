#include <iterator>
#define CATCH_CONFIG_MAIN

#include <string_view>    // std::string_view
#include <vector>    // std::vector
#include <functional>    // std::greater
#include <algorithm>   // std::sort
#include <queue>    // std::priority_queue
#include <limits> // std::numeric_limits
#include <random>   // std::random_device

#include <catch2/catch_test_macros.hpp> // TEST_CASE, SECTION, REQUIRE

#include "slidr/container/bucketqueuelib.hpp" // BucketQueue
#include "slidr/constants/constantslib.hpp" // constants::EMPTY
#include "slidr/node/nodelib.hpp"   // Node

TEST_CASE( "Basic Operations for Max Heap", "[main]" )
{
    auto bq = BucketQueue<int, std::size_t> {};
    std::priority_queue pq(std::less<std::size_t>{}, std::vector<int>{});

    const std::size_t N = 12;

    const int min_size_t = 0;
    const int max_size_t = 64 - 1;

    // Generate the seed, the generator, and the distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min_size_t, max_size_t);

    // Generate the vector
    for (std::size_t i = 0; i < (N - 2); ++i)
    {
        const std::size_t val = distrib(gen);

        // Push the random number into the queues
        bq.push(val);
        pq.push(val);
    }

    // Push the min value and the max value
    pq.push(min_size_t);
    pq.push(max_size_t);
    bq.push(min_size_t);
    bq.push(max_size_t);

    SECTION("Push", "[some_details]")
    {
        REQUIRE(bq.size() == pq.size());
    }

    SECTION("Top", "[some_details]")
    {
        REQUIRE(bq.top() == pq.top());
    }

    SECTION("Pop", "[some_details]")
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            REQUIRE(bq.top() == pq.top());
            bq.pop();
            pq.pop();
        }

        REQUIRE(bq.empty());
    }
}

TEST_CASE( "Basic Operations for Min Heap", "[main]" )
{
    auto bq = BucketQueue<int, unsigned short, std::greater<unsigned short>> {};
    std::priority_queue pq(std::greater<std::size_t>{}, std::vector<std::size_t>{});

    const std::size_t N = 12;

    const int min_size_t = 0;
    const int max_size_t = 64 - 1;

    // Generate the seed, the generator, and the distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min_size_t, max_size_t);

    // Generate the vector
    for (std::size_t i = 0; i < (N - 2); ++i)
    {
        const std::size_t val = distrib(gen);

        // Push the random number into the queues
        bq.push(val);
        pq.push(val);
    }

    // Push the min value and the max value
    pq.push(min_size_t);
    pq.push(max_size_t);
    bq.push(min_size_t);
    bq.push(max_size_t);

    SECTION("Push", "[some_details]")
    {
        REQUIRE(bq.size() == pq.size());
    }

    SECTION("Top", "[some_details]")
    {
        REQUIRE(bq.top() == pq.top());
    }

    SECTION("Pop", "[some_details]")
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            REQUIRE(bq.top() == pq.top());
            bq.pop();
            pq.pop();
        }

        REQUIRE(bq.empty());
    }
}

TEST_CASE( "Basic Operations for Max Heap (32)", "[main]" )
{
    auto bq = BucketQueue<int, std::size_t, std::less<std::size_t>, 32> {};
    std::priority_queue pq(std::less<std::size_t>{}, std::vector<int>{});

    const std::size_t N = 12;

    const int min_size_t = 0;
    const int max_size_t = 32 - 1;

    // Generate the seed, the generator, and the distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min_size_t, max_size_t);

    // Generate the vector
    for (std::size_t i = 0; i < (N - 2); ++i)
    {
        const std::size_t val = distrib(gen);

        // Push the random number into the queues
        bq.push(val);
        pq.push(val);
    }

    // Push the min value and the max value
    pq.push(min_size_t);
    pq.push(max_size_t);
    bq.push(min_size_t);
    bq.push(max_size_t);

    SECTION("Push", "[some_details]")
    {
        REQUIRE(bq.size() == pq.size());
    }

    SECTION("Top", "[some_details]")
    {
        REQUIRE(bq.top() == pq.top());
    }

    SECTION("Pop", "[some_details]")
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            REQUIRE(bq.top() == pq.top());
            bq.pop();
            pq.pop();
        }

        REQUIRE(bq.empty());
    }
}

TEST_CASE( "Basic Operations for Min Heap (32)", "[main]" )
{
    auto bq = BucketQueue<int, unsigned short, std::greater<unsigned short>> {};
    std::priority_queue pq(std::greater<std::size_t>{}, std::vector<std::size_t>{});

    const std::size_t N = 12;

    const int min_size_t = 0;
    const int max_size_t = 32 - 1;

    // Generate the seed, the generator, and the distribution
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min_size_t, max_size_t);

    // Generate the vector
    for (std::size_t i = 0; i < (N - 2); ++i)
    {
        const std::size_t val = distrib(gen);

        // Push the random number into the queues
        bq.push(val);
        pq.push(val);
    }

    // Push the min value and the max value
    pq.push(min_size_t);
    pq.push(max_size_t);
    bq.push(min_size_t);
    bq.push(max_size_t);

    SECTION("Push", "[some_details]")
    {
        REQUIRE(bq.size() == pq.size());
    }

    SECTION("Top", "[some_details]")
    {
        REQUIRE(bq.top() == pq.top());
    }

    SECTION("Pop", "[some_details]")
    {
        for (std::size_t i = 0; i < N; ++i)
        {
            REQUIRE(bq.top() == pq.top());
            bq.pop();
            pq.pop();
        }

        REQUIRE(bq.empty());
    }
}

TEST_CASE( "Basic Operations for Min Heap Node", "[main]" )
{
    auto bq = BucketQueue<Node, unsigned int, std::greater<Node>> {};
    constexpr std::size_t N = 3;

    Node startNode({8, 4, 2, 1, constants::EMPTY, 5, 6, 7, 3});
    Node halfwayNode({4, 1, 2, 7, 5, 3, 8, 6, constants::EMPTY});
    Node finishedNode({1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY});

    bq.push(startNode);
    bq.push(halfwayNode);
    bq.push(finishedNode);

    SECTION("Size", "[some_details]")
    {
        REQUIRE(bq.size() == N);
    }

    SECTION("Top", "[some_details]")
    {
        REQUIRE(bq.top() == finishedNode);
    }

    SECTION("Pop", "[some_details]")
    {
        bq.pop();
        REQUIRE(bq.top() == halfwayNode);
        REQUIRE(bq.size() == N - 1);

        bq.pop();
        REQUIRE(bq.top() == startNode);
        REQUIRE(bq.size() == N - 2);

        bq.pop();
        REQUIRE(bq.size() == 0);
        REQUIRE(bq.empty());
    }
}
