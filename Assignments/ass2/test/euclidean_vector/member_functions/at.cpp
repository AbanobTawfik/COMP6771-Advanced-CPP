#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>

// at and subscript are almost identical especially in testing, however it only differs in handling
// edge cases, so we will perform the following
// 1. all subscript checks
// 2. negative index
// 3. index greater than size of vector - 1

TEST_CASE("at_in_range_correct_value") {
	const auto vector = comp6771::euclidean_vector();
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	auto value = double{vector.at(0)};
	REQUIRE(value == Approx(0).margin(0.000001));
}

// non const cases (Changing values at indexes)
TEST_CASE("at_change_in_range_default") {
	auto vector = comp6771::euclidean_vector();
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	auto value = vector.at(0);
	REQUIRE(value == Approx(0).margin(0.000001));
	vector.at(0) = value + 1;
	// make sure rest of vector is the same
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	REQUIRE(vector.at(0) == Approx(value + 1).margin(0.000001));
}

// EXCEPTIONS

// at with negative index for access
TEST_CASE("at_negative_index_access") {
	const auto vector = comp6771::euclidean_vector();
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	auto value = double{vector.at(0)};
	REQUIRE(value == Approx(0).margin(0.000001));
	REQUIRE_THROWS_WITH(vector.at(-1), "Index " + std::to_string(-1) + " is out of bounds!");
	// MAKE SURE NO CHANGES
	value = double{vector.at(0)};
	REQUIRE(value == Approx(0).margin(0.000001));
}

// at with index out of bounds for access
TEST_CASE("at_out_of_bounds_access") {
	const size_t size = 100;
	const auto vector = comp6771::euclidean_vector(size);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
	const auto casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto value) {
		return value == Approx(0).margin(0.000001);
	}));
	REQUIRE_THROWS_WITH(vector.at(size), "Index " + std::to_string(size) + " is out of bounds!");
	// MAKE SURE NO CHANGES
	REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto value) {
		return value == Approx(0).margin(0.000001);
	}));
}
// at with negative index for change
TEST_CASE("at_negative_index_change") {
	auto vector = comp6771::euclidean_vector();
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	auto value = double{vector.at(0)};
	REQUIRE(value == Approx(0).margin(0.000001));
	REQUIRE_THROWS_WITH(vector.at(-1) = 3, "Index " + std::to_string(-1) + " is out of bounds!");
	// make sure no changes
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	value = double{vector.at(0)};
	REQUIRE(value == Approx(0).margin(0.000001));
}
// at with index out of bounds for change
TEST_CASE("at_out_of_bounds_change") {
	const size_t size = 100;
	auto vector = comp6771::euclidean_vector(size);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
	const auto casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto value) {
		return value == Approx(0).margin(0.000001);
	}));
	REQUIRE_THROWS_WITH(vector.at(size) = 3, "Index " + std::to_string(size) + " is out of bounds!");
	// make sure no changes
	REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto value) {
		return value == Approx(0).margin(0.000001);
	}));
}