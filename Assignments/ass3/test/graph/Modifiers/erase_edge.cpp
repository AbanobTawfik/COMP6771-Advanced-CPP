// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

// Simplest test case, makes sure that when calling the default constructor we get a euclidean
// vector like [0]

TEST_CASE("remove_edges_default") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    g.insert_edge(1, 2, 9);
    REQUIRE(g.nodes() == std::vector<int>{1, 2, 3, 4});
    REQUIRE(g.connections(1) == std::vector<int>{2});
    REQUIRE(g.weights(1, 2) == std::vector<int>{9});
    REQUIRE(g.connections(2) == std::vector<int>{});
    REQUIRE(g.connections(3) == std::vector<int>{});
    REQUIRE(g.connections(4) == std::vector<int>{});
    REQUIRE(g.erase_edge(1, 2, 9));
    REQUIRE(g.nodes() == std::vector<int>{1, 2, 3, 4});
    REQUIRE(g.connections(1) == std::vector<int>{});
    REQUIRE(g.weights(1, 2) == std::vector<int>{});
    REQUIRE(g.connections(2) == std::vector<int>{});
    REQUIRE(g.connections(3) == std::vector<int>{});
    REQUIRE(g.connections(4) == std::vector<int>{});
}

TEST_CASE("remove_edges_errors") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    g.insert_edge(1, 2, 9);
    REQUIRE(g.nodes() == std::vector<int>{1, 2, 3, 4});
    REQUIRE(g.connections(1) == std::vector<int>{2});
    REQUIRE(g.weights(1, 2) == std::vector<int>{9});
    REQUIRE(g.connections(2) == std::vector<int>{});
    REQUIRE(g.connections(3) == std::vector<int>{});
    REQUIRE(g.connections(4) == std::vector<int>{});
    REQUIRE(!g.erase_edge(1, 2, 99));
    REQUIRE(!g.erase_edge(1, 3, 99));
    REQUIRE(!g.erase_edge(2, 2, 99));
    REQUIRE(!g.erase_edge(2, 2, 9));
    REQUIRE_THROWS_WITH(g.erase_edge(2, 29, 9), "Cannot call gdwg::graph<N, E>::erase_edge on src or dst if they don't exist in the graph");
    REQUIRE_THROWS_WITH(g.erase_edge(29, 2, 9), "Cannot call gdwg::graph<N, E>::erase_edge on src or dst if they don't exist in the graph");
    REQUIRE_THROWS_WITH(g.erase_edge(82, 29, 9), "Cannot call gdwg::graph<N, E>::erase_edge on src or dst if they don't exist in the graph");
    REQUIRE(g.nodes() == std::vector<int>{1, 2, 3, 4});
    REQUIRE(g.connections(1) == std::vector<int>{2});
    REQUIRE(g.weights(1, 2) == std::vector<int>{9});
    REQUIRE(g.connections(2) == std::vector<int>{});
    REQUIRE(g.connections(3) == std::vector<int>{});
    REQUIRE(g.connections(4) == std::vector<int>{});
}