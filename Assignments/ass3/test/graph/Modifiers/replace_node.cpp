// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("replace_node_success") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"hello", "replace me"};
    g.insert_edge("hello", "replace me", 5);
    auto replaced = g.replace_node("hello", "replaced_hello");
    CHECK(replaced);
    auto is_connected = g.is_connected("replaced_hello", "replace me");
    CHECK(is_connected);
    replaced = g.replace_node("replace me", "replaced");
    CHECK(replaced);
    is_connected = g.is_connected("replaced_hello", "replaced");
    CHECK(is_connected);
    CHECK(g.nodes() == std::vector<std::string>{"replaced", "replaced_hello"});
    CHECK(g.connections("replaced_hello") == std::vector<std::string>{"replaced"});
    CHECK(g.weights("replaced_hello", "replaced") == std::vector<int>{5});
}

TEST_CASE("replace_node_errors") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"hello", "replace me"};
    CHECK_THROWS_WITH(g.replace_node("helloWRONG", "replaced"), "Cannot call gdwg::graph<N, E>::replace_node on a node that doesn't exist");
}

TEST_CASE("replace_node_fail") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"hello", "replace me"};
    auto replaced = g.replace_node("hello", "replace me");
    CHECK(!replaced);
    CHECK(g.nodes() == std::vector<std::string>{"hello", "replace me"});
}