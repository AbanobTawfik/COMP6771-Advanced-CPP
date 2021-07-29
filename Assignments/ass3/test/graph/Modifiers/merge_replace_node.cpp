// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

// This file is designed to act as the program entry point. Everything is defined in catch.hpp, so
// we don't need to worry about doing anything other than indicating our interest to use it via the
// CATCH_CONFIG_MAIN macro.
#include "gdwg/graph.hpp"

// Simplest test case, makes sure that when calling the default constructor we get a euclidean
// vector like [0]

TEST_CASE("merge_replace_simple") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"A", "B", "C", "D"};
    g.insert_edge("A", "B", 1);
    g.insert_edge("A", "A", 5);
    g.insert_edge("A", "C", 2);
    g.insert_edge("C", "A", 9);
    g.insert_edge("A", "D", 3);
    g.insert_edge("B", "B", 1);
    g.merge_replace_node("A", "B");
//    REQUIRE(g.nodes() == std::vector<std::string>{"B", "C", "D"});
//    auto connections = g.connections("B");
//    REQUIRE(g.connections("B") == std::vector<std::string>{"B", "C", "D"});
//    REQUIRE(g.connections("C") == std::vector<std::string>{"B"});
////    REQUIRE(g.weights("B", "B") == std::vector<int>{1, 5});
//    REQUIRE(g.weights("B", "C") == std::vector<int>{2});
//    REQUIRE(g.weights("B", "D") == std::vector<int>{3});
//    REQUIRE(g.weights("C", "B") == std::vector<int>{9});
    std::cout << g << std::endl;
}

TEST_CASE("merge_replace_keeps_sorted") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"A", "B", "C", "D"};
    g.insert_edge("A", "B", 1);
    g.insert_edge("A", "C", 2);
    g.insert_edge("C", "D", 3);
    g.insert_edge("C", "A", 2);
    g.insert_edge("A", "D", 3);
    g.insert_edge("B", "B", 1);
    g.insert_edge("B", "B", 1);
    g.merge_replace_node("A", "B");
    REQUIRE(g.nodes() == std::vector<std::string>{"B", "C", "D"});
    REQUIRE(g.connections("B") == std::vector<std::string>{"B", "C", "D"});
    REQUIRE(g.weights("B", "B") == std::vector<int>{1});
    REQUIRE(g.weights("B", "C") == std::vector<int>{2});
    REQUIRE(g.weights("B", "D") == std::vector<int>{3});
}

TEST_CASE("merge_replace_keeps_errors") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"A", "B", "C", "D"};
    g.insert_edge("A", "B", 1);
    g.insert_edge("A", "C", 2);
    g.insert_edge("A", "D", 3);
    g.insert_edge("B", "B", 1);
    g.merge_replace_node("A", "B");
    REQUIRE(g.nodes() == std::vector<std::string>{"B", "C", "D"});
    REQUIRE(g.connections("B") == std::vector<std::string>{"B", "C", "D"});
    REQUIRE(g.weights("B", "B") == std::vector<int>{1});
    REQUIRE(g.weights("B", "C") == std::vector<int>{2});
    REQUIRE(g.weights("B", "D") == std::vector<int>{3});
}