#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// there were 3 cases handled for compound addition
// 1. empty vectors, making sure [] + [] = []
// 2. vectors containing values, making sure operation works exactly as expected
// 3. vector being compoundedly added has a different size, expect an exception only leaving vectors
// unchanged

TEST_CASE("basic_compound_addition_empty_vectors") {
	auto left_vector = comp6771::euclidean_vector(0);
	auto right_vector = comp6771::euclidean_vector(0);
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == 0);
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == 0);

	left_vector += right_vector;
	// make sure dimensions dont change, nothing should happen, [] + [] = []
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == 0);
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == 0);
}

TEST_CASE("basic_compound_addition_case_different_values") {
	const size_t size = 500;
	const auto value = -500.434;
	auto left_stdvector = std::vector<double>(size);
	std::iota(left_stdvector.begin(), left_stdvector.end(), value);
	auto left_vector = comp6771::euclidean_vector(left_stdvector.begin(), left_stdvector.end());
	auto casted_left_vector = comp6771_helpers::convert_to_vector_manually(left_vector);
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == left_stdvector.size());
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == size);
	REQUIRE(std::equal(casted_left_vector.begin(),
	                   casted_left_vector.end(),
	                   left_stdvector.begin(),
	                   left_stdvector.end()));
	const auto value2 = 6342;
	auto right_stdvector = std::vector<double>(size);
	std::iota(right_stdvector.begin(), right_stdvector.end(), value2);
	auto right_vector = comp6771::euclidean_vector(right_stdvector.begin(), right_stdvector.end());
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == right_stdvector.size());
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == size);
	const auto casted_right_vector = comp6771_helpers::convert_to_vector_manually(right_vector);
	REQUIRE(std::equal(casted_right_vector.begin(),
	                   casted_right_vector.end(),
	                   right_stdvector.begin(),
	                   right_stdvector.end()));
	// keep in mind our original 2 std vectors stay the same, so we will compare the values in them
	// to the result below
	left_vector += right_vector;
	casted_left_vector = comp6771_helpers::convert_to_vector_manually(left_vector);
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == size);
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == size);
	// make sure right vector doesn't change
	REQUIRE(std::equal(casted_right_vector.begin(),
	                   casted_right_vector.end(),
	                   right_stdvector.begin(),
	                   right_stdvector.end()));
	size_t count = 0;
	size_t count2 = 0;
	REQUIRE(std::all_of(casted_left_vector.begin(), casted_left_vector.end(), [&](auto value) {
		return value
		       == Approx(left_stdvector.at(count++) + right_stdvector.at(count2++)).margin(0.000001);
	}));
}

// HANDLE EXCEPTIONS NOW
TEST_CASE("compound_addition_different_size") {
	const auto size1 = 3;
	const auto size2 = 5;
	REQUIRE(size1 != size2);
	const auto val = 3;
	auto left_vector = comp6771::euclidean_vector(size1, val);
	auto right_vector = comp6771::euclidean_vector(size2, val);
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == size1);
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == size2);
	const auto casted_left_vector = comp6771_helpers::convert_to_vector_manually(left_vector);
	const auto casted_right_vector = comp6771_helpers::convert_to_vector_manually(right_vector);
	REQUIRE(std::all_of(casted_left_vector.begin(), casted_left_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));
	REQUIRE(std::all_of(casted_right_vector.begin(), casted_right_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));
	REQUIRE_THROWS_WITH(left_vector += right_vector,
	                    "Dimensions of LHS(" + std::to_string(size1) + ") and RHS ("
	                       + std::to_string(size2) + ") do not match");
	// NO CHANGES!
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == size1);
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == size2);
	REQUIRE(std::all_of(casted_left_vector.begin(), casted_left_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));
	REQUIRE(std::all_of(casted_right_vector.begin(), casted_right_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));
}