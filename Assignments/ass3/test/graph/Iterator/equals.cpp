// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("Equal_iterators") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4, 5};
    g.insert_edge(1, 2, 3);
    CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4, 5});
    auto first_it = g.begin();
    ++first_it;
    auto second_it = g.begin();
    ++second_it;
    CHECK(first_it == second_it);
    --second_it;
    CHECK(!(second_it == first_it));
    CHECK(second_it == g.begin());
}