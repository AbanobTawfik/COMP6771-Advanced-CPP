// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("copy_equals") {
    using graph = gdwg::graph<std::string, int>;
    const auto g1 = graph{"Hey", "hello", "why", "??", "lol", "Kappa123", "PauseChamp"};
    CHECK(!g1.empty());
    const auto g2 = g1;
    CHECK(g1 == g2);
}