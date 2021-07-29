// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)

#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

// Simplest test case, makes sure that when calling the default constructor we get a euclidean
// vector like [0]

TEST_CASE("merge_replace_all_covered") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"A", "B", "C", "D"};
    g.insert_edge("A", "B", 1);
    g.insert_edge("A", "A", 5);
    g.insert_edge("A", "C", 2);
    g.insert_edge("C", "A", 9);
    g.insert_edge("A", "D", 3);
    g.insert_edge("B", "B", 9);

    g.merge_replace_node("A", "B");
    REQUIRE(g.nodes() == std::vector<std::string>{"B", "C", "D"});
    REQUIRE(g.connections("B") == std::vector<std::string>{"B", "C", "D"});
    REQUIRE(g.connections("C") == std::vector<std::string>{"B"});
    REQUIRE(g.weights("B", "B") == std::vector<int>{1, 5, 9});
    REQUIRE(g.weights("B", "C") == std::vector<int>{2});
    REQUIRE(g.weights("B", "D") == std::vector<int>{3});
    REQUIRE(g.weights("C", "B") == std::vector<int>{9});
}

TEST_CASE("merge_replace_same") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"A", "B", "C", "D"};
    g.insert_edge("A", "B", 1);
    g.insert_edge("A", "C", 2);
    g.insert_edge("A", "D", 3);
    g.insert_edge("B", "B", 1);
    REQUIRE(g.nodes() == std::vector<std::string>{"A", "B", "C", "D"});
    REQUIRE(g.connections("A") == std::vector<std::string>{"B", "C", "D"});
    REQUIRE(g.weights("B", "B") == std::vector<int>{1});
    REQUIRE(g.weights("B", "C") == std::vector<int>{});
    REQUIRE(g.weights("B", "D") == std::vector<int>{});
    REQUIRE(g.weights("A", "B") == std::vector<int>{1});
    REQUIRE(g.weights("A", "C") == std::vector<int>{2});
    REQUIRE(g.weights("A", "D") == std::vector<int>{3});
    g.merge_replace_node("A", "A");
    REQUIRE(g.nodes() == std::vector<std::string>{"A", "B", "C", "D"});
    REQUIRE(g.connections("A") == std::vector<std::string>{"B", "C", "D"});
    REQUIRE(g.weights("B", "B") == std::vector<int>{1});
    REQUIRE(g.weights("B", "C") == std::vector<int>{});
    REQUIRE(g.weights("B", "D") == std::vector<int>{});
    REQUIRE(g.weights("A", "B") == std::vector<int>{1});
    REQUIRE(g.weights("A", "C") == std::vector<int>{2});
    REQUIRE(g.weights("A", "D") == std::vector<int>{3});
}

TEST_CASE("merge_replace_errors") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"A", "B", "C", "D"};
    g.insert_edge("A", "B", 1);
    g.insert_edge("A", "C", 2);
    g.insert_edge("A", "D", 3);
    g.insert_edge("B", "B", 1);
    REQUIRE_THROWS_WITH(g.merge_replace_node("A", "F"),
                        "Cannot call gdwg::graph<N, E>::merge_replace_node on old or new data if they don't exist in the graph");
    REQUIRE_THROWS_WITH(g.merge_replace_node("G", "F"),
                        "Cannot call gdwg::graph<N, E>::merge_replace_node on old or new data if they don't exist in the graph");
    REQUIRE_THROWS_WITH(g.merge_replace_node("B", "F"),
                        "Cannot call gdwg::graph<N, E>::merge_replace_node on old or new data if they don't exist in the graph");

}