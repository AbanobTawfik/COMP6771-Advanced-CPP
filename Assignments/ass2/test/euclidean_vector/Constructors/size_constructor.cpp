#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <iostream>

// the only cases handled for this constructor is using integer object or using a implicit integer (seen in spec)
// and the final case is for the empty constructor (size = 0), we want to return []

TEST_CASE("size_constructor_implicit") {
    const auto vector = comp6771::euclidean_vector(10);
    REQUIRE(vector.dimensions() == 10);
    // check all values defaulting to 0
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == 0; }));
}

TEST_CASE("size_constructor_explicit") {
    auto dimension = int{3};
    auto vector_object_initialised = comp6771::euclidean_vector(dimension);
    REQUIRE(vector_object_initialised.dimensions() == 3);
    REQUIRE(std::all_of(vector_object_initialised.begin(), vector_object_initialised.end(),
                        [&](auto value) { return value == 0; }));
}

TEST_CASE("size_constructor_empty") {
    const auto vector = comp6771::euclidean_vector(0);
    REQUIRE(vector.dimensions() == 0);
}
