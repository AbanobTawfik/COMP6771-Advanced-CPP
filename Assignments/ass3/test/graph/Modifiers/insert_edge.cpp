// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

// Simplest test case, makes sure that when calling the default constructor we get a euclidean
// vector like [0]

TEST_CASE("insert_edge_default") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    auto inserted = g.insert_edge(1, 2, 900);
    REQUIRE(inserted);
    inserted = g.insert_edge(1, 2, 4);
    REQUIRE(inserted);
    inserted = g.insert_edge(1, 2, 4);
    REQUIRE(!inserted);
    inserted = g.insert_edge(1, 3, 5);
    REQUIRE(inserted);
    REQUIRE(g.connections(1) == std::vector<int>{2, 3});
    // checks weights sorted
    REQUIRE(g.weights(1, 2) == std::vector<int>{4, 900});
}

TEST_CASE("insert_edge_missing_node") {
    using graph = gdwg::graph<int, int>;
    auto default_graph = graph();
    auto g = graph{1, 2, 3, 4};
    REQUIRE_THROWS_WITH(g.insert_edge(1, 69, 900), "Cannot call gdwg::graph<N, E>::insert_edge when either from or to node does not exist");
    REQUIRE_THROWS_WITH(g.insert_edge(69, 1, 900), "Cannot call gdwg::graph<N, E>::insert_edge when either from or to node does not exist");
    REQUIRE_THROWS_WITH(g.insert_edge(69, 69, 900), "Cannot call gdwg::graph<N, E>::insert_edge when either from or to node does not exist");
}