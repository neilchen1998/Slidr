#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <vector>   // std::vector
#include <string>   // std::string

#include "pattern/serializationlib.hpp"
#include "pattern/deserializationlib.hpp"
#include "math/mathlib.hpp"
#include "constants/constantslib.hpp"   // constants::EMPTY

TEST_CASE( "Hash Range Function <8>", "[main]" )
{
    std::vector<int> trueV1 {constants::EMPTY, 1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> trueV2 {3, 1, constants::EMPTY, 2, 8, 7, 6, 5, 4};

    std::string data1 = pattern::serialize(trueV1);
    std::string data2 = pattern::serialize(trueV2);

    std::vector<int> v1 = pattern::deserialize(data1);
    std::vector<int> v2 = pattern::deserialize(data2);

    SECTION ( "Serialization", "[main]")
    {
        REQUIRE (data1 == "ff0102030405060708");
        REQUIRE (data2 == "0301ff020807060504");
    }

    SECTION ( "Deserialization", "[main]")
    {
        REQUIRE (trueV1 == v1);
        REQUIRE (trueV2 == v2);
    }
}

TEST_CASE( "Hash Range Function <16>", "[main]" )
{
    std::vector<int> trueV1 {3, 1, 11, 10, 13, 9, 5, 4, 15, 8, constants::EMPTY, 7, 6, 2, 14, 12};
    std::vector<int> trueV2 {3, 1, 11, 10, 13, 9, 5, 4, 15, constants::EMPTY, 8, 7, 6, 2, 14, 12};
    std::vector<int> trueV3 {3, 1, 11, 10, 13, constants::EMPTY, 5, 4, 15, 9, 8, 7, 6, 2, 14, 12};

    std::string data1 = pattern::serialize(trueV1);
    std::string data2 = pattern::serialize(trueV2);
    std::string data3 = pattern::serialize(trueV3);

    std::vector<int> v1 = pattern::deserialize(data1);
    std::vector<int> v2 = pattern::deserialize(data2);
    std::vector<int> v3 = pattern::deserialize(data3);

    SECTION ( "Serialization", "[main]")
    {
        REQUIRE (data1 == "03010b0a0d0905040f08ff0706020e0c");
        REQUIRE (data2 == "03010b0a0d0905040fff080706020e0c");
        REQUIRE (data3 == "03010b0a0dff05040f09080706020e0c");
    }

    SECTION ( "Deserialization", "[main]")
    {
        REQUIRE (trueV1 == v1);
        REQUIRE (trueV2 == v2);
        REQUIRE (trueV3 == v3);
    }
}
