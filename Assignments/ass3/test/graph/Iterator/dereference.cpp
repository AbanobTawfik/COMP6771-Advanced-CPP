// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("dereference_value") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4, 5};
    g.insert_edge(1, 2, 3);
    CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4, 5});
    CHECK(*g.begin() == gdwg::graph<int, int>::value_type{1, 2, 3});
}