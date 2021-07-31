// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("remove_node_default") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    g.insert_edge(1, 2, 9);
    CHECK(g.erase_node(1));
    CHECK(g.nodes() == std::vector<int>{2, 3, 4});
    CHECK(g.connections(2) == std::vector<int>{});
    CHECK(g.connections(3) == std::vector<int>{});
    CHECK(g.connections(4) == std::vector<int>{});
}

TEST_CASE("remove_node_false_cases") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    g.insert_edge(1, 2, 9);
    CHECK(!g.erase_node(69));
    CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4});
    CHECK(g.connections(1) == std::vector<int>{2});
    CHECK(g.weights(1, 2) == std::vector<int>{9});
    CHECK(g.connections(2) == std::vector<int>{});
    CHECK(g.connections(3) == std::vector<int>{});
    CHECK(g.connections(4) == std::vector<int>{});
}