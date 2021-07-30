// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

// Simplest test case, makes sure that when calling the default constructor we get a euclidean
// vector like [0]

TEST_CASE("decrement_pre") {
    using graph = gdwg::graph<int, int>;
    using value_type = gdwg::graph<int,int>::value_type;
    auto g = graph{1,2,3,4,5};
    g.insert_edge(1,2,3);
    g.insert_edge(1,2,7);
    g.insert_edge(1,2,4);
    g.insert_edge(1,2,6);
    auto it_original = g.begin();
    auto it = g.begin();
    CHECK(*it == value_type{1,2,3});
    it = it++;
    CHECK(*it == value_type{1,2,4});
    it = it--;
    CHECK(*it == value_type{1,2,3});
    CHECK(it == it_original);
    CHECK(it_original == g.begin());
}

TEST_CASE("decrement_post") {
    using graph = gdwg::graph<int, int>;
    using value_type = gdwg::graph<int,int>::value_type;
    auto g = graph{1,2,3,4,5};
    g.insert_edge(1,2,3);
    g.insert_edge(1,2,7);
    g.insert_edge(1,2,4);
    g.insert_edge(1,2,6);
    auto it_original = g.begin();
    auto it = g.begin();
    CHECK(*it == value_type{1,2,3});
    it = it++;
    CHECK(*it == value_type{1,2,4});
    --it;
    CHECK(*it == value_type{1,2,3});
    CHECK(it == it_original);
    CHECK(it_original == g.begin());
}