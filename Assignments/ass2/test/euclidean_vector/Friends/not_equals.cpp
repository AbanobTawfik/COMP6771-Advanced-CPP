#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>

// this is extremely similair to equals case, however there aren't too many cases to check for unequals in comparison
// we do similair of checking both not equals works for true case and false case using the following tests
// 1. empty vector vs default vector [] != [0] , not equals should return true since not equal
// 2. after creating a vector from another vector and modifying, not equals should return true since no longer equal
// 3. two equal vectors, not equals should return false since equal

TEST_CASE("not_equals_works_correctly_equal_vectors_empty") {
    const auto vector_one = comp6771::euclidean_vector(0);
    const auto vector_two = comp6771::euclidean_vector();
    REQUIRE(vector_one.dimensions() == 0);
    REQUIRE(vector_two.dimensions() == 1);
    REQUIRE(vector_two[0] == 0);
    auto not_equal = (vector_one != vector_two);
    REQUIRE(not_equal);
}


TEST_CASE("not_equals_works_correctly_modifications") {
    auto vector_one = comp6771::euclidean_vector(10, 5);
    const auto vector_two = comp6771::euclidean_vector(vector_one);
    REQUIRE(vector_one.dimensions() == 10);
    REQUIRE(std::all_of(vector_one.begin(), vector_one.end(), [&](auto value) { return value == 5; }));
    REQUIRE(vector_two.dimensions() == 10);
    REQUIRE(std::all_of(vector_two.begin(), vector_two.end(), [&](auto value) { return value == 5; }));
    vector_one[0] *= 2;
    REQUIRE(vector_one[0] == 10);
    REQUIRE(vector_one.dimensions() == 10);
    bool updated_correctly = true;
    for (auto i = 0; i < vector_one.dimensions(); i++) {
        if (i == 0 and vector_one.at(i) == 10) {
            continue;
        }
        if (vector_one.at(i) != 5) {
            updated_correctly = false;
            break;
        }
    }
    REQUIRE(updated_correctly);
    // now since both vectors are not equal shown above due to modifications, since index 0 was modified
    auto not_equal = (vector_one != vector_two);
    REQUIRE(not_equal);
}

TEST_CASE("not_equals_works_correctly_equal_vectors") {
    const auto vector_one = comp6771::euclidean_vector(10, 5);
    const auto vector_two = comp6771::euclidean_vector(10, 5);
    REQUIRE(vector_one.dimensions() == 10);
    REQUIRE(std::all_of(vector_one.begin(), vector_one.end(), [&](auto value) { return value == 5; }));
    REQUIRE(vector_two.dimensions() == 10);
    REQUIRE(std::all_of(vector_two.begin(), vector_two.end(), [&](auto value) { return value == 5; }));
    auto not_equal = (vector_one != vector_two);
    REQUIRE(!not_equal);
}