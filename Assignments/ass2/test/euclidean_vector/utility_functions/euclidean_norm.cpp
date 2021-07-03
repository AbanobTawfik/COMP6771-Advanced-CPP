#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// NOTE IN HERE WE DO NOT TEST CACHING AS IT IS NOT CORE TO EUCLIDEAN NORM IT IS EXTRA, CACHING TESTS ARE IN A DIFFERENT FILE
// here we test a few important behaviour of euclidean norm
// 1. default contructor, [0] -> euclidean norm results in 0
// 2. empty vector, [] -> euclidean norm results in 0
// 3. euclidean vector populated -> euclidean norm is equal to the sum of the squares of each value, all square rooted


TEST_CASE("default_constructor_euclidean_vector") {
    const auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
    const auto euclidean_norm = comp6771::euclidean_norm(vector);
    REQUIRE(euclidean_norm == 0);
}

TEST_CASE("empty_constructor_euclidean_vector") {
    const auto vector = comp6771::euclidean_vector(0);
    REQUIRE(vector.dimensions() == 0);
    const auto euclidean_norm = comp6771::euclidean_norm(vector);
    REQUIRE(euclidean_norm == 0);
}

TEST_CASE("euclidean_vector_with_values") {
    const auto size = 500;
    const auto value = -500.434;
    auto stdvector = std::vector<double>(size);
    std::iota(stdvector.begin(), stdvector.end(), value);
    // creating a euclidean vector with standard vector
    const auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
    REQUIRE(vector.dimensions() == stdvector.size());
    REQUIRE(vector.dimensions() == size);
    REQUIRE(std::equal(vector.begin(), vector.end(), stdvector.begin(), stdvector.end()));
    const auto euclidean_norm = comp6771::euclidean_norm(vector);
    REQUIRE(euclidean_norm >= 0);
    // manual computation of euclidean norm below for comparison
    double actual_euclidean_norm = 0;
    for (auto value : vector) {
        actual_euclidean_norm += value * value;
    }
    actual_euclidean_norm = std::sqrt(actual_euclidean_norm);
    REQUIRE(euclidean_norm == actual_euclidean_norm);
}