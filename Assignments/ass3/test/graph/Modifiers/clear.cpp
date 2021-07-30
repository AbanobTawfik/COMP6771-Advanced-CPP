// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

// Simplest test case, makes sure that when calling the default constructor we get a euclidean
// vector like [0]

TEST_CASE("clear_graphs") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1,2,3,4,5,6,7,8,0, 9};
    REQUIRE(g.nodes() == std::vector<int>{0,1,2,3,4,5,6,7,8,9});
    g.clear();
    REQUIRE(g.empty());
}