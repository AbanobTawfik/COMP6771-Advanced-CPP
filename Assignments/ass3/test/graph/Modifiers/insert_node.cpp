// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

TEST_CASE("insert_node_no_duplicate") {
    using graph = gdwg::graph<int, int>;
    auto g = graph();
    REQUIRE(g.empty());
    auto inserted = g.insert_node(1);
    REQUIRE(g.nodes().size() == 1);
    REQUIRE(g.nodes().at(0) == 1);
    REQUIRE(inserted);
}

TEST_CASE("insert_node_with_duplicate") {
    using graph = gdwg::graph<int, int>;
    auto g = graph();
    REQUIRE(g.empty());
    auto inserted = g.insert_node(1);
    REQUIRE(g.nodes().size() == 1);
    REQUIRE(g.nodes().at(0) == 1);
    REQUIRE(inserted);
    inserted = g.insert_node(1);
    REQUIRE(g.nodes().size() == 1);
    REQUIRE(g.nodes().at(0) == 1);
    REQUIRE(!inserted);
}