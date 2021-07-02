#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

// normal correct cases
TEST_CASE("basic_multiplication_empty_vectors") {
    auto left_vector = comp6771::euclidean_vector(0);
    const auto scale = 0;
    REQUIRE(left_vector.dimensions() == 0);
    const auto multiplied_vector = left_vector * scale;
    // make sure no changes to left vector
    REQUIRE(left_vector.dimensions() == 0);
    // make sure multiplied vector has the results we want
    REQUIRE(multiplied_vector.dimensions() == 0);
    REQUIRE(multiplied_vector == left_vector);
}

TEST_CASE("basic_multiplication_case_all_same") {
    auto scale = 3;
    auto size = 5;
    auto val = 3;
    auto vector = comp6771::euclidean_vector(size, val);
    REQUIRE(vector.dimensions() == size);
    bool all_values_same = std::all_of(vector.begin(), vector.end(),
                                       [&](auto value) { return value == val; });
    REQUIRE(all_values_same);

    const auto multiplied_vector = vector * scale;

    // check original vector is unchanged
    REQUIRE(vector.dimensions() == size);
    auto values_updated_correctly = std::all_of(vector.begin(), vector.end(),
                                                [&](auto value) { return value == val; });
    REQUIRE(values_updated_correctly);
    // check the multiplication worked correctly
    REQUIRE(multiplied_vector.dimensions() == size);
    values_updated_correctly = std::all_of(multiplied_vector.begin(), multiplied_vector.end(),
                                           [&](auto value) { return value == val * scale; });
    REQUIRE(values_updated_correctly);
}

TEST_CASE("basic_multiplication_case_different_values") {
    const auto size = 500;
    const auto value = -500.434;
    const auto scale = -34.9845;
    auto count = 0;
    auto stdvector = std::vector<double>(size);
    // values using iota will be steadily increasing so all different
    std::iota(stdvector.begin(), stdvector.end(), value);
    auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
    REQUIRE(vector.dimensions() == stdvector.size());
    REQUIRE(vector.dimensions() == size);
    bool all_values_same = std::all_of(vector.begin(), vector.end(),
                                       [&](auto value) { return value == stdvector.at(count++); });
    REQUIRE(all_values_same);

    const auto multiplied_vector = vector * scale;
    // check original vector is unchanged
    REQUIRE(vector.dimensions() == size);
    count = 0;
    all_values_same = std::all_of(vector.begin(), vector.end(),
                                  [&](auto value) { return value == stdvector.at(count++); });
    REQUIRE(all_values_same);
    // check the multiplication worked correctly
    count = 0;
    auto values_updated_correctly = std::all_of(multiplied_vector.begin(), multiplied_vector.end(),
                                                [&](auto value) { return value == stdvector.at(count++) * scale; });
    REQUIRE(values_updated_correctly);
}

TEST_CASE("multiplication_negation_same") {
    auto scale = -1;
    auto size = 5;
    auto val = 3;
    auto vector = comp6771::euclidean_vector(size, val);
    REQUIRE(vector.dimensions() == size);
    bool all_values_same = std::all_of(vector.begin(), vector.end(),
                                       [&](auto value) { return value == val; });
    REQUIRE(all_values_same);

    const auto multiplied_vector = vector * scale;
    // check original vector is unchanged
    REQUIRE(vector.dimensions() == size);
    all_values_same = std::all_of(vector.begin(), vector.end(),
                                  [&](auto value) { return value == val; });
    REQUIRE(all_values_same);

    // check the multiplication worked correctly
    REQUIRE(multiplied_vector.dimensions() == size);
    auto values_updated_correctly = std::all_of(multiplied_vector.begin(), multiplied_vector.end(),
                                                [&](auto value) { return value == val * scale; });
    REQUIRE(values_updated_correctly);
    REQUIRE(multiplied_vector == -vector);
}

TEST_CASE("multiplication_unary_same") {
    auto scale = 1;
    auto size = 5;
    auto val = 3;
    auto vector = comp6771::euclidean_vector(size, val);
    REQUIRE(vector.dimensions() == size);
    bool all_values_same = std::all_of(vector.begin(), vector.end(),
                                       [&](auto value) { return value == val; });
    REQUIRE(all_values_same);

    const auto multiplied_vector = vector * scale;
    // check original vector is unchanged
    REQUIRE(vector.dimensions() == size);
    all_values_same = std::all_of(vector.begin(), vector.end(),
                                                [&](auto value) { return value == val; });
    REQUIRE(all_values_same);

    // check the multiplication worked correctly
    REQUIRE(multiplied_vector.dimensions() == size);
    auto values_updated_correctly = std::all_of(multiplied_vector.begin(), multiplied_vector.end(),
                                                [&](auto value) { return value == val * scale; });
    REQUIRE(values_updated_correctly);
    REQUIRE(multiplied_vector == +vector);
}