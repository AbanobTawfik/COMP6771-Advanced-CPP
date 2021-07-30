// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("normal_case_is_connected") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1,2,3,4,5};
    g.insert_edge(1,2,3);
    g.insert_edge(1,3,3);
    g.insert_edge(1,4,4);
    g.insert_edge(1,1,5);
    CHECK(g.is_connected(1,1));
    CHECK(g.is_connected(1,2));
    CHECK(g.is_connected(1,3));
    CHECK(g.is_connected(1,4));
}

TEST_CASE("error_case") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1,2,3,4,5};
    g.insert_edge(1,2,3);
    g.insert_edge(1,3,3);
    g.insert_edge(1,4,4);
    g.insert_edge(1,1,5);
    CHECK_THROWS_WITH(g.is_connected(1,59), "Cannot call gdwg::graph<N, E>::is_connected if src or dst node don't exist in the graph");
    CHECK_THROWS_WITH(g.is_connected(59,1), "Cannot call gdwg::graph<N, E>::is_connected if src or dst node don't exist in the graph");
    CHECK_THROWS_WITH(g.is_connected(6,59), "Cannot call gdwg::graph<N, E>::is_connected if src or dst node don't exist in the graph");
}