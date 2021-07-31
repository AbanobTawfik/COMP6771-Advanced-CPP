// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("empty_graph_with_nodes") {
    using graph = gdwg::graph<int, int>;
    const auto g1 = graph();
    CHECK(g1.begin() == g1.end());
    const auto g2 = graph{1,2,3,4,5};
    CHECK(g2.nodes() == std::vector<int>{1,2,3,4,5});
    CHECK(g2.begin() == g2.end());

}

TEST_CASE("graph_with_edges") {
    using graph = gdwg::graph<int, int>;
    using value_type = gdwg::graph<int, int>::value_type;
    auto g = graph{1,2,3,4,5};
    CHECK(g.nodes() == std::vector<int>{1,2,3,4,5});
    CHECK(g.begin() == g.end());
    g.insert_edge(1,2,3);
    CHECK(*g.begin() == value_type{1,2,3});
}