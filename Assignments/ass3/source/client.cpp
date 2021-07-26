#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "gdwg/graph.hpp"

auto main() -> int {
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
    for (const auto& x : v) {
        g.insert_node(x.from);
        g.insert_node(x.to);
        g.insert_edge(x.from, x.to, x.weight);
    };

    g.insert_node(64);
    auto dd = graph(g);
    auto p = *g.begin();
    auto c = g.begin();
    auto d = c++;
    auto vec1 = std::vector<int>{1,2,3,4};
    auto vec2 = std::vector<int>{1,2,3,4};
    auto r = g.begin();
    std::cout << g << std::endl;
    g.erase_edge(r);
    std::cout << g << std::endl;
    auto t = g.begin();
    auto f = (r == t);
//    std::cout << g << std::endl;

}
