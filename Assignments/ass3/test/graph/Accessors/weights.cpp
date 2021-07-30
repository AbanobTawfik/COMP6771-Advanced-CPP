// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("weights_normal_case") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2};
    CHECK(g.nodes() == std::vector<int>{1, 2});
    g.insert_edge(1, 2, 4);
    g.insert_edge(1, 2, 9);
    g.insert_edge(1, 2, 9);
    g.insert_edge(1, 2, 3);
    g.insert_edge(2, 2, 1);
    CHECK(g.weights(1,2) == std::vector<int>{3,4,9});
    CHECK(g.weights(2,2) == std::vector<int>{1});
    SECTION("Checking weights are correct after a merge replace") {
        g.merge_replace_node(1, 2);
        CHECK(g.nodes() == std::vector<int>{2});
        CHECK(g.connections(2) == std::vector<int>{2});
        CHECK(g.weights(2, 2) == std::vector<int>{1, 3, 4, 9});
    }
}

TEST_CASE("weights_error_case") {
    using graph = gdwg::graph<int, int>;
    auto g = graph();
    CHECK(g.empty());
    CHECK_THROWS_WITH(g.weights(1,3), "Cannot call gdwg::graph<N, E>::weights if src or dst node don't exist in the graph");
}
