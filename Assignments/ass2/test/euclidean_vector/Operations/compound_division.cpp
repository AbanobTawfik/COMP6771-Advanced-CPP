#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// for testing division a few things were tested for the sake of completeness
// 1. division on empty vector [] / scale = []
// 2. division on vector with values should divide each index value by scale correctly
// 3. checking dividing by 1 is the same as unary
// 3. checking dividing by -1 is the same as negation
// 4. checking dividing by 0 throws the correct exception alongside leaving the original vector
// unmodified

TEST_CASE("basic_compound_division_empty_vectors") {
	auto left_vector = comp6771::euclidean_vector(0);
	auto left_vector_copy = left_vector;
	const auto scale = 1.34;
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == 0);
	left_vector /= scale;
	// make sure no changes
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == 0);
	REQUIRE(left_vector == left_vector_copy);
}

TEST_CASE("basic_compound_division_case_different_values") {
	const size_t size = 500;
	const auto value = -500.434;
	const auto scale = -34.9849;
	auto stdvector = std::vector<double>(size);
	std::iota(stdvector.begin(), stdvector.end(), value);
	auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
	auto casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == stdvector.size());
	REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
	REQUIRE(std::equal(casted_vector.begin(), casted_vector.end(), stdvector.begin(), stdvector.end()));
	vector /= scale;
	casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	// check the compound_division worked correctly
	size_t count = 0;
	// for this example since conversions are precise and there is arithmetic rounding errors,
	// dividing by 34.9845 and values are 3 decimal places too, this checks values are atleast within
	// 4 decimal places
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto val) {
		return val == Approx(stdvector.at(count++) / scale).margin(0.000001);
	}));
}

TEST_CASE("compound_division_negation_same") {
	auto scale = -1;
	const size_t size = 5;
	auto val = 3;
	auto vector = comp6771::euclidean_vector(size, val);
	auto pre_compound_division = comp6771::euclidean_vector(size, val);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
	auto casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));
	REQUIRE(vector == pre_compound_division);

	vector /= scale;
	casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
	// check the compound_division worked correctly
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto value) {
		return value == Approx(val / scale).margin(0.000001);
	}));
	REQUIRE(vector == -pre_compound_division);
}

TEST_CASE("compound_division_unary_same") {
	auto scale = 1;
	const size_t size = 5;
	auto val = 3;
	auto vector = comp6771::euclidean_vector(size, val);
	auto pre_compound_division = comp6771::euclidean_vector(size, val);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
	auto casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));
	REQUIRE(vector == pre_compound_division);

	vector /= scale;
	casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
	// check the compound_division worked correctly
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto value) {
		return value == Approx(val / scale).margin(0.000001);
	}));
	REQUIRE(vector == +pre_compound_division);
}

// HANDLE EXCEPTIONS NOW
TEST_CASE("compound_division_scale_0") {
	const auto scale = 0;
	auto vector = comp6771::euclidean_vector();
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	REQUIRE(vector[0] == Approx(0).margin(0.000001));
	REQUIRE_THROWS_WITH(vector /= scale, "Invalid vector division by 0");
	// NO CHANGES!
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	REQUIRE(vector[0] == Approx(0).margin(0.000001));
}
