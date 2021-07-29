// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

TEST_CASE("initialiser_list_constructor") {
    using graph = gdwg::graph<std::string, int>;
    const auto vector_il = std::vector<std::string>{"Hey", "hello", "why", "??", "lol", "Kappa123", "PauseChamp"};
    const auto g = graph{"Hey", "hello", "why", "??", "lol", "Kappa123", "PauseChamp"};
    const auto all_nodes = g.nodes();
    auto sorted_nodes = vector_il;
    std::sort(sorted_nodes.begin(), sorted_nodes.end());
    REQUIRE(!g.empty());
    REQUIRE(std::is_sorted(all_nodes.begin(), all_nodes.end()));
    REQUIRE(std::equal(all_nodes.begin(), all_nodes.end(), sorted_nodes.begin()));
}