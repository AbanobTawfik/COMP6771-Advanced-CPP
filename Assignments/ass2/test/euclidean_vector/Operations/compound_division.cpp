#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <iostream>
#include <vector>

// for testing division a few things were tested for the sake of completeness
// 1. division on empty vector [] / scale = []
// 2. division on vector with values should divide each index value by scale correctly
// 3. checking dividing by 1 is the same as unary
// 3. checking dividing by -1 is the same as negation
// 4. checking dividing by 0 throws the correct exception alongside leaving the original vector unmodified

TEST_CASE("basic_compound_division_empty_vectors") {
    auto left_vector = comp6771::euclidean_vector(0);
    auto left_vector_copy = left_vector;
    const auto scale = 1.34;
    REQUIRE(left_vector.dimensions() == 0);
    left_vector /= scale;
    // make sure no changes
    REQUIRE(left_vector.dimensions() == 0);
    REQUIRE(left_vector == left_vector_copy);
}

TEST_CASE("basic_compound_division_case_different_values") {
    const auto size = 500;
    const auto value = -500.434;
    const auto scale = -34.9849;
    auto count = 0;
    auto stdvector = std::vector<double>(size);
    // values using iota will be steadily increasing so all different
    std::iota(stdvector.begin(), stdvector.end(), value);
    auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
    REQUIRE(vector.dimensions() == stdvector.size());
    REQUIRE(vector.dimensions() == size);
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == stdvector.at(count++); }));

    vector /= scale;
    // check the compound_division worked correctly
    count = 0;
    // for this example since conversions are precise and there is arithmetic rounding errors, dividing by 34.9845
    // and values are 3 decimal places too, this checks values are atleast within 4 decimal places
    const auto difference = 0.00001;
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) {
                            return std::abs(value - (stdvector.at(count++) / scale)) <
                                   difference;
                        }));
}

TEST_CASE("compound_division_negation_same") {
    auto scale = -1;
    auto size = 5;
    auto val = 3;
    auto vector = comp6771::euclidean_vector(size, val);
    auto pre_compound_division = comp6771::euclidean_vector(size, val);
    REQUIRE(vector.dimensions() == size);
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == val; }));
    REQUIRE(vector == pre_compound_division);

    vector /= scale;
    REQUIRE(vector.dimensions() == size);
    // check the compound_division worked correctly
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == val / scale; }));
    REQUIRE(vector == -pre_compound_division);
}

TEST_CASE("compound_division_unary_same") {
    auto scale = 1;
    auto size = 5;
    auto val = 3;
    auto vector = comp6771::euclidean_vector(size, val);
    auto pre_compound_division = comp6771::euclidean_vector(size, val);
    REQUIRE(vector.dimensions() == size);
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == val; }));
    REQUIRE(vector == pre_compound_division);

    vector /= scale;
    REQUIRE(vector.dimensions() == size);
    // check the compound_division worked correctly
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == val / scale; }));
    REQUIRE(vector == +pre_compound_division);
}
// HANDLE EXCEPTIONS NOW
// divide by 0 case
TEST_CASE("compound_division_scale_0") {
    const auto scale = 0;
    auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
    REQUIRE_THROWS_WITH(vector /= scale,
                        "Invalid vector division by 0\n");
    // NO CHANGES!
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
}
