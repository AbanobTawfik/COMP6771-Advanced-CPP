#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

TEST_CASE("unary_base_case") {
    auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
    vector = +vector;
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
}

TEST_CASE("unary_changes") {
    auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);

    vector = +vector;
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);

    // make sure changes give desired results
    vector[0] = 1;
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 1);

}