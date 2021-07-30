// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("default_constructor_ints") {
    using graph = gdwg::graph<int, int>;
    const auto g = graph();
    CHECK(g.empty());
}