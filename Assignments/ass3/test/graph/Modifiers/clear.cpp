// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("clear_graphs") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1,2,3,4,5,6,7,8,0, 9};
    CHECK(g.nodes() == std::vector<int>{0,1,2,3,4,5,6,7,8,9});
    g.clear();
    CHECK(g.empty());
}