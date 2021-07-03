#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// for testing multiplication a few things were tested for the sake of completeness
// 1. multiplication on empty vector [] * scale = []
// 2. multiplication on vector with values should multiply each index value by scale correctly
// 3. checking multiplying by 1 is the same as unary
// 3. checking multiplying by -1 is the same as negation

TEST_CASE("basic_compound_multiplication_empty_vectors") {
    auto left_vector = comp6771::euclidean_vector(0);
    auto left_vector_copy = left_vector;
    const auto scale = 0;
    REQUIRE(static_cast<size_t>(left_vector.dimensions()) == 0);
    left_vector *= scale;
    // make sure no changes
    REQUIRE(static_cast<size_t>(left_vector.dimensions()) == 0);
    REQUIRE(left_vector == left_vector_copy);
}

TEST_CASE("basic_compound_multiplication_case_different_values") {
    const size_t size =500;
    const auto value = -500.434;
    const auto scale = -34.9845;
    size_t count = 0;
    auto stdvector = std::vector<double>(size);
    std::iota(stdvector.begin(), stdvector.end(), value);
    auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
    REQUIRE(static_cast<size_t>(vector.dimensions()) == stdvector.size());
    REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
    REQUIRE(std::equal(vector.begin(), vector.end(), stdvector.begin(), stdvector.end()));

    vector *= scale;
    // check the compound_multiplication worked correctly
    count = 0;
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == stdvector.at(count++) * scale; }));
}

TEST_CASE("compound_multiplication_negation_same") {
    auto scale = -1;
    const size_t size =5;
    auto val = 3;
    auto vector = comp6771::euclidean_vector(size, val);
    auto pre_compound_multiplication = comp6771::euclidean_vector(size, val);
    REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == val; }));
    REQUIRE(vector == pre_compound_multiplication);

    vector *= scale;
    REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
    // check the compound_multiplication worked correctly
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == val * scale; }));
    REQUIRE(vector == -pre_compound_multiplication);
}

TEST_CASE("compound_multiplication_unary_same") {
    auto scale = 1;
    const size_t size =5;
    auto val = 3;
    auto vector = comp6771::euclidean_vector(size, val);
    auto pre_compound_multiplication = comp6771::euclidean_vector(size, val);
    REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == val; }));
    REQUIRE(vector == pre_compound_multiplication);

    vector *= scale;
    REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
    // check the compound_multiplication worked correctly
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == val * scale; }));
    REQUIRE(vector == +pre_compound_multiplication);
}