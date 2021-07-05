#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>

// the only cases handled for this constructor is using integer object or using a implicit integer
// (seen in spec) and the final case is for the empty constructor (size = 0), we want to return []

TEST_CASE("size_constructor_implicit") {
	const auto vector = comp6771::euclidean_vector(10);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 10);
	// check all values defaulting to 0
	const auto casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto value) {
		return value == Approx(0).margin(0.000001);
	}));
}

TEST_CASE("size_constructor_explicit") {
	auto dimension = int{3};
	auto vector_object_initialised = comp6771::euclidean_vector(dimension);
	REQUIRE(static_cast<size_t>(vector_object_initialised.dimensions()) == 3);
	const auto casted_vector_object_initialised =
	   comp6771_helpers::convert_to_vector_manually(vector_object_initialised);
	REQUIRE(std::all_of(casted_vector_object_initialised.begin(),
	                    casted_vector_object_initialised.end(),
	                    [&](auto value) { return value == Approx(0).margin(0.000001); }));
}

TEST_CASE("size_constructor_empty") {
	const auto vector = comp6771::euclidean_vector(0);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 0);
}
