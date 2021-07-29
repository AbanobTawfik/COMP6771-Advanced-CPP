// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

// Simplest test case, makes sure that when calling the default constructor we get a euclidean
// vector like [0]

TEST_CASE("default_delete_iterator") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    REQUIRE(g.insert_edge(1,2,3));
    REQUIRE(g.weights(1, 2) == std::vector<int>{3});
    auto iterator_begin = g.begin();
    REQUIRE(*iterator_begin == gdwg::graph<int, int>::value_type{1,2,3});
    auto next_iterator = g.erase_edge(iterator_begin);
    REQUIRE(next_iterator == g.end());
    REQUIRE(g.weights(1, 2) == std::vector<int>{});
}