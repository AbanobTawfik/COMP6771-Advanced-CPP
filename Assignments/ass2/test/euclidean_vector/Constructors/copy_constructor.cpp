#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

// when we copy constructor, we want the created vector to be detatched from the original vector, this means
// changes to the copied vector do not carry through the original, however they start off the same!

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
    REQUIRE(vector.check_cached_norm() == -1);
    REQUIRE(copy_vector.check_cached_norm() == -1);
    bool all_values_same = true;
    for (auto i = 0; i < size; i++) {
        if (vector.at(i) != copy_vector.at(i)) {
            all_values_same = false;
            break;
        }
    }
    REQUIRE(all_values_same);
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
    REQUIRE(vector.check_cached_norm() == -1);
    REQUIRE(copy_vector.check_cached_norm() == -1);
    bool all_values_same = true;
    for (auto i = 0; i < size; i++) {
        if (vector.at(i) != copy_vector.at(i)) {
            all_values_same = false;
            break;
        }
    }
    REQUIRE(all_values_same);
    for (auto i = 0; i < size; i++) {
        copy_vector[i]++;
    }
    // first check all values are unchanged on original vector, then check changes occured
    for (auto i = 0; i < size; i++) {
        if (vector.at(i) != check_no_changes.at(i)) {
            all_values_same = false;
            break;
        }
    }
    REQUIRE(all_values_same);
    bool all_values_different = true;
    bool all_values_modified_by_1 = true;
    for (auto i = 0; i < size; i++) {
        if (vector.at(i) == copy_vector.at(i)) {
            all_values_different = false;
            break;
        }
        if (vector.at(i) != copy_vector.at(i) - 1) {
            all_values_modified_by_1 = false;
            break;
        }
    }
    REQUIRE(all_values_different);
    REQUIRE(all_values_modified_by_1);
}