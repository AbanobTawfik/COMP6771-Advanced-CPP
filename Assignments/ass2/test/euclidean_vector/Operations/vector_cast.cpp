#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

// empty array
TEST_CASE("empty_vector_to_vec") {
    const auto vector = comp6771::euclidean_vector(0);
    REQUIRE(vector.dimensions() == 0);
    const auto casted_vector = static_cast<std::vector<double>>(vector);
    REQUIRE(casted_vector.empty());
    const auto recreated_from_cast = comp6771::euclidean_vector(casted_vector.begin(), casted_vector.end());
    REQUIRE(recreated_from_cast.dimensions() == 0);
    REQUIRE(recreated_from_cast == vector);
}

// array with values
TEST_CASE("same_values_vector_to_vec") {
    const auto size = 5;
    const auto val = 3;
    const auto vector = comp6771::euclidean_vector(size, val);
    REQUIRE(vector.dimensions() == size);
    bool all_values_same = std::all_of(vector.begin(), vector.end(), [&](auto value) { return value == val; });
    REQUIRE(all_values_same);

    const auto casted_vector = static_cast<std::vector<double>>(vector);
    REQUIRE(casted_vector.size() == size);
    all_values_same = std::all_of(casted_vector.begin(), casted_vector.end(),
                                  [&](auto value) { return value == val; });
    REQUIRE(all_values_same);

    // now we cast back and see if we get the same result
    const auto recreated_from_cast = comp6771::euclidean_vector(casted_vector.begin(), casted_vector.end());
    REQUIRE(recreated_from_cast.dimensions() == 5);
    all_values_same = std::all_of(recreated_from_cast.begin(), recreated_from_cast.end(),
                                  [&](auto value) { return value == val; });
    REQUIRE(all_values_same);
}


// create euclidean vector with std vector, then cast it as std vector to see if same result
TEST_CASE("vector_recasts") {
    const auto size = 500;
    const auto value = -500.434;
    auto count = 0;
    auto stdvector = std::vector<double>(size);
    // values using iota will be steadily increasing so all different
    std::iota(stdvector.begin(), stdvector.end(), value);
    // creating a euclidean vector with standard vector
    const auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
    REQUIRE(vector.dimensions() == stdvector.size());
    REQUIRE(vector.dimensions() == size);
    bool all_values_same = std::all_of(vector.begin(), vector.end(),
                                       [&](auto value) { return value == stdvector.at(count++); });
    REQUIRE(all_values_same);
    // now we will cast that euclidean vector we verified was the same as the standard vector used to create it
    // and compare the two vectors
    auto stdvector_casted = static_cast<std::vector<double>>(vector);
    REQUIRE(std::equal(stdvector.begin(), stdvector.end(), stdvector_casted.begin(), stdvector_casted.end()));
}