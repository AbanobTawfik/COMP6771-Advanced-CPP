#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

TEST_CASE("negation_empty_case") {
    auto vector = comp6771::euclidean_vector(0);
    REQUIRE(vector.dimensions() == 0);
    vector = -vector;
    REQUIRE(vector.dimensions() == 0);
}

TEST_CASE("negation_base_case") {
    auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
    vector = -vector;
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
}

TEST_CASE("negation_with_values") {
    const auto size = 500;
    const auto value = -500.434;
    auto stdvector = std::vector<double>(size);
    // values using iota will be steadily increasing so all different
    std::iota(stdvector.begin(), stdvector.end(), value);
    auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
    REQUIRE(vector.dimensions() == stdvector.size());
    REQUIRE(vector.dimensions() == size);
    bool all_values_same = true;
    for (auto i = 0; i < size; i++) {
        if (vector.at(i) != stdvector.at(i)) {
            all_values_same = false;
            break;
        }
    }
    REQUIRE(all_values_same);

    // call in the negation
    vector = -vector;
    bool all_negatives_now = true;
    for (auto i = 0; i < size; i++) {
        if (vector.at(i) != stdvector.at(i)*-1) {
            all_negatives_now = false;
            break;
        }
    }
    REQUIRE(all_negatives_now);
}


TEST_CASE("negation_changes") {
    auto vector = comp6771::euclidean_vector(1,1);
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 1);

    vector = -vector;
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == -1);

    // make sure changes give desired results
    vector[0] = 1;
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 1);
}