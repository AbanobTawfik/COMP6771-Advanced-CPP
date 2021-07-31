// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)

#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("merge_replace_all_covered") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"A", "B", "C", "D"};
    g.insert_edge("A", "B", 1);
    g.insert_edge("A", "A", 1);
    g.insert_edge("A", "A", 5);
    g.insert_edge("A", "C", 2);
    g.insert_edge("C", "A", 9);
    g.insert_edge("A", "D", 3);
    g.insert_edge("B", "B", 9);
    g.merge_replace_node("A", "B");
    SECTION("Check the graph state after merge replace") {
        CHECK(g.nodes() == std::vector<std::string>{"B", "C", "D"});
        CHECK(g.connections("B") == std::vector<std::string>{"B", "C", "D"});
        CHECK(g.connections("C") == std::vector<std::string>{"B"});
        CHECK(g.weights("B", "B") == std::vector<int>{1, 5, 9});
        CHECK(g.weights("B", "C") == std::vector<int>{2});
        CHECK(g.weights("B", "D") == std::vector<int>{3});
        CHECK(g.weights("C", "B") == std::vector<int>{9});
    }
}

TEST_CASE("merge_replace_same") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"A", "B", "C", "D"};
    g.insert_edge("A", "B", 1);
    g.insert_edge("A", "C", 2);
    g.insert_edge("A", "D", 3);
    g.insert_edge("B", "B", 1);
    SECTION("Check graph before merge replace is called") {
        CHECK(g.nodes() == std::vector<std::string>{"A", "B", "C", "D"});
        CHECK(g.connections("A") == std::vector<std::string>{"B", "C", "D"});
        CHECK(g.weights("B", "B") == std::vector<int>{1});
        CHECK(g.weights("B", "C") == std::vector<int>{});
        CHECK(g.weights("B", "D") == std::vector<int>{});
        CHECK(g.weights("A", "B") == std::vector<int>{1});
        CHECK(g.weights("A", "C") == std::vector<int>{2});
        CHECK(g.weights("A", "D") == std::vector<int>{3});
    }
    g.merge_replace_node("A", "A");
    SECTION("Check same state of graph after merge replacing with the same node") {
        CHECK(g.nodes() == std::vector<std::string>{"A", "B", "C", "D"});
        CHECK(g.connections("A") == std::vector<std::string>{"B", "C", "D"});
        CHECK(g.weights("B", "B") == std::vector<int>{1});
        CHECK(g.weights("B", "C") == std::vector<int>{});
        CHECK(g.weights("B", "D") == std::vector<int>{});
        CHECK(g.weights("A", "B") == std::vector<int>{1});
        CHECK(g.weights("A", "C") == std::vector<int>{2});
        CHECK(g.weights("A", "D") == std::vector<int>{3});
    }
}

TEST_CASE("merge_replace_errors") {
    using graph = gdwg::graph<std::string, int>;
    auto g = graph{"A", "B", "C", "D"};
    g.insert_edge("A", "B", 1);
    g.insert_edge("A", "C", 2);
    g.insert_edge("A", "D", 3);
    g.insert_edge("B", "B", 1);
    CHECK_THROWS_WITH(g.merge_replace_node("A", "F"),
                        "Cannot call gdwg::graph<N, E>::merge_replace_node on old or new data if they don't exist in the graph");
    CHECK_THROWS_WITH(g.merge_replace_node("G", "F"),
                        "Cannot call gdwg::graph<N, E>::merge_replace_node on old or new data if they don't exist in the graph");
    CHECK_THROWS_WITH(g.merge_replace_node("B", "F"),
                        "Cannot call gdwg::graph<N, E>::merge_replace_node on old or new data if they don't exist in the graph");
}