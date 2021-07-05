#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// divison testing is im similair to multiplication however we also check exception of dividing by 0
// 1. empty vector case [] / scale = [] no matter what scale that isn't exaclty 0
// 2. vector with values divided by scale should divide the vector correctly
// 3. division with scale -1 should give the same result as negation, vec / -1 == -vec
// 4. division with scale 1 should give the same result as unary, vec / 1 == +vec

TEST_CASE("basic_division_empty_vectors") {
	auto left_vector = comp6771::euclidean_vector(0);
	const auto scale = 1;
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == 0);
	const auto divided_vector = left_vector / scale;
	// make sure no changes to left vector
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == 0);
	// make sure divided vector has the results we want
	REQUIRE(static_cast<size_t>(divided_vector.dimensions()) == 0);
	REQUIRE(divided_vector == left_vector);
}

TEST_CASE("basic_division_case_different_values") {
	const size_t size = 500;
	const auto value = -500.434;
	const auto scale = -34.9845;
	auto stdvector = std::vector<double>(size);
	std::iota(stdvector.begin(), stdvector.end(), value);
	auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
	const auto casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == stdvector.size());
	REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
	REQUIRE(std::equal(casted_vector.begin(), casted_vector.end(), stdvector.begin(), stdvector.end()));

	const auto divided_vector = vector / scale;
	const auto casted_divided_vector = comp6771_helpers::convert_to_vector_manually(divided_vector);
	// check original vector is unchanged
	REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
	REQUIRE(std::equal(casted_vector.begin(), casted_vector.end(), stdvector.begin(), stdvector.end()));
	// check the division worked correctly
	size_t count = 0;
	REQUIRE(std::all_of(casted_divided_vector.begin(), casted_divided_vector.end(), [&](auto value) {
		return value == Approx(stdvector.at(count++) / scale).template margin(0.000001);
	}));
}

TEST_CASE("division_negation_same") {
	auto scale = -1;
	auto size = 5;
	auto val = 3;
	auto vector = comp6771::euclidean_vector(size, val);
	const auto casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(vector.dimensions() == size);
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));

	const auto divided_vector = vector / scale;
	const auto casted_divided_vector = comp6771_helpers::convert_to_vector_manually(divided_vector);
	// check original vector is unchanged
	REQUIRE(vector.dimensions() == size);
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));

	// check the division worked correctly
	REQUIRE(divided_vector.dimensions() == size);
	REQUIRE(std::all_of(casted_divided_vector.begin(), casted_divided_vector.end(), [&](auto value) {
		return value == Approx(val / scale).margin(0.000001);
	}));
	REQUIRE(divided_vector == -vector);
}

TEST_CASE("division_unary_same") {
	auto scale = 1;
	auto size = 5;
	auto val = 3;
	auto vector = comp6771::euclidean_vector(size, val);
	const auto casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(vector.dimensions() == size);
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));

	const auto divided_vector = vector / scale;
	const auto casted_divided_vector = comp6771_helpers::convert_to_vector_manually(divided_vector);
	// check original vector is unchanged
	REQUIRE(vector.dimensions() == size);
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));

	// check the division worked correctly
	REQUIRE(divided_vector.dimensions() == size);
	REQUIRE(std::all_of(casted_divided_vector.begin(), casted_divided_vector.end(), [&](auto value) {
		return value == Approx(val / scale).margin(0.000001);
	}));
	REQUIRE(divided_vector == +vector);
}

// HANDLE EXCEPTIONS NOW
// divide by 0 case
TEST_CASE("compound_division_different_size") {
	const auto scale = 0;
	auto vector = comp6771::euclidean_vector();
	REQUIRE(vector.dimensions() == 1);
	REQUIRE(vector[0] == Approx(0.0).margin(0.000001));
	REQUIRE_THROWS_WITH(vector /= scale, "Invalid vector division by 0");
	// CHECK NO CHANGES
	REQUIRE(vector.dimensions() == 1);
	REQUIRE(vector[0] == Approx(0).margin(0.000001));
}
