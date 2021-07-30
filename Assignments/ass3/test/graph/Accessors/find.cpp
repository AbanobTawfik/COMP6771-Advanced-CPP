// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("default_constructor_ints") {
    using graph = gdwg::graph<int, int>;
    using value_type = gdwg::graph<int, int>::value_type;
    auto g = graph{1,2,3,4,5};
    g.insert_edge(1,2,3);
    g.insert_edge(1,2,3);
    g.insert_edge(1,2,4);
    g.insert_edge(1,2,5);
    CHECK(*g.find(1,2,3) == value_type{1,2,3});
    CHECK(*g.find(1,2,4) == value_type{1,2,4});
    CHECK(*g.find(1,2,5) == value_type{1,2,5});
    CHECK(g.find(68,2,3) == g.end());
}