#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

TEST_CASE("copy_assignment_const") {
    const auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector.check_cached_norm() == -1);
    REQUIRE(vector[0] == 0);
    const auto copy_vector = vector;
    REQUIRE(copy_vector.dimensions() == 1);
    REQUIRE(copy_vector.check_cached_norm() == -1);
    REQUIRE(vector[0] == 0);
}

TEST_CASE("copy_assignment_non_const") {
    const auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector.check_cached_norm() == -1);
    REQUIRE(vector[0] == 0);
    auto copy_vector = vector;
    REQUIRE(copy_vector.dimensions() == 1);
    REQUIRE(copy_vector.check_cached_norm() == -1);
    REQUIRE(vector[0] == 0);
}

TEST_CASE("copy_assignment_changes") {
    auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector.check_cached_norm() == -1);
    REQUIRE(vector[0] == 0);

    auto copy_vector = vector;
    REQUIRE(copy_vector.dimensions() == 1);
    REQUIRE(copy_vector.check_cached_norm() == -1);
    REQUIRE(copy_vector[0] == 0);

    copy_vector[0] = 1;
    REQUIRE(copy_vector.dimensions() == 1);
    REQUIRE(copy_vector.check_cached_norm() == -1);
    REQUIRE(copy_vector[0] == 1);
    // original stays unchanged!
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector.check_cached_norm() == -1);
    REQUIRE(vector[0] == 0);

}