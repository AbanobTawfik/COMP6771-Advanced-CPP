#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// 2 cases were tested for completeness
// 1. move assignment with empty vector
// 2. move assignment where there are values
// making sure that the original euclidean we are moving from is properly dealt with, size 0, and
// content is ready for destruction

TEST_CASE("move_assignment_default") {
	auto vector = comp6771::euclidean_vector(0);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 0);

	const auto copy_vector = std::move(vector);
	REQUIRE(static_cast<size_t>(copy_vector.dimensions()) == 0);
	// check what we moved from is dealt with correctly
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 0);
}

TEST_CASE("move_assignment_contains_values") {
	const size_t size = 500;
	const auto value = -500.434;
	auto stdvector = std::vector<double>(size);
	std::iota(stdvector.begin(), stdvector.end(), value);
	auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
	const auto casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(std::equal(casted_vector.begin(), casted_vector.end(), stdvector.begin(), stdvector.end()));
	const auto moved_vector = std::move(vector);
	const auto casted_moved_vector = comp6771_helpers::convert_to_vector_manually(moved_vector);
	REQUIRE(std::equal(casted_moved_vector.begin(),
	                   casted_moved_vector.end(),
	                   stdvector.begin(),
	                   stdvector.end()));
	// check what we moved from was also removed, i.e length 0
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 0);
}