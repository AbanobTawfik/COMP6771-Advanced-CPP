// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

// Simplest test case, makes sure that when calling the default constructor we get a euclidean
// vector like [0]


TEST_CASE("weights_normal_case") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4, 5, 6, 7, 8, 8};
    CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
    g.insert_edge(1, 2, 4);
    g.insert_edge(1, 2, 9);
    g.insert_edge(1, 2, 9);
    g.insert_edge(1, 2, 3);
    g.insert_edge(2, 2, 1);
    g.erase_node(1);
    CHECK(g.weights(1,2) == std::vector<int>{3,4,9});
    CHECK(g.weights(2,2) == std::vector<int>{1});
    g.merge_replace_node(1,2);
    CHECK(g.nodes() == std::vector<int>{2});
    CHECK(g.connections(2) == std::vector<int>{2});
    CHECK(g.weights(2, 2) == std::vector<int>{1,3,4,9});
}

TEST_CASE("weights_error_case") {
    using graph = gdwg::graph<int, int>;
    auto g = graph();
    CHECK(g.empty());
    CHECK_THROWS_WITH(g.weights(1,3), "Cannot call gdwg::graph<N, E>::weights if src or dst node don't exist in the graph");
}
