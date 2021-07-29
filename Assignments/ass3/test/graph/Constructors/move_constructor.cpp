// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

TEST_CASE("move_constructor") {
    using graph = gdwg::graph<std::string, int>;
    auto g1 = graph{"Hey", "hello", "why", "??", "lol", "Kappa123", "PauseChamp"};
    const auto all_nodes1 = g1.nodes();
    REQUIRE(!g1.empty());
    const auto g2 = graph(std::move(g1));
    const auto all_nodes2 = g2.nodes();
    REQUIRE(g1.empty());
    REQUIRE(std::equal(all_nodes1.begin(), all_nodes1.end(), all_nodes2.begin(), all_nodes2.end()));
}