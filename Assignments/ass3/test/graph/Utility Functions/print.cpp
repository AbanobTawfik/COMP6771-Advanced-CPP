// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)

#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

// Simplest test case, makes sure that when calling the default constructor we get a euclidean
// vector like [0]

TEST_CASE("default_constructor_ints") {
    using graph = gdwg::graph<int, int>;
    auto const v = std::vector<graph::value_type>{
            {4, 1, -4},
            {3, 2, 2},
            {2, 4, 2},
            {2, 1, 1},
            {6, 2, 5},
            {6, 3, 10},
            {1, 5, -1},
            {3, 6, -8},
            {4, 5, 3},
            {5, 2, 7},
    };

    auto g = graph{};
    for (const auto &x : v) {
        g.insert_node(x.from);
        g.insert_node(x.to);
        g.insert_edge(x.from, x.to, x.weight);
    };

    g.insert_node(64);
    auto out = std::ostringstream{};
    out << g;
    auto const expected_output = std::string_view(R"(1 (
  5 | -1
)
2 (
  1 | 1
  4 | 2
)
3 (
  2 | 2
  6 | -8
)
4 (
  1 | -4
  5 | 3
)
5 (
  2 | 7
)
6 (
  2 | 5
  3 | 10
)
64 (
)
)");
    CHECK(out.str() == expected_output);

}