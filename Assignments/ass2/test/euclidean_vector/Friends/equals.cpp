#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

// when we copy constructor, we want the created vector to be detatched from the original vector, this means
// changes to the copied vector do not carry through the original, however they start off the same!

TEST_CASE("equals_works_correctly_equal_vectors_empty") {
    const auto vector_one = comp6771::euclidean_vector(0);
    const auto vector_two = comp6771::euclidean_vector(0);
    REQUIRE(vector_one.dimensions() == 0);
    REQUIRE(vector_two.dimensions() == 0);
    auto equal = (vector_one == vector_two);
    REQUIRE(equal);
}

TEST_CASE("equals_works_correctly_equal_vectors_empty2") {
    const auto vector_one = comp6771::euclidean_vector(0);
    const auto empty_vector = std::vector<double>();
    const auto vector_two = comp6771::euclidean_vector(empty_vector.begin(), empty_vector.end());
    REQUIRE(vector_one.dimensions() == 0);
    REQUIRE(vector_two.dimensions() == 0);
    auto equal = (vector_one == vector_two);
    REQUIRE(equal);
}

TEST_CASE("equals_works_correctly_equal_vectors_default_constructor") {
    const auto vector_one = comp6771::euclidean_vector();
    const auto vector_two = comp6771::euclidean_vector();
    REQUIRE(vector_one.dimensions() == 1);
    REQUIRE(vector_one[0] == 0);
    REQUIRE(vector_two.dimensions() == 1);
    REQUIRE(vector_two[0] == 0);
    auto equal = (vector_one == vector_two);
    REQUIRE(equal);
}

TEST_CASE("equals_works_correctly_equal_vectors") {
    const auto vector_one = comp6771::euclidean_vector(10, 5);
    const auto vector_two = comp6771::euclidean_vector(10, 5);
    // check vectors are equal first by checking properties of internals
    REQUIRE(vector_one.dimensions() == 10);
    REQUIRE(std::all_of(vector_one.begin(), vector_one.end(), [&](auto value) { return value == 5; }));
    REQUIRE(vector_two.dimensions() == 10);
    REQUIRE(std::all_of(vector_two.begin(), vector_two.end(), [&](auto value) { return value == 5; }));
    // check if the equals now does the same thing
    auto equal = (vector_one == vector_two);
    REQUIRE(equal);
}

TEST_CASE("equals_works_correctly_equal_vectors_assigned1") {
    const auto vector_one = comp6771::euclidean_vector(10, 5);
    const auto vector_two = comp6771::euclidean_vector(vector_one);
    REQUIRE(vector_one.dimensions() == 10);
    REQUIRE(std::all_of(vector_one.begin(), vector_one.end(), [&](auto value) { return value == 5; }));
    REQUIRE(vector_two.dimensions() == 10);
    REQUIRE(std::all_of(vector_two.begin(), vector_two.end(), [&](auto value) { return value == 5; }));
    auto equal = (vector_one == vector_two);
    REQUIRE(equal);
}

TEST_CASE("equals_works_correctly_equal_vectors_assigned2") {
    const auto vector_one = comp6771::euclidean_vector(10, 5);
    const auto vector_two = vector_one;
    REQUIRE(vector_one.dimensions() == 10);
    REQUIRE(std::all_of(vector_one.begin(), vector_one.end(), [&](auto value) { return value == 5; }));
    REQUIRE(vector_two.dimensions() == 10);
    REQUIRE(std::all_of(vector_two.begin(), vector_two.end(), [&](auto value) { return value == 5; }));
    auto equal = (vector_one == vector_two);
    REQUIRE(equal);
}

TEST_CASE("equals_works_correctly_unequal_vectors") {
    const auto vector_one = comp6771::euclidean_vector(10, 5);
    const auto vector_two = comp6771::euclidean_vector(15, 5);
    REQUIRE(vector_one.dimensions() == 10);
    REQUIRE(std::all_of(vector_one.begin(), vector_one.end(), [&](auto value) { return value == 5; }));
    REQUIRE(vector_two.dimensions() == 15);
    REQUIRE(std::all_of(vector_two.begin(), vector_two.end(), [&](auto value) { return value == 5; }));
    auto equal = (vector_one == vector_two);
    REQUIRE(!equal);
}