#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>

// Simplest test case, makes sure that when calling the default constructor we get a euclidean
// vector like [0]

TEST_CASE("default_constructor") {
	const auto vector = comp6771::euclidean_vector();
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	REQUIRE(vector[0] == Approx(0).margin(0.000001));
}