#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <iostream>
#include <vector>

// the only two types of vectors we can pass in are the empty vector, or a vector populated with values
// Test case 1: empty vector -> empty euclidean vector
// test case 2: populated vector -> populated euclidean vector with same values at same indicies

TEST_CASE("empty_vector_constructor") {
    const auto stdvec = std::vector<double>();
    const auto euclidean_vec = comp6771::euclidean_vector(stdvec.begin(), stdvec.end());
    REQUIRE(euclidean_vec.dimensions() == 0);
}

TEST_CASE("normal_vector_with_different_values") {
    const auto size = 500;
    const auto value = -500.434;
    auto stdvector = std::vector<double>(size);
    // values using iota will be steadily increasing so all different
    std::iota(stdvector.begin(), stdvector.end(), value);
    const auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
    REQUIRE(vector.dimensions() == stdvector.size());
    REQUIRE(vector.dimensions() == size);
    auto count = 0;
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == stdvector.at(count++); }));
}