// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("input_iterator_constructor") {
    using graph = gdwg::graph<std::string, int>;
    const auto vector_il = std::vector<std::string>{"Hey", "hello", "why", "??", "lol", "Kappa123", "PauseChamp"};
    const auto g = graph(vector_il.begin(), vector_il.end());
    const auto all_nodes = g.nodes();
    auto sorted_nodes = vector_il;
    std::sort(sorted_nodes.begin(), sorted_nodes.end());
    CHECK(!g.empty());
    CHECK(std::is_sorted(all_nodes.begin(), all_nodes.end()));
    CHECK(std::equal(all_nodes.begin(), all_nodes.end(), sorted_nodes.begin()));
}