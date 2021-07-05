#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <list>

// these tests will check the 2 cases
// 1. empty euclidean vector -> list, expecting an empty list
// 2. euclidean vector with values -> list with values in the same index corresponding to the
// euclidean vector

TEST_CASE("empty_vector_to_list") {
	const auto vector = comp6771::euclidean_vector(0);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 0);
	const auto casted_list = static_cast<std::list<double>>(vector);
	REQUIRE(casted_list.empty());
}

TEST_CASE("same_values_vector_to_list") {
	const size_t size = 5;
	const auto val = 3;
	const auto vector = comp6771::euclidean_vector(size, val);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
	const auto casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));

	const auto casted_list = static_cast<std::list<double>>(vector);
	REQUIRE(casted_list.size() == size);
	REQUIRE(std::all_of(casted_list.begin(), casted_list.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));
}