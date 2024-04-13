#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>

#include "constants/constantslib.hpp"
#include "node/nodelib.hpp"

TEST_CASE( "Node Initialization", "[main]" )
{
    Node n({1, 2, constants::EMPTY, 4, 5, 3, 7, 8, 6});

    struct Tester : Node
    {
        std::vector<int> GetLayout() const { return this-> layout; }

        int GetPosX() const { return this->posX; }
    };

    REQUIRE (static_cast<const Tester&>(n).GetPosX() == 2);
}
