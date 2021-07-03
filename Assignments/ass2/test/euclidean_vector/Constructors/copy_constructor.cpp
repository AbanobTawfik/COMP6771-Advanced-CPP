#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <iostream>
#include <vector>

// i wrote 3 tests to check all possible behaviour and expected outcome of using copy constructor
// Test 1 : tests that creating a copy of an empty vector returns a correct empty vector
// Test 2 : just makes sure that when copying a vector, all values are identical to the original vector
// Test 3 : makes sure that when changing a value, the other vector it was copied from is unaffected

TEST_CASE("empty_copy_constructor") {
    const auto empty_constructor = comp6771::euclidean_vector();
    const auto copy_empty_constructor = comp6771::euclidean_vector(empty_constructor);
    REQUIRE(empty_constructor.dimensions() == 1);
    REQUIRE(copy_empty_constructor.dimensions() == 1);
    REQUIRE(empty_constructor[0] == 0);
    REQUIRE(copy_empty_constructor[0] == empty_constructor[0]);
}

TEST_CASE("copy_with_values_no_change") {
    const auto size = 500;
    const auto value = -500.434;
    auto stdvector = std::vector<double>(size);
    // values using iota will be steadily increasing so all different
    std::iota(stdvector.begin(), stdvector.end(), value);
    const auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
    const auto copy_vector = comp6771::euclidean_vector(vector);

    REQUIRE(vector.dimensions() == size);
    REQUIRE(vector.dimensions() == copy_vector.dimensions());
    auto count = 0;
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == stdvector.at(count++); }));
}

TEST_CASE("copy_with_values_change_after") {
    const auto size = 500;
    const auto value = -500.434;
    auto stdvector = std::vector<double>(size);
    // values using iota will be steadily increasing so all different
    std::iota(stdvector.begin(), stdvector.end(), value);
    auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
    auto check_no_changes = comp6771::euclidean_vector(vector);
    auto copy_vector = comp6771::euclidean_vector(vector);
    REQUIRE(vector.dimensions() == size);
    REQUIRE(vector.dimensions() == copy_vector.dimensions());
    auto count = 0;
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == copy_vector.at(count++); }));
    for (auto i = 0; i < size; i++) {
        copy_vector[i]++;
    }
    // first check all values are unchanged on original vector, then check changes occured
    count = 0;
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == check_no_changes.at(count++); }));

    // check changed vector is modified properly, not original values, but incremented by 1 from original
    count = 0;
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value != copy_vector.at(count++); }));
    count = 0;
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == (copy_vector.at(count++) - 1); }));
}