// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)

#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("nodes_test") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 3, 2, 4, 6, 5, 7, 8};
    g.insert_edge(1, 2, 3);
    g.insert_edge(1, 2, 4);
    g.insert_edge(1, 2, 5);
    g.insert_edge(2, 2, 1);
    CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
    g.erase_node(1);
    CHECK(g.nodes() == std::vector<int>{2, 3, 4, 5, 6, 7, 8});
}

TEST_CASE("nodes_empty") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4, 5, 6, 7, 8, 8};
    CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
    g.insert_edge(1, 2, 3);
    g.insert_edge(1, 2, 4);
    g.insert_edge(1, 2, 5);
    g.insert_edge(2, 2, 1);
    g.erase_node(1);
    CHECK(g.nodes() == std::vector<int>{2, 3, 4, 5, 6, 7, 8});
}