#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>

// three different cases were made to test the copy assignment behaves correctly
// 1. able to copy a const euclidean vector -> const euclidean vector
// 2. able to copy a const euclidean vector -> non const euclidean vector
// 3. checking changes to the copy doesn't effect the euclidean vector it was copied from

TEST_CASE("copy_assignment_const") {
    const auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
    const auto copy_vector = vector;
    REQUIRE(copy_vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
}

TEST_CASE("copy_assignment_non_const") {
    const auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
    auto copy_vector = vector;
    REQUIRE(copy_vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
}

TEST_CASE("copy_assignment_changes") {
    auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);

    auto copy_vector = vector;
    REQUIRE(copy_vector.dimensions() == 1);
    REQUIRE(copy_vector[0] == 0);

    copy_vector[0] = 1;
    // check changes went through
    REQUIRE(copy_vector.dimensions() == 1);
    REQUIRE(copy_vector[0] == 1);
    // original stays unchanged!
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);

}