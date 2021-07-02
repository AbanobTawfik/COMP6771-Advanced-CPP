#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

TEST_CASE("unit_vector_size1") {
    const auto vector = comp6771::euclidean_vector(1, 1);
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 1);
    const auto euclidean_norm = comp6771::euclidean_norm(vector);
    // sqrt(1*1) = 1
    REQUIRE(euclidean_norm == 1);
    const auto unit_vector = comp6771::unit(vector);
    REQUIRE(unit_vector.dimensions() == vector.dimensions());
    // now we need to check the unit vector gave us the correct value, since the unit vector is just
    // all values, divided by the euclidean norm, in this case 1, it should return just the same vector
    REQUIRE(unit_vector == vector / 1); // <-- vector = vector/1
}

TEST_CASE("euclidean_vector_alot_of_values") {
    const auto size = 500;
    const auto value = -500.434;
    auto count = 0;
    auto stdvector = std::vector<double>(size);
    // values using iota will be steadily increasing so all different
    std::iota(stdvector.begin(), stdvector.end(), value);
    // creating a euclidean vector with standard vector
    const auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
    REQUIRE(vector.dimensions() == stdvector.size());
    REQUIRE(vector.dimensions() == size);
    bool all_values_same = std::all_of(vector.begin(), vector.end(),
                                       [&](auto value) { return value == stdvector.at(count++); });
    REQUIRE(all_values_same);
    const auto euclidean_norm = comp6771::euclidean_norm(vector);
    REQUIRE(euclidean_norm >= 0);
    double actual_euclidean_norm = 0;
    for (auto value : vector) {
        actual_euclidean_norm += value * value;
    }
    actual_euclidean_norm = std::sqrt(actual_euclidean_norm);
    REQUIRE(euclidean_norm == actual_euclidean_norm);
    const auto unit_vector = comp6771::unit(vector);
    REQUIRE(unit_vector.dimensions() == vector.dimensions());
    // now we need to check the unit vector gave us the correct value, since the unit vector is just
    REQUIRE(unit_vector == vector / euclidean_norm);
}

// Exceptions
TEST_CASE("unit_vector_0_euclidean_norm") {
    // creating 0 vector, dimension 1 aka default vector
    const auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
    // euclidean norm will be 0
    const auto euclidean_norm = comp6771::euclidean_norm(vector);
    // sqrt(0*0) = 0
    REQUIRE(euclidean_norm == 0);

    REQUIRE_THROWS_WITH(comp6771::unit(vector),
                        "euclidean_vector with zero euclidean normal does not have a unit vector\n");
}

// empty unit vector case
TEST_CASE("unit_vector_0_dimensions") {
    // creating 0 vector, dimension 1 aka default vector
    const auto vector = comp6771::euclidean_vector(0);
    REQUIRE(vector.dimensions() == 0);
    // euclidean norm will be 0
    const auto euclidean_norm = comp6771::euclidean_norm(vector);
    // sqrt(0*0) = 0
    REQUIRE(euclidean_norm == 0);
    REQUIRE_THROWS_WITH(comp6771::unit(vector),
                        "euclidean_vector with no dimensions does not have a unit vector\n");
}