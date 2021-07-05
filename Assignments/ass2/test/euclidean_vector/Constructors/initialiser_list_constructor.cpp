#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>

// Only two test case needed, first is with empty initaliser list, we expect the default constructor
// reference: https://edstem.org/courses/5921/discussion/519507?comment=1190795
// other case just checks all values line up in the correct indicies for the list passed in

TEST_CASE("empty_initialiser_list") {
	const auto euclidean_vec = comp6771::euclidean_vector{};
	REQUIRE(static_cast<size_t>(euclidean_vec.dimensions()) == 1);
	REQUIRE(euclidean_vec[0] == Approx(0).margin(0.000001));
	// now we want to check if a default constructed euclidean vector gives the same result
	const auto default_euclidean_vec = comp6771::euclidean_vector();
	REQUIRE(default_euclidean_vec == euclidean_vec);
}

TEST_CASE("normal_initialiser_list_with_different_values") {
	const auto vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 10);
	auto count = 0;
	const auto vector_casted = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(std::all_of(vector_casted.begin(), vector_casted.end(), [&](auto value) {
		return value == Approx(count++).margin(0.000001);
	}));
}