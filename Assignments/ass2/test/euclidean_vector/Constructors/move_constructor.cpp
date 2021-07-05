#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// when testing move we want to make sure that the original vector moved from is correctly dealt
// with this means setting the dimensions to 0 (i.e. clearing it ready for deletion) the other case
// handled is just on the default constructor

TEST_CASE("default_move_constructor") {
	auto empty_constructor = comp6771::euclidean_vector();
	const auto move_empty_constructor = comp6771::euclidean_vector(std::move(empty_constructor));
	// we want to make sure that our new vector is the same as the one that moved into it (Default
	// constructor)
	REQUIRE(static_cast<size_t>(move_empty_constructor.dimensions()) == 1);
	REQUIRE(move_empty_constructor[0] == Approx(0).margin(0.000001));
	// check what we moved from was also removed, i.e length 0
	REQUIRE(static_cast<size_t>(empty_constructor.dimensions()) == 0);
}

TEST_CASE("contains_values_move_constructor") {
	const size_t size = 500;
	const auto value = -500.434;
	auto stdvector = std::vector<double>(size);
	// values using iota will be steadily increasing so all different
	std::iota(stdvector.begin(), stdvector.end(), value);

	auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
	REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
	const auto casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(std::equal(casted_vector.begin(), casted_vector.end(), stdvector.begin(), stdvector.end()));
	const auto moved_vector = comp6771::euclidean_vector(std::move(vector));
	const auto moved_vector_casted = comp6771_helpers::convert_to_vector_manually(moved_vector);
	REQUIRE(static_cast<size_t>(moved_vector.dimensions()) == size);
	REQUIRE(std::equal(moved_vector_casted.begin(),
	                   moved_vector_casted.end(),
	                   stdvector.begin(),
	                   stdvector.end()));
	// check what we moved from was also removed, i.e length 0
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 0);
}
