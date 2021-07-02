#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

// const cases
TEST_CASE("at_in_range_correct_value") {
    const auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    auto value = double{vector.at(0)};
    REQUIRE(value == 0);
}

// non const cases (Changing values at indexes)
TEST_CASE("at_change_in_range_default") {
    auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    auto value = vector.at(0);
    REQUIRE(value == 0);
    vector.at(0) = value + 1;
    // make sure rest of vector is the same
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector.at(0) == value + 1);
}

TEST_CASE("at_change_in_range_multiple_values") {
    auto vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(vector.dimensions() == 10);
    bool all_values_same = true;
    for (auto i = 0; i < vector.dimensions(); i++) {
        if (vector.at(i) != i) {
            all_values_same = false;
            break;
        }
    }
    REQUIRE(all_values_same);

    // making sure when we change, the rest stays the same
    auto index_to_change = 5;
    auto value_change = -50;
    vector.at(index_to_change) = value_change;
    REQUIRE(vector.dimensions() == 10);

    for (auto i = 0; i < vector.dimensions(); i++) {
        if (vector.at(index_to_change) == value_change) {
            continue;
        }
        if (vector.at(i) != i) {
            all_values_same = false;
            break;
        }
    }
    REQUIRE(all_values_same);
}

TEST_CASE("at_multiple_change_in_range") {
    auto vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(vector.dimensions() == 10);
    bool all_values_same = true;
    for (auto i = 0; i < vector.dimensions(); i++) {
        if (vector.at(i) != i) {
            all_values_same = false;
            break;
        }
    }
    REQUIRE(all_values_same);

    // doubling all the values in the vector
    for (auto i = 0; i < vector.dimensions(); i++) {
        vector[i] *= 2;
    }

    // now check the vector changes applies to all the indices appleid on
    REQUIRE(vector.dimensions() == 10);
    for (auto i = 0; i < vector.dimensions(); i++) {
        if (vector.at(i) != i * 2) {
            all_values_same = false;
            break;
        }
    }
    REQUIRE(all_values_same);
}

// EXCEPTIONS

// at with negative index for access
TEST_CASE("at_negative_index_access") {
    const auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    auto value = double{vector.at(0)};
    REQUIRE(value == 0);
    REQUIRE_THROWS_WITH(vector.at(-1),
                        "Index" + std::to_string(-1) + " is out of bounds!\n");
}

// at with index out of bounds for access
TEST_CASE("at_out_of_bounds_access") {
    const auto size = 100;
    const auto vector = comp6771::euclidean_vector(size);
    REQUIRE(vector.dimensions() == size);
    bool all_values_same = std::all_of(vector.begin(), vector.end(), [&](auto value) { return value == 0; });
    REQUIRE(all_values_same);
    REQUIRE_THROWS_WITH(vector.at(size),
                        "Index" + std::to_string(size) + " is out of bounds!\n");
}
// at with negative index for change
TEST_CASE("at_negative_index_change") {
    auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    auto value = double{vector.at(0)};
    REQUIRE(value == 0);
    REQUIRE_THROWS_WITH(vector.at(-1) = 3,
                        "Index" + std::to_string(-1) + " is out of bounds!\n");
}
// at with index out of bounds for change
TEST_CASE("at_out_of_bounds_change") {
    const auto size = 100;
    auto vector = comp6771::euclidean_vector(size);
    REQUIRE(vector.dimensions() == size);
    bool all_values_same = std::all_of(vector.begin(), vector.end(), [&](auto value) { return value == 0; });
    REQUIRE(all_values_same);
    REQUIRE_THROWS_WITH(vector.at(size) = 3,
                        "Index" + std::to_string(size) + " is out of bounds!\n");
}