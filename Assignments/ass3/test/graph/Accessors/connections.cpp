// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

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
    CHECK(g.erase_edge(1,5,3));
    CHECK(g.connections(1) == std::vector<int>{1, 2, 3, 4, 6});
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