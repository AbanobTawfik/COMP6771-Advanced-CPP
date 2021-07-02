#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

TEST_CASE("dot_product_empty_vectors") {
    const auto left_vector = comp6771::euclidean_vector();
    REQUIRE(left_vector.dimensions() == 1);
    REQUIRE(left_vector[0] == 0);

    const auto right_vector = comp6771::euclidean_vector();
    REQUIRE(right_vector.dimensions() == 1);
    REQUIRE(right_vector[0] == 0);

    const auto dot_product = comp6771::dot(left_vector, right_vector);

    // make sure dot product is correctly calculated
    // [0] . [0] = 0 + 0 -> 0
    REQUIRE(dot_product == 0);
}

TEST_CASE("dot_product_with_different_values") {
    const auto size = 500;
    const auto value = -500.434;
    auto left_stdvector = std::vector<double>(size);
    // values using iota will be steadily increasing so all different
    std::iota(left_stdvector.begin(), left_stdvector.end(), value);
    auto left_vector = comp6771::euclidean_vector(left_stdvector.begin(), left_stdvector.end());
    REQUIRE(left_vector.dimensions() == left_stdvector.size());
    REQUIRE(left_vector.dimensions() == size);
    auto count = 0;
    auto count2 = 0;
    bool all_values_same = std::all_of(left_vector.begin(), left_vector.end(),
                                       [&](auto value) { return value == left_stdvector.at(count++); });
    REQUIRE(all_values_same);

    const auto value2 = 6342;
    auto right_stdvector = std::vector<double>(size);
    // values using iota will be steadily increasing so all different
    std::iota(right_stdvector.begin(), right_stdvector.end(), value2);
    auto right_vector = comp6771::euclidean_vector(right_stdvector.begin(), right_stdvector.end());
    REQUIRE(right_vector.dimensions() == right_stdvector.size());
    REQUIRE(right_vector.dimensions() == size);
    count = 0;
    all_values_same = std::all_of(right_vector.begin(), right_vector.end(),
                                  [&](auto value) { return value == right_stdvector.at(count++); });
    REQUIRE(all_values_same);
    // keep in mind our original 2 std vectors stay the same, so we will compare the values in them to the result below
    const auto dot_product = comp6771::dot(left_vector, right_vector);
    REQUIRE(right_vector.dimensions() == size);
    REQUIRE(left_vector.dimensions() == size);
    // make sure right vector and left vector doesn't change
    count = 0;
    all_values_same = std::all_of(left_vector.begin(), left_vector.end(),
                                  [&](auto value) { return value == left_vector.at(count++); });
    REQUIRE(all_values_same);
    count = 0;
    all_values_same = std::all_of(right_vector.begin(), right_vector.end(),
                                  [&](auto value) { return value == right_stdvector.at(count++); });
    REQUIRE(all_values_same);
    // now i need to check the dot product contains, the right value, the dot product is simply just the sum
    // of all vector values at the same index multiplied together, [1 2 3] [3 2 1] -> 1*3 + 2*2 + 3*1 = 10
    // so we will manually compute this the long way here and compare to the much more concise solution found in the class
    double dot_product_compare = 0;
    for(auto i = 0; i < size; i++){
        dot_product_compare += left_vector[i] * right_vector[i];
    }
    REQUIRE(dot_product == dot_product_compare);
}

// Exception, different sizes
TEST_CASE("dot_product_different_size") {
    const auto size1 = 3;
    const auto size2 = 5;
    REQUIRE(size1 != size2);
    const auto val = 3;
    auto left_vector = comp6771::euclidean_vector(size1, val);
    auto right_vector = comp6771::euclidean_vector(size2, val);
    REQUIRE(left_vector.dimensions() == size1);
    REQUIRE(right_vector.dimensions() == size2);
    bool all_values_same = std::all_of(left_vector.begin(), left_vector.end(),
                                       [&](auto value) { return value == val; });
    REQUIRE(all_values_same);
    all_values_same = std::all_of(right_vector.begin(), right_vector.end(),
                                  [&](auto value) { return value == val; });
    REQUIRE(all_values_same);
    REQUIRE_THROWS_WITH(comp6771::dot(left_vector, right_vector),
                        "Dimensions of LHS(" + std::to_string(size1) + ") and RHS (" + std::to_string(size2) +
                        ") do not match\n");
}