#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

TEST_CASE("default_constructor_euclidean_vector") {
    const auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
    const auto euclidean_norm = comp6771::euclidean_norm(vector);
    REQUIRE(euclidean_norm == 0);
}

TEST_CASE("empty_constructor_euclidean_vector") {
    const auto vector = comp6771::euclidean_vector(0);
    REQUIRE(vector.dimensions() == 0);
    const auto euclidean_norm = comp6771::euclidean_norm(vector);
    REQUIRE(euclidean_norm == 0);
}

TEST_CASE("euclidean_vector_with_values") {
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
    const auto euclidean_norm = comp6771::euclidean_norm(vector);
    REQUIRE(euclidean_norm >= 0);
    double actual_euclidean_norm = 0;
    for(auto value : vector){
        actual_euclidean_norm += value*value;
    }
    actual_euclidean_norm = std::sqrt(actual_euclidean_norm);
    REQUIRE(euclidean_norm == actual_euclidean_norm);
}