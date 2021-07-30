// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

// Simplest test case, makes sure that when calling the default constructor we get a euclidean
// vector like [0]

TEST_CASE("equals_test") {
    using graph = gdwg::graph<int, int>;
    const auto g1 = graph();
    const auto g2 = graph();
    const auto g3 = graph{3};
    const auto g4 = graph(g3);
    CHECK(g1 == g2);
    CHECK(g1 != g3);
    CHECK(g3 == g4);
}