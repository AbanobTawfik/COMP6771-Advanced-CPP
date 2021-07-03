#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// multiplication testing is alot simpler since there are no exceptions however, we do also test unity and negation
// 1. empty vector case [] * scale = [] no matter what scale
// 2. vector with values multipleid by scale should multiply the vector correctly
// 3. multiplication with scale -1 should give the same result as negation, vec * -1 == -vec
// 4. multiplication with scale 1 should give the same result as unary, vec * 1 == +vec

TEST_CASE("basic_multiplication_empty_vectors") {
    auto vector = comp6771::euclidean_vector(0);
    const auto scale = 0;
    REQUIRE(static_cast<size_t>(vector.dimensions()) == 0);
    const auto multiplied_vector = vector * scale;
    // make sure no changes to left vector
    REQUIRE(static_cast<size_t>(vector.dimensions()) == 0);
    // make sure multiplied vector has the results we want
    REQUIRE(static_cast<size_t>(multiplied_vector.dimensions()) == 0);
    REQUIRE(multiplied_vector == vector);
}

TEST_CASE("basic_multiplication_case_different_values") {
    const size_t size =500;
    const auto value = -500.434;
    const auto scale = -34.9845;
    auto stdvector = std::vector<double>(size);
    std::iota(stdvector.begin(), stdvector.end(), value);
    auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
    REQUIRE(static_cast<size_t>(vector.dimensions()) == stdvector.size());
    REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
    REQUIRE(std::equal(vector.begin(), vector.end(), stdvector.begin(), stdvector.end()));

    const auto multiplied_vector = vector * scale;
    // check original vector is unchanged
    REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
    REQUIRE(std::equal(vector.begin(), vector.end(), stdvector.begin(), stdvector.end()));
    // check the multiplication worked correctly
    size_t count = 0;
    REQUIRE(std::all_of(multiplied_vector.begin(), multiplied_vector.end(),
                        [&](auto value) { return value == stdvector.at(count++) * scale; }));
}

TEST_CASE("multiplication_negation_same") {
    auto scale = -1;
    auto size = 5;
    auto val = 3;
    auto vector = comp6771::euclidean_vector(size, val);
    REQUIRE(vector.dimensions() == size);
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == val; }));

    const auto multiplied_vector = vector * scale;
    // check original vector is unchanged
    REQUIRE(vector.dimensions() == size);
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == val; }));

    // check the multiplication worked correctly
    REQUIRE(multiplied_vector.dimensions() == size);
    REQUIRE(std::all_of(multiplied_vector.begin(), multiplied_vector.end(),
                        [&](auto value) { return value == val * scale; }));
    REQUIRE(multiplied_vector == -vector);
}

TEST_CASE("multiplication_unary_same") {
    auto scale = 1;
    auto size = 5;
    auto val = 3;
    auto vector = comp6771::euclidean_vector(size, val);
    REQUIRE(vector.dimensions() == size);
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == val; }));

    const auto multiplied_vector = vector * scale;
    // check original vector is unchanged
    REQUIRE(vector.dimensions() == size);
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == val; }));

    // check the multiplication worked correctly
    REQUIRE(multiplied_vector.dimensions() == size);
    REQUIRE(std::all_of(multiplied_vector.begin(), multiplied_vector.end(),
                        [&](auto value) { return value == val * scale; }));
    REQUIRE(multiplied_vector == +vector);
}