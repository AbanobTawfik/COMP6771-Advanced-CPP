#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// NOTE IN HERE WE DO NOT TEST CACHING AS IT IS NOT CORE TO EUCLIDEAN NORM IT IS EXTRA, CACHING
// TESTS ARE IN A DIFFERENT FILE here we test a few important behaviour of euclidean norm
// 1. default contructor, [0] -> euclidean norm results in 0
// 2. empty vector, [] -> euclidean norm results in 0
// 3. euclidean vector populated -> euclidean norm is equal to the sum of the squares of each value,
// all square rooted

TEST_CASE("default_constructor_euclidean_vector") {
	const auto vector = comp6771::euclidean_vector();
	REQUIRE(static_cast<size_t>(static_cast<size_t>(vector.dimensions())) == 1);
	REQUIRE(vector[0] == Approx(0).margin(0.000001));
	const auto euclidean_norm = comp6771::euclidean_norm(vector);
	REQUIRE(euclidean_norm == Approx(0).margin(0.000001));
}

TEST_CASE("empty_constructor_euclidean_vector") {
	const auto vector = comp6771::euclidean_vector(0);
	REQUIRE(static_cast<size_t>(static_cast<size_t>(vector.dimensions())) == 0);
	const auto euclidean_norm = comp6771::euclidean_norm(vector);
	REQUIRE(euclidean_norm == Approx(0).margin(0.000001));
}

TEST_CASE("euclidean_vector_with_values") {
	const size_t size = 500;
	const auto value = -500.434;
	auto stdvector = std::vector<double>(size);
	std::iota(stdvector.begin(), stdvector.end(), value);
	// creating a euclidean vector with standard vector
	const auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
	REQUIRE(static_cast<size_t>(static_cast<size_t>(vector.dimensions())) == stdvector.size());
	REQUIRE(static_cast<size_t>(static_cast<size_t>(vector.dimensions())) == size);
	const auto casted_vector = comp6771_helpers::convert_to_vector_manually(vector);

	REQUIRE(
	   std::equal(&vector[0], &vector[0] + vector.dimensions(), stdvector.begin(), stdvector.end()));
	const auto euclidean_norm = comp6771::euclidean_norm(vector);
	REQUIRE(euclidean_norm >= 0);
	// manual computation of euclidean norm below for comparison
	double actual_euclidean_norm = 0;
	for (auto val : casted_vector) {
		actual_euclidean_norm += val * val;
	}
	actual_euclidean_norm = std::sqrt(actual_euclidean_norm);
	REQUIRE(euclidean_norm == Approx(actual_euclidean_norm).margin(0.000001));
}