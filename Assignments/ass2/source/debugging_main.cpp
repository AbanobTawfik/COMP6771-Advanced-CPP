#include "comp6771/euclidean_vector.hpp"
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>
//  Please note: it's not good practice to test your code via a main function that does
//  printing. Instead, you should be using your test folder. This file should only really
//  be used for more "primitive" debugging as we know that working solely with test
//  frameworks might be overwhelming for some.

auto my_begin(comp6771::euclidean_vector vec) -> std::vector<double>::iterator {
    auto vector = std::vector<double>();
    for(auto i = 0; i < vec.dimensions(); i++){
        vector.push_back(vec[i]);
    }
    return vector.begin();
}

auto my_end(comp6771::euclidean_vector vec) -> std::vector<double>::iterator {
    auto vector = std::vector<double>();
    for(auto i = 0; i < vec.dimensions(); i++){
        vector.push_back(vec[i]);
    }
    return vector.end();
}

auto main() -> int {
	auto x = comp6771::euclidean_vector(50);
	auto begin = my_begin(x);
	auto end = my_end(x);
	auto check = std::all_of(begin, end, [](auto value){return value == 0;});
    std::cout << check << std::endl;
}

