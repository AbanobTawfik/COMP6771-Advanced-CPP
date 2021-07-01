#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

// since we can assume the integer passed into single arguement constructor can always be assumed to be non-negative
// we don't have any other edge cases

TEST_CASE("size_constructor_magnitude_empty") {
    const auto vector = comp6771::euclidean_vector(0, 4);
    REQUIRE(vector.dimensions() == 0);
    REQUIRE(vector.check_cached_norm() == -1);
}

TEST_CASE("size_constructor_magnitude_implicit") {
    const auto vector = comp6771::euclidean_vector(10, 4);
    REQUIRE(vector.dimensions() == 10);
    REQUIRE(vector.check_cached_norm() == -1);
    // check all values defaulting to 0
    for (auto i = 0; i < vector.dimensions(); i++) {
        REQUIRE(vector[i] == 4);
    }
}

TEST_CASE("size_constructor_magnitude_explicit") {
    auto dimension = int{3};
    auto magnitude = double{3.24};
    auto vector_object_initialised = comp6771::euclidean_vector(dimension, magnitude);
    REQUIRE(vector_object_initialised.dimensions() == 3);
    REQUIRE(vector_object_initialised.check_cached_norm() == -1);
    for (auto i = 0; i < dimension; i++) {
        REQUIRE(vector_object_initialised[i] == magnitude);
    }
}