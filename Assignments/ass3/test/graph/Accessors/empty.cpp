// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("empty_tests") {
    using graph = gdwg::graph<int, int>;
    const auto g = graph();
    auto g2 = graph{1,2,3,4,5};
    CHECK(g.empty());
    CHECK(!g2.empty());
    g2.erase_node(1);
    g2.erase_node(2);
    g2.erase_node(3);
    g2.erase_node(4);
    g2.erase_node(5);
    CHECK(g2.empty());
}