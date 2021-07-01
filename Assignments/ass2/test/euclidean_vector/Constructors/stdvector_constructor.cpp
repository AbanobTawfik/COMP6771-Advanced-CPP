#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

// since we can assume the integer passed into single arguement constructor can always be assumed to be non-negative
// we don't have any other edge cases

TEST_CASE("empty_vector_constructor") {
    const auto stdvec = std::vector<double>();
    const auto euclidean_vec = comp6771::euclidean_vector(stdvec.begin(), stdvec.end());
    REQUIRE(euclidean_vec.dimensions() == 0);
    REQUIRE(euclidean_vec.check_cached_norm() == -1);
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
    REQUIRE(vector.check_cached_norm() == -1);
    bool all_values_same = true;
    for (auto i = 0; i < size; i++) {
        if (vector.at(i) != vector.at(i)) {
            all_values_same = false;
            break;
        }
    }
    REQUIRE(all_values_same);
}