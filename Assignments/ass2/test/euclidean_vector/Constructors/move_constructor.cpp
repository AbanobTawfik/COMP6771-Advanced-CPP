#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// when testing move we want to make sure that the original vector moved from is correctly dealt with
// this means setting the dimensions to 0 (i.e. clearing it ready for deletion)
// the other case handled is just on the default constructor

TEST_CASE("default_move_constructor") {
    auto empty_constructor = comp6771::euclidean_vector();
    const auto move_empty_constructor = comp6771::euclidean_vector(std::move(empty_constructor));
    // we want to make sure that our new vector is the same as the one that moved into it (Default constructor)
    REQUIRE(move_empty_constructor.dimensions() == 1);
    REQUIRE(move_empty_constructor[0] == 0);
    // check what we moved from was also removed, i.e length 0
    REQUIRE(empty_constructor.dimensions() == 0);
}

TEST_CASE("contains_values_move_constructor") {
    const auto size = 500;
    const auto value = -500.434;
    auto stdvector = std::vector<double>(size);
    // values using iota will be steadily increasing so all different
    std::iota(stdvector.begin(), stdvector.end(), value);

    auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
    REQUIRE(vector.dimensions() == size);
    auto count = 0;
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == stdvector.at(count++); }));
    const auto moved_vector = comp6771::euclidean_vector(std::move(vector));
    REQUIRE(moved_vector.dimensions() == size);
    count = 0;
    REQUIRE(std::all_of(moved_vector.begin(), moved_vector.end(),
                        [&](auto value) { return value == stdvector.at(count++); }));
    // check what we moved from was also removed, i.e length 0
    REQUIRE(vector.dimensions() == 0);
}

