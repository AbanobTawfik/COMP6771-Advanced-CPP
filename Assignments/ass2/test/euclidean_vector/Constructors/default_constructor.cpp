#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

TEST_CASE("default_constructor") {
    const auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
}