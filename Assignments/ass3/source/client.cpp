#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "gdwg/graph.hpp"

auto main() -> int {
    auto g = gdwg::graph<std::string, int>{};
    g.insert_node("a");
    g.insert_node("b");
    g.insert_node("c");
    g.insert_node("you?");

    g.insert_edge("a", "b", 3);
    g.insert_edge("a", "c", 2);
    g.insert_edge("b", "c", 1);

    auto x = g.weights("a", "b");

}