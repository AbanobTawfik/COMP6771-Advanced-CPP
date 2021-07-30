// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

// Simplest test case, makes sure that when calling the default constructor we get a euclidean
// vector like [0]

TEST_CASE("is_node_tests") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1,2,3,4,5,6,7,8,9};
    g.insert_edge(1,2,3);
    g.insert_edge(1,2,4);
    g.insert_edge(1,2,5);
    g.insert_edge(2,2,1);
    CHECK(g.is_node(1));
    CHECK(g.is_node(2));
    CHECK(g.is_node(3));
    CHECK(g.is_node(4));
    CHECK(g.is_node(5));
    CHECK(g.is_node(6));
    CHECK(g.is_node(7));
    CHECK(g.is_node(8));
    CHECK(g.is_node(9));
    CHECK(!g.is_node(6659));
    g.erase_node(1);
    CHECK(!g.is_node(1));
    CHECK(g.is_node(2));
    CHECK(g.is_node(3));
    CHECK(g.is_node(4));
    CHECK(g.is_node(5));
    CHECK(g.is_node(6));
    CHECK(g.is_node(7));
    CHECK(g.is_node(8));
    CHECK(g.is_node(9));
}