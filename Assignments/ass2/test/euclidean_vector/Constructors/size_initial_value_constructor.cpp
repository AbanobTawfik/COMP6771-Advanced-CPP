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
	REQUIRE(std::all_of(vector.begin(), vector.end(), [&](auto value) {
		return value == Approx(4).margin(0.000001);
	}));
}

TEST_CASE("size_constructor_magnitude_explicit") {
	auto dimension = int{3};
	auto magnitude = double{3.24};
	auto vector_object_initialised = comp6771::euclidean_vector(dimension, magnitude);
	REQUIRE(static_cast<size_t>(vector_object_initialised.dimensions()) == 3);
	REQUIRE(std::all_of(vector_object_initialised.begin(),
	                    vector_object_initialised.end(),
	                    [&](auto value) { return value == Approx(magnitude).margin(0.000001); }));
}