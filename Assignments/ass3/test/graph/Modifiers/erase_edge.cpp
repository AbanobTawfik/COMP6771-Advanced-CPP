// We don't own this macro; don't prefix it with `COMP6771_`.
#define CATCH_CONFIG_MAIN // NOLINT(readability-identifier-naming)
#include "catch2/catch.hpp"

#include "gdwg/graph.hpp"

TEST_CASE("remove_edges_default") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    g.insert_edge(1, 2, 9);
    SECTION("Checking graph before erase conditions") {
        CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4});
        CHECK(g.connections(1) == std::vector<int>{2});
        CHECK(g.weights(1, 2) == std::vector<int>{9});
        CHECK(g.connections(2) == std::vector<int>{});
        CHECK(g.connections(3) == std::vector<int>{});
        CHECK(g.connections(4) == std::vector<int>{});
    }
    SECTION("Removing the edge and checking graph post conditions"){
        CHECK(g.erase_edge(1, 2, 9));
        CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4});
        CHECK(g.connections(1) == std::vector<int>{});
        CHECK(g.weights(1, 2) == std::vector<int>{});
        CHECK(g.connections(2) == std::vector<int>{});
        CHECK(g.connections(3) == std::vector<int>{});
        CHECK(g.connections(4) == std::vector<int>{});
    }
}

TEST_CASE("remove_edges_errors") {
    using graph = gdwg::graph<int, int>;
    auto g = graph{1, 2, 3, 4};
    g.insert_edge(1, 2, 9);
    SECTION("Check graph is made properly") {
        CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4});
        CHECK(g.connections(1) == std::vector<int>{2});
        CHECK(g.weights(1, 2) == std::vector<int>{9});
        CHECK(g.connections(2) == std::vector<int>{});
        CHECK(g.connections(3) == std::vector<int>{});
        CHECK(g.connections(4) == std::vector<int>{});
    }
    SECTION("erase edge returns false for nodes that exist") {
        CHECK(!g.erase_edge(1, 2, 99));
        CHECK(!g.erase_edge(1, 3, 99));
        CHECK(!g.erase_edge(2, 2, 99));
        CHECK(!g.erase_edge(2, 2, 9));
    }
    SECTION("erase edge throws exception when nodes either from and to dont exist") {
        CHECK_THROWS_WITH(g.erase_edge(2, 29, 9),
                          "Cannot call gdwg::graph<N, E>::erase_edge on src or dst if they don't exist in the graph");
        CHECK_THROWS_WITH(g.erase_edge(29, 2, 9),
                          "Cannot call gdwg::graph<N, E>::erase_edge on src or dst if they don't exist in the graph");
        CHECK_THROWS_WITH(g.erase_edge(82, 29, 9),
                          "Cannot call gdwg::graph<N, E>::erase_edge on src or dst if they don't exist in the graph");
    }
    SECTION("Check graph is unmodified from these fail cases above") {
        CHECK(g.nodes() == std::vector<int>{1, 2, 3, 4});
        CHECK(g.connections(1) == std::vector<int>{2});
        CHECK(g.weights(1, 2) == std::vector<int>{9});
        CHECK(g.connections(2) == std::vector<int>{});
        CHECK(g.connections(3) == std::vector<int>{});
        CHECK(g.connections(4) == std::vector<int>{});
    }
}