// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("insert_edge_default") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    auto inserted = g.insert_edge(1, 2, 900);
    CHECK(inserted);
    inserted = g.insert_edge(1, 2, 4);
    CHECK(inserted);
    inserted = g.insert_edge(1, 2, 4);
    CHECK(!inserted);
    inserted = g.insert_edge(1, 3, 5);
    CHECK(inserted);
    CHECK(g.connections(1) == std::vector<int>{2, 3});
    // checks weights sorted
    CHECK(g.weights(1, 2) == std::vector<int>{4, 900});
}

TEST_CASE("insert_edge_missing_node") {
    using graph = gdwg::graph<int, int>;
    auto default_graph = graph();
    auto g = graph{1, 2, 3, 4};
    CHECK_THROWS_WITH(g.insert_edge(1, 69, 900),
                      "Cannot call gdwg::graph<N, E>::insert_edge when either from or to node does not exist");
    CHECK_THROWS_WITH(g.insert_edge(69, 1, 900),
                      "Cannot call gdwg::graph<N, E>::insert_edge when either from or to node does not exist");
    CHECK_THROWS_WITH(g.insert_edge(69, 69, 900),
                      "Cannot call gdwg::graph<N, E>::insert_edge when either from or to node does not exist");
}