#define CATCH_CONFIG_MAIN

#include <string_view>    // std::string_view
#include <vector>    // std::vector
#include <functional>    // std::greater
#include <algorithm>   // std::sort
#include <catch2/catch_test_macros.hpp> // TEST_CASE, SECTION, REQUIRE

#include "container/bucketqueuelib.hpp" // BucketQueue
#include "constants/constantslib.hpp"
#include "node/nodelib.hpp"

TEST_CASE( "Basic Operations for Max Heap", "[main]" )
{
    auto b = BucketQueue<std::string, unsigned short>();

    std::vector<std::string> elements {"low", "medium low",
        "medium", "high", "highest"};

    const std::size_t N = elements.size();

    auto itr = elements.crbegin();

    unsigned short priority = 1;
    for (auto e : elements)
    {
        b.push(e, priority);

        priority += 2;
    }

    SECTION("Push", "[some_details]")
    {
        REQUIRE(b.size() == N);
    }

    SECTION("Top", "[some_details]")
    {
        REQUIRE(b.top() == *itr);
    }

    SECTION("Pop", "[some_details]")
    {
        std::size_t sz = N;
        b.pop();
        ++itr;
        --sz;
        REQUIRE(b.top() == *itr);
        REQUIRE(b.size() == sz);
        
        b.pop();
        ++itr;
        --sz;
        REQUIRE(b.top() == *itr);
        REQUIRE(b.size() == sz);
        
        b.pop();
        ++itr;
        --sz;
        REQUIRE(b.top() == *itr);
        REQUIRE(b.size() == sz);
        
        b.pop();
        ++itr;
        --sz;
        REQUIRE(b.top() == *itr);
        REQUIRE(b.size() == sz);

        b.pop();
        --sz;
        REQUIRE(b.size() == sz);
    }
}

TEST_CASE( "Basic Operations for Min Heap", "[main]" )
{
    auto b = BucketQueue<std::string, unsigned short, std::greater<unsigned short>()>();

    std::vector<std::string> elements {"highest", "high",
        "medium", "medium low", "low"};

    const std::size_t N = elements.size();

    auto itr = elements.cbegin();

    unsigned short priority = 1;
    for (auto e : elements)
    {
        b.push(e, priority);

        priority += 2;
    }

    SECTION("Push", "[some_details]")
    {
        REQUIRE(b.size() == N);
    }

    SECTION("Top", "[some_details]")
    {
        REQUIRE(b.top() == *itr);
    }

    SECTION("Pop", "[some_details]")
    {
        std::size_t sz = N;
        b.pop();
        ++itr;
        --sz;
        REQUIRE(b.top() == *itr);
        REQUIRE(b.size() == sz);
        
        b.pop();
        ++itr;
        --sz;
        REQUIRE(b.top() == *itr);
        REQUIRE(b.size() == sz);
        
        b.pop();
        ++itr;
        --sz;
        REQUIRE(b.top() == *itr);
        REQUIRE(b.size() == sz);
        
        b.pop();
        ++itr;
        --sz;
        REQUIRE(b.top() == *itr);
        REQUIRE(b.size() == sz);

        b.pop();
        --sz;
        REQUIRE(b.size() == sz);
    }
}

TEST_CASE( "Same Priority", "[main]" )
{
    auto b = BucketQueue<std::string, unsigned short, std::greater<unsigned short>()>();

    std::vector<std::string> samePriorityElements {"medium1", "medium2"};

    b.push(samePriorityElements.front(), 5);
    b.push(samePriorityElements.back(), 5);

    SECTION("Top", "[some_details]")
    {
        REQUIRE(b.size() == samePriorityElements.size());
        REQUIRE(b.top() == samePriorityElements.back());
    }

    SECTION("Second Top", "[some_details]")
    {
        b.pop();
        samePriorityElements.pop_back();
        REQUIRE(b.size() == samePriorityElements.size());
        REQUIRE(b.top() == samePriorityElements.back());
    }
}

TEST_CASE( "Basic Operations for Min Heap Node", "[main]" )
{

    auto b = BucketQueue<Node, unsigned unsigned short, std::greater<Node>()>();
    constexpr std::size_t N = 3;

    Node startNode({8, 4, 2, 1, constants::EMPTY, 5, 6, 7, 3});
    Node halfwayNode({4, 1, 2, 7, 5, 3, 8, 6, constants::EMPTY});
    Node finishedNode({1, 2, 3, 4, 5, 6, 7, 8, constants::EMPTY});

    b.push(startNode, startNode.GetTotalCost());
    b.push(halfwayNode, halfwayNode.GetTotalCost());
    b.push(finishedNode, finishedNode.GetTotalCost());

    SECTION("Size", "[some_details]")
    {
        REQUIRE(b.size() == N);
    }

    SECTION("Top", "[some_details]")
    {
        REQUIRE(b.top() == finishedNode);
    }

    SECTION("Pop", "[some_details]")
    {
        b.pop();
        REQUIRE(b.top() == halfwayNode);
        REQUIRE(b.size() == N - 1);
        
        b.pop();
        REQUIRE(b.top() == startNode);
        REQUIRE(b.size() == N - 2);

        b.pop();
        REQUIRE(b.size() == 0);
    }
}