// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("equals_test") {
    using graph = gdwg::graph<int, int>;
    const auto g1 = graph();
    const auto g2 = graph();
    auto g3 = graph{3,2};
    g3.insert_edge(3,2,4);
    const auto g4 = graph(g3);
    CHECK(g1 == g2);
    CHECK(!(g1 == g3));
    CHECK(g3 == g4);
    CHECK(g3.weights(3,2) == g4.weights(3,2));
}