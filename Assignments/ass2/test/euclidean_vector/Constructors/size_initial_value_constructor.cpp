#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>

// similar case to size constructor, testing the empty case, and using explicit and implicit values
// as seen in spec

TEST_CASE("size_constructor_magnitude_empty") {
	const auto vector = comp6771::euclidean_vector(0, 4);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 0);
}

TEST_CASE("size_constructor_magnitude_implicit") {
	const auto vector = comp6771::euclidean_vector(10, 4);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 10);
	// check all values defaulting to initial value of 4
	const auto casted_vector = static_cast<std::vector<double>>(vector);
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto value) {
		return value == Approx(4).margin(0.000001);
	}));
}

TEST_CASE("size_constructor_magnitude_explicit") {
	auto dimension = int{3};
	auto magnitude = double{3.24};
	auto vector_object_initialised = comp6771::euclidean_vector(dimension, magnitude);
	REQUIRE(static_cast<size_t>(vector_object_initialised.dimensions()) == 3);
	const auto casted_vector_object_initialised =
	   comp6771_helpers::convert_to_vector_manually(vector_object_initialised);

	REQUIRE(std::all_of(casted_vector_object_initialised.begin(),
	                    casted_vector_object_initialised.end(),
	                    [&](auto value) { return value == Approx(magnitude).margin(0.000001); }));
}