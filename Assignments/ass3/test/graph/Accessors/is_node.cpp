// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("is_node_tests") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1,2,3,4,5,6,7,8,9};
    g.insert_edge(1,2,3);
    g.insert_edge(1,2,4);
    g.insert_edge(1,2,5);
    g.insert_edge(2,2,1);
    SECTION("Checking positive and negative cases before deletion") {
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
    }
    SECTION("Removing Node and seeing if it still works") {
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
}