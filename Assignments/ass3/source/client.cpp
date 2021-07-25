#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "gdwg/graph.hpp"

auto main() -> int {
//    auto x = std::vector<std::string>{"hello", "hi", "bye"};
//    auto g = gdwg::graph<std::string, int>(x.begin(), x.end());
//    g.insert_node("pooo");
//    auto b = g.insert_edge("hello", "hi", 5);
//    auto c = g.insert_edge("hello", "hi", 5);
//    std::cout << b << std::endl;
//    auto g = gdwg::graph<std::string, int>();
//    g.insert_node("A");
//    g.insert_node("B");
//    g.insert_node("C");
//    g.insert_node("D");
//    g.insert_node("E");
//    g.insert_edge("A", "B", 1);
//    g.insert_edge("A", "C", 2);
//    g.insert_edge("A", "C", 44);
//    g.insert_edge("A", "D", 3);
//    g.insert_edge("B", "B", 1);
//    auto weight = g.weights("A", "B");
//    auto weightzzzz = g.connections("A");
//    auto out = std::ostringstream {};
//    out << g << std::endl;


//    g.merge_replace_node("A", "B");
    //g.is_connected("A","C");
//    g.insert_edge("B", "C", 1);
//    g.insert_edge("B", "D", 2);
//    g.insert_edge("B", "E", 3);
//    g.insert_edge("C", "D", 1);
//    g.insert_edge("D", "E", 4);
//
//    g.merge_replace_node("D", "A");
//	std::cout << g << "\n";
//
//	auto g2 = gdwg::graph<std::string, int>(g);
//
//	std::cout << g2 << "\n";
//
//	// This is a structured binding.
//	// https://en.cppreference.com/w/cpp/language/structured_binding
//	// It allows you to unpack your tuple.
//	for (auto const& [from, to, weight] : g) {
//		std::cout << from << " -> " << to << " (weight " << weight << ")\n";
//	}
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
//    auto out = std::ostringstream{};
//    out << g;
    std::cout << g << std::endl;
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

}
