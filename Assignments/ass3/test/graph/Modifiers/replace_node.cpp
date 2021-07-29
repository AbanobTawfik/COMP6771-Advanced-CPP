// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

// Simplest test case, makes sure that when calling the default constructor we get a euclidean
// vector like [0]

TEST_CASE("replace_node_success") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"hello", "replace me"};
    g.insert_edge("hello", "replace me", 5);
    auto replaced = g.replace_node("hello", "replaced_hello");
    REQUIRE(replaced);
    auto is_connected = g.is_connected("replaced_hello", "replace me");
    REQUIRE(is_connected);
    replaced = g.replace_node("replace me", "replaced");
    REQUIRE(replaced);
    is_connected = g.is_connected("replaced_hello", "replaced");
    REQUIRE(is_connected);
    REQUIRE(g.nodes() == std::vector<std::string>{"replaced", "replaced_hello"});
    REQUIRE(g.connections("replaced_hello") == std::vector<std::string>{"replaced"});
    REQUIRE(g.weights("replaced_hello", "replaced") == std::vector<int>{5});
}

TEST_CASE("replace_node_errors") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"hello", "replace me"};
    REQUIRE_THROWS_WITH(g.replace_node("helloWRONG", "replaced"), "Cannot call gdwg::graph<N, E>::replace_node on a node that doesn't exist");
}

TEST_CASE("replace_node_fail") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"hello", "replace me"};
    auto replaced = g.replace_node("hello", "replace me");
    REQUIRE(!replaced);
    REQUIRE(g.nodes() == std::vector<std::string>{"hello", "replace me"});
}