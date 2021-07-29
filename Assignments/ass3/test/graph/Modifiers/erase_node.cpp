// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)

#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

// Simplest test case, makes sure that when calling the default constructor we get a euclidean
// vector like [0]

TEST_CASE("remove_node_default") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    g.insert_edge(1, 2, 9);
    REQUIRE(g.erase_node(1));
    REQUIRE(g.nodes() == std::vector<int>{2, 3, 4});
    REQUIRE(g.connections(2) == std::vector<int>{});
    REQUIRE(g.connections(3) == std::vector<int>{});
    REQUIRE(g.connections(4) == std::vector<int>{});
}

TEST_CASE("remove_node_errors") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    g.insert_edge(1, 2, 9);
    REQUIRE(!g.erase_node(69));
    REQUIRE(g.nodes() == std::vector<int>{1, 2, 3, 4});
    REQUIRE(g.connections(1) == std::vector<int>{2});
    REQUIRE(g.weights(1, 2) == std::vector<int>{9});
    REQUIRE(g.connections(2) == std::vector<int>{});
    REQUIRE(g.connections(3) == std::vector<int>{});
    REQUIRE(g.connections(4) == std::vector<int>{});
}