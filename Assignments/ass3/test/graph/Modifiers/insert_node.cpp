// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("insert_node_no_duplicate") {
    using graph = gdwg::graph<int, int>;
    auto g = graph();
    CHECK(g.empty());
    auto inserted = g.insert_node(1);
    CHECK(g.nodes().size() == 1);
    CHECK(g.nodes().at(0) == 1);
    CHECK(inserted);
}

TEST_CASE("insert_node_with_duplicate") {
    using graph = gdwg::graph<int, int>;
    auto g = graph();
    CHECK(g.empty());
    auto inserted = g.insert_node(1);
    SECTION("check initial insert is okay") {
        CHECK(g.nodes().size() == 1);
        CHECK(g.nodes().at(0) == 1);
        CHECK(inserted);
    }
    SECTION("Check duplicate insert has no effect") {
        inserted = g.insert_node(1);
        CHECK(g.nodes().size() == 1);
        CHECK(g.nodes().at(0) == 1);
        CHECK(!inserted);
    }
}