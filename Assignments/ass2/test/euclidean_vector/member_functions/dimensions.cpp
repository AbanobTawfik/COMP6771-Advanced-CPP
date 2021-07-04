#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>

// only had to test 3 simple test cases for dimensions
// 1. empty vector -> dimensions = 0
// 2. default vector -> dimensions = 1
// 3. all other cases, dimensions = size of how it was initialised

// const cases
TEST_CASE("empty_vector_dimension") {
	const auto vector = comp6771::euclidean_vector(0);
	const auto vector_size = vector.dimensions();
	REQUIRE(vector_size == 0);
}

TEST_CASE("default_vector_dimension") {
	const auto vector = comp6771::euclidean_vector();
	const auto vector_size = vector.dimensions();
	REQUIRE(vector_size == 1);
}

TEST_CASE("multiple_element_dimension") {
	const auto vector = comp6771::euclidean_vector(368);
	const auto vector_size = vector.dimensions();
	REQUIRE(vector_size == 368);
}