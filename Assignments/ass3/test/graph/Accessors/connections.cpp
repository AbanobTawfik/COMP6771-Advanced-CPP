// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)

#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

// Simplest test case, makes sure that when calling the default constructor we get a euclidean
// vector like [0]

TEST_CASE("connections_basic_case") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4, 5, 6};
    g.insert_edge(1, 2, 5);
    g.insert_edge(1, 1, 5);
    g.insert_edge(1, 2, 4);
    g.insert_edge(1, 3, 3);
    g.insert_edge(1, 4, 3);
    g.insert_edge(1, 5, 3);
    g.insert_edge(1, 6, 3);
    CHECK(g.connections(1) == std::vector<int>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("connections_error_case") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4, 5, 6};
    g.insert_edge(1, 2, 5);
    g.insert_edge(1, 1, 5);
    g.insert_edge(1, 2, 4);
    g.insert_edge(1, 3, 3);
    g.insert_edge(1, 4, 3);
    g.insert_edge(1, 5, 3);
    g.insert_edge(1, 6, 3);
    CHECK_THROWS_WITH(g.connections(34),
                      "Cannot call gdwg::graph<N, E>::connections if src doesn't exist in the graph");
}