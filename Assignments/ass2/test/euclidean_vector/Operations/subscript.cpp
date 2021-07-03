#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>

// for subscript there were many cases to test the following
// 1. checking subscript in the range of vector gives correct value, and doesnt touch the array, so remaining array
//    is unmodified
// 2. checks change for subscript works correctly, not modifying the array besides the one element at the subscriptt
//    we don't test accessing out of bounds index here

// const cases
TEST_CASE("subscript_in_range_correct_value") {
    const auto vector = comp6771::euclidean_vector(10, 50);
    REQUIRE(vector.dimensions() == 10);
    REQUIRE(std::all_of(vector.begin(), vector.end(), [&](auto value){ return value == 50;}));
    auto value = double{vector[0]};
    REQUIRE(value == 50);
    // make sure no changes to the rest of the array
    REQUIRE(vector.dimensions() == 10);
    REQUIRE(std::all_of(vector.begin(), vector.end(), [&](auto value){ return value == 50;}));
}

// non const cases (Changing values at indexes)
TEST_CASE("subscript_change_in_range_default") {
    auto vector = comp6771::euclidean_vector(10, 50);
    REQUIRE(vector.dimensions() == 10);
    REQUIRE(std::all_of(vector.begin(), vector.end(), [&](auto value){ return value == 50;}));
    auto value = double{vector[0]};
    REQUIRE(value == 50);
    vector[0] = value + 1;
    // make sure rest of vector is the same we only modified index 1 so look from beginning + 1 -> end
    REQUIRE(std::all_of(vector.begin() + 1, vector.end(), [&](auto value){ return value == 50;}));
    REQUIRE(vector.dimensions() == 10);
    // check the change went through correctly
    REQUIRE(vector[0] == value + 1);
}