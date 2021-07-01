#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

// since we don't have a constructor which lets us take in 2 generic iterators, i can't do as extensive of testing
// as i did on vector, however the code for both are almost identical, so if vector works, list will also work.

// empty array
TEST_CASE("empty_vector_to_list") {
    const auto vector = comp6771::euclidean_vector(0);
    REQUIRE(vector.dimensions() == 0);
    const auto casted_list = static_cast<std::list<double>>(vector);
    REQUIRE(casted_list.empty());
}

// array with values
TEST_CASE("same_values_vector_to_list") {
    const auto size = 5;
    const auto val = 3;
    const auto vector = comp6771::euclidean_vector(size, val);
    REQUIRE(vector.dimensions() == size);
    bool all_values_same = std::all_of(vector.cbegin(), vector.cend(), [&](auto value) { return value == val; });
    REQUIRE(all_values_same);

    const auto casted_list = static_cast<std::list<double>>(vector);
    REQUIRE(casted_list.size() == size);
    all_values_same = std::all_of(casted_list.cbegin(), casted_list.cend(),
                                  [&](auto value) { return value == val; });
    REQUIRE(all_values_same);
}