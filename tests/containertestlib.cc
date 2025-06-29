#define CATCH_CONFIG_MAIN

#include <string_view>    // std::string_view
#include <vector>    // std::vector
#include <functional>    // std::greater
#include <catch2/catch.hpp> // TEST_CASE, SECTION, REQUIRE

#include "container/bucketqueuelib.hpp" // BucketQueue

TEST_CASE( "Basic Operations for Max Heap", "[main]" )
{

    auto b = BucketQueue<std::string, int>(10);

    std::vector<std::string> elements {"low", "medium low",
        "medium", "high", "highest"};

    const std::size_t N = elements.size();

    auto itr = elements.crbegin();

    int priority = 1;
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

    auto b = BucketQueue<std::string, int, std::greater<int>()>(10);

    std::vector<std::string> elements {"highest", "high",
        "medium", "medium low", "low"};

    const std::size_t N = elements.size();

    auto itr = elements.cbegin();

    int priority = 1;
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
