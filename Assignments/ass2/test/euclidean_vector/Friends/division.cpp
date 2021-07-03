#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// divison testing is im similair to multiplication however we also check exception of dividing by 0
// 1. empty vector case [] / scale = [] no matter what scale that isn't exaclty 0
// 2. vector with values divided by scale should divide the vector correctly
// 3. division with scale -1 should give the same result as negation, vec / -1 == -vec
// 4. division with scale 1 should give the same result as unary, vec / 1 == +vec

TEST_CASE("basic_division_empty_vectors") {
    auto left_vector = comp6771::euclidean_vector(0);
    const auto scale = 1;
    REQUIRE(left_vector.dimensions() == 0);
    const auto divided_vector = left_vector / scale;
    // make sure no changes to left vector
    REQUIRE(left_vector.dimensions() == 0);
    // make sure divided vector has the results we want
    REQUIRE(divided_vector.dimensions() == 0);
    REQUIRE(divided_vector == left_vector);
}

TEST_CASE("basic_division_case_different_values") {
    const auto size = 500;
    const auto value = -500.434;
    const auto scale = -34.9845;
    auto stdvector = std::vector<double>(size);
    std::iota(stdvector.begin(), stdvector.end(), value);
    auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
    REQUIRE(vector.dimensions() == stdvector.size());
    REQUIRE(vector.dimensions() == size);
    REQUIRE(std::equal(vector.begin(), vector.end(), stdvector.begin(), stdvector.end()));

    const auto divided_vector = vector / scale;
    // check original vector is unchanged
    REQUIRE(vector.dimensions() == size);
    REQUIRE(std::equal(vector.begin(), vector.end(), stdvector.begin(), stdvector.end()));
    // check the division worked correctly
    auto count = 0;
    // we check the values are within a range of the difference below as floating point conversion can be lossy and
    // precision errors
    const auto difference = 0.00001;
    REQUIRE(std::all_of(divided_vector.begin(), divided_vector.end(),
                        [&](auto value) {
                            return std::abs(value - (stdvector.at(count++) / scale)) < difference;
                        }));
}

TEST_CASE("division_negation_same") {
    auto scale = -1;
    auto size = 5;
    auto val = 3;
    auto vector = comp6771::euclidean_vector(size, val);
    REQUIRE(vector.dimensions() == size);
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == val; }));

    const auto divided_vector = vector / scale;
    // check original vector is unchanged
    REQUIRE(vector.dimensions() == size);
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == val; }));

    // check the division worked correctly
    REQUIRE(divided_vector.dimensions() == size);
    REQUIRE(std::all_of(divided_vector.begin(), divided_vector.end(),
                        [&](auto value) { return value == val / scale; }));
    REQUIRE(divided_vector == -vector);
}

TEST_CASE("division_unary_same") {
    auto scale = 1;
    auto size = 5;
    auto val = 3;
    auto vector = comp6771::euclidean_vector(size, val);
    REQUIRE(vector.dimensions() == size);
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == val; }));

    const auto divided_vector = vector / scale;
    // check original vector is unchanged
    REQUIRE(vector.dimensions() == size);
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == val; }));

    // check the division worked correctly
    REQUIRE(divided_vector.dimensions() == size);
    REQUIRE(std::all_of(divided_vector.begin(), divided_vector.end(),
                        [&](auto value) { return value == val / scale; }));
    REQUIRE(divided_vector == +vector);
}

// HANDLE EXCEPTIONS NOW
// divide by 0 case
TEST_CASE("compound_division_different_size") {
    const auto scale = 0;
    auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
    REQUIRE_THROWS_WITH(vector /= scale,
                        "Invalid vector division by 0\n");
    // CHECK NO CHANGES
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
}
