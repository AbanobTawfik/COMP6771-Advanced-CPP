#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

TEST_CASE("basic_addition_empty_vectors") {
    auto left_vector = comp6771::euclidean_vector(0);
    auto right_vector = comp6771::euclidean_vector(0);
    REQUIRE(left_vector.dimensions() == 0);
    REQUIRE(right_vector.dimensions() == 0);

    left_vector += right_vector;
    // make sure dimensions dont change, nothing should happen, [] + [] = []
    REQUIRE(left_vector.dimensions() == 0);
    REQUIRE(right_vector.dimensions() == 0);
}

TEST_CASE("basic_addition_case_all_same") {
    auto size = 3;
    auto l_value = 3;
    auto r_value = 4;
    auto left_vector = comp6771::euclidean_vector(size, l_value);
    REQUIRE(left_vector.dimensions() == size);
    bool all_values_same = std::all_of(left_vector.begin(), left_vector.end(),
                                       [&](auto value) { return value == l_value; });
    REQUIRE(all_values_same);
    auto right_vector = comp6771::euclidean_vector(size, r_value);
    REQUIRE(right_vector.dimensions() == size);
    all_values_same = std::all_of(right_vector.begin(), right_vector.end(),
                                  [&](auto value) { return value == r_value; });
    REQUIRE(all_values_same);
    left_vector += right_vector;
    REQUIRE(left_vector.dimensions() == 3);
    REQUIRE(right_vector.dimensions() == 3);
    // make sure right hand side is unaffected
    all_values_same = std::all_of(right_vector.begin(), right_vector.end(),
                                  [&](auto value) { return value == r_value; });
    REQUIRE(all_values_same);
    // check the addition worked correctly
    auto values_updated_correctly = std::all_of(left_vector.begin(), left_vector.end(),
                                                [&](auto value) { return value == l_value + r_value; });
    REQUIRE(values_updated_correctly);
}

TEST_CASE("basic_addition_case_different_values") {
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
    left_vector += right_vector;
    REQUIRE(right_vector.dimensions() == size);
    REQUIRE(left_vector.dimensions() == size);
    count = 0;
    bool values_updated_correctly = std::all_of(left_vector.begin(), left_vector.end(),
                                                [&](auto value) {
                                                    return value == left_stdvector.at(count++) +
                                                                    right_stdvector.at(count2++);
                                                });
    REQUIRE(values_updated_correctly);
}