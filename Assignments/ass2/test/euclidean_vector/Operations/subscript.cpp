#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

// const cases
TEST_CASE("subscript_in_range_correct_value") {
    const auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector.check_cached_norm() == -1);
    auto value = double{vector[0]};
    REQUIRE(value == 0);
}

// non const cases (Changing values at indexes)
TEST_CASE("subscript_change_in_range_default") {
    auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector.check_cached_norm() == -1);
    auto value = vector[0];
    REQUIRE(value == 0);
    vector[0] = value + 1;
    // make sure rest of vector is the same
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector.check_cached_norm() == -1);
    REQUIRE(vector[0] == value + 1);
}

TEST_CASE("subscript_change_in_range_multiple_values") {
    auto vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(vector.dimensions() == 10);
    REQUIRE(vector.check_cached_norm() == -1);
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
    vector[index_to_change] = value_change;
    REQUIRE(vector.dimensions() == 10);
    REQUIRE(vector.check_cached_norm() == -1);

    for(auto i = 0; i < vector.dimensions(); i++){
        if(vector[index_to_change] == value_change){
            continue;
        }
        if (vector.at(i) != i) {
            all_values_same = false;
            break;
        }
    }
    REQUIRE(all_values_same);
}

TEST_CASE("subscript_multiple_change_in_range") {
    auto vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(vector.dimensions() == 10);
    REQUIRE(vector.check_cached_norm() == -1);
    bool all_values_same = true;
    for (auto i = 0; i < vector.dimensions(); i++) {
        if (vector.at(i) != i) {
            all_values_same = false;
            break;
        }
    }
    REQUIRE(all_values_same);

    // doubling all the values in the vector
    for(auto i = 0; i < vector.dimensions(); i++){
        vector[i] *=2;
    }

    // now check the vector changes applies to all the indices appleid on
    REQUIRE(vector.dimensions() == 10);
    REQUIRE(vector.check_cached_norm() == -1);
    for(auto i = 0; i < vector.dimensions(); i++){
        if (vector.at(i) != i*2) {
            all_values_same = false;
            break;
        }
    }
    REQUIRE(all_values_same);
}