#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

// since we can assume the integer passed into single arguement constructor can always be assumed to be non-negative
// we don't have any other edge cases

TEST_CASE("empty_initialiser_list") {
    const auto euclidean_vec = comp6771::euclidean_vector{};
    REQUIRE(euclidean_vec.dimensions() == 1);
    REQUIRE(euclidean_vec[0] == 0);
    // now we want to check if a default constructed euclidean vector gives the same result
    const auto default_euclidean_vec = comp6771::euclidean_vector();
    REQUIRE(default_euclidean_vec == euclidean_vec);
}

TEST_CASE("normal_initialiser_list_with_different_values") {

    const auto vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(vector.dimensions() == 10);
    bool all_values_same = true;
    for (auto i = 0; i < vector.dimensions(); i++) {
        if (vector.at(i) != i) {
            all_values_same = false;
            break;
        }
    }
    REQUIRE(all_values_same);
}