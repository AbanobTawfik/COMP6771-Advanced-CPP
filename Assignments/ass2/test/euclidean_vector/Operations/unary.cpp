#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>

// the only thing we want to check for unary is that it creates a copy of the vector to do this i
// made 2 test cases
// 1. basic case to see if it creates identical copy, to the original vector
// 2. copying vector and then performing changes to see if changes applied to the copy

TEST_CASE("unary_base_case") {
	auto vector = comp6771::euclidean_vector();
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	REQUIRE(vector[0] == Approx(0).margin(0.000001));
	vector = +vector;
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	REQUIRE(vector[0] == Approx(0).margin(0.000001));
}

TEST_CASE("unary_changes") {
	auto vector = comp6771::euclidean_vector();
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	REQUIRE(vector[0] == Approx(0).margin(0.000001));

	vector = +vector;
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	REQUIRE(vector[0] == Approx(0).margin(0.000001));

	// make sure changes give desired results
	vector[0] = 1;
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	REQUIRE(vector[0] == Approx(1).margin(0.000001));
}