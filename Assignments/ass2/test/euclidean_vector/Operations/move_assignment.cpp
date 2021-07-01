#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

TEST_CASE("move_assignment_default") {
    auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);

    const auto copy_vector = std::move(vector);
    REQUIRE(copy_vector.dimensions() == 1);
    REQUIRE(copy_vector[0] == 0);
    // check what we moved from is dealt with correctly
    REQUIRE(vector.dimensions() == 0);
}

TEST_CASE("move_assignment_contains_values") {
    const auto size = 500;
    const auto value = -500.434;
    auto stdvector = std::vector<double>(size);
    // values using iota will be steadily increasing so all different
    std::iota(stdvector.begin(), stdvector.end(), value);

    auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
    REQUIRE(vector.dimensions() == size);
    bool all_values_same = true;
    for (auto i = 0; i < size; i++) {
        if (vector.at(i) != stdvector.at(i)) {
            all_values_same = false;
            break;
        }
    }
    REQUIRE(all_values_same);

    const auto moved_vector = std::move(vector);

    REQUIRE(moved_vector.dimensions() == size);
    all_values_same = true;
    for (auto i = 0; i < size; i++) {
        if (moved_vector.at(i) != stdvector.at(i)) {
            all_values_same = false;
            break;
        }
    }
    REQUIRE(all_values_same);

    // check what we moved from was also removed, i.e length 0
    REQUIRE(vector.dimensions() == 0);
}