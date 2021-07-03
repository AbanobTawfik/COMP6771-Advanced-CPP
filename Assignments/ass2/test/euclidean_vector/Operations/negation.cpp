#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// for negation we have 3 cases we want to check
// 1. empty negated vector should be unmodified [] == -[]
// 2. default vector should be unmodified [0] == -[0]
// 3. default negation behaviour works correctly with values

TEST_CASE("negation_empty_case") {
    auto vector = comp6771::euclidean_vector(0);
    REQUIRE(static_cast<size_t>(vector.dimensions()) == 0);
    vector = -vector;
    REQUIRE(static_cast<size_t>(vector.dimensions()) == 0);
}

TEST_CASE("negation_base_case") {
    auto vector = comp6771::euclidean_vector();
    REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
    REQUIRE(vector[0] == 0);
    vector = -vector;
    REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
    REQUIRE(vector[0] == 0);
}

TEST_CASE("negation_with_values") {
    const size_t size =500;
    const auto value = -500.434;
    auto stdvector = std::vector<double>(size);
    // values using iota will be steadily increasing so all different
    std::iota(stdvector.begin(), stdvector.end(), value);
    auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
    REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
    REQUIRE(std::equal(vector.begin(), vector.end(), stdvector.begin(), stdvector.end()));
    // call in the negation
    vector = -vector;
    size_t count = 0;
    REQUIRE(std::all_of(vector.begin(), vector.end(), [&](auto value) { return value == -1 * stdvector.at(count++); }));
}