#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

// when we copy constructor, we want the created vector to be detatched from the original vector, this means
// changes to the copied vector do not carry through the original, however they start off the same!

TEST_CASE("empty_move_constructor") {
    auto empty_constructor = comp6771::euclidean_vector();
    const auto move_empty_constructor = comp6771::euclidean_vector(std::move(empty_constructor));
    // we want to make sure that our new vector is the same as the one that moved into it (Default constructor)
    REQUIRE(move_empty_constructor.dimensions() == 1);
    REQUIRE(move_empty_constructor[0] == 0);
    // check what we moved from was also removed, i.e length 0
    REQUIRE(empty_constructor.dimensions() == 0);
    REQUIRE(empty_constructor.check_cached_norm() == -1);
}

TEST_CASE("contains_values_move_constructor") {
    const auto size = 500;
    const auto value = -500.434;
    auto stdvector = std::vector<double>(size);
    // values using iota will be steadily increasing so all different
    std::iota(stdvector.begin(), stdvector.end(), value);

    auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
    REQUIRE(vector.dimensions() == size);
    REQUIRE(vector.check_cached_norm() == -1);
    bool all_values_same = true;
    for (auto i = 0; i < size; i++) {
        if (vector.at(i) != stdvector.at(i)) {
            all_values_same = false;
            break;
        }
    }
    REQUIRE(all_values_same);

    const auto moved_vector = comp6771::euclidean_vector(std::move(vector));

    REQUIRE(moved_vector.dimensions() == size);
    REQUIRE(moved_vector.check_cached_norm() == -1);
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
    REQUIRE(vector.check_cached_norm() == -1);
}

