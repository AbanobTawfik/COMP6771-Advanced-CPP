// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)

#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

TEST_CASE("default_delete_iterator") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    CHECK(g.insert_edge(1, 2, 3));
    CHECK(g.weights(1, 2) == std::vector<int>{3});
    auto iterator_begin = g.begin();
    CHECK(*iterator_begin == gdwg::graph<int, int>::value_type{1, 2, 3});
    auto next_iterator = g.erase_edge(iterator_begin);
    CHECK(next_iterator == g.end());
    CHECK(g.weights(1, 2) == std::vector<int>{});
}

TEST_CASE("multiple_iterator_erase_few") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    CHECK(g.insert_edge(1, 2, 3));
    CHECK(g.insert_edge(1, 3, 3));
    CHECK(g.insert_edge(1, 4, 3));
    CHECK(g.weights(1, 2) == std::vector<int>{3});
    auto iterator_begin = g.begin();
    auto iterator_end = iterator_begin++;
    auto next_iterator = g.erase_edge(iterator_begin, iterator_end);
    CHECK(*next_iterator == gdwg::graph<int, int>::value_type{1, 3, 3});
    // check graph is reset
    CHECK(*g.begin() == gdwg::graph<int, int>::value_type{1, 3, 3});
}

TEST_CASE("multiple_iterator_erase_all") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    CHECK(g.insert_edge(1, 2, 3));
    CHECK(g.insert_edge(1, 3, 3));
    CHECK(g.insert_edge(1, 4, 3));
    CHECK(g.weights(1, 2) == std::vector<int>{3});
    auto iterator_begin = g.begin();
    auto iterator_end = g.end();
    auto next_iterator = g.erase_edge(iterator_begin, iterator_end);
    CHECK(next_iterator == g.end());
    // check graph is reset
    CHECK(g.begin() == g.end());
    CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4});
}