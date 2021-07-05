#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// these tests will check the 2 cases
// 1. empty euclidean vector -> stdvector, expecting an empty vector, here we play around with
// casting to see
//    if the empty stdvector we casted from creates an empty euclidean vector
// 2. euclidean vector with values -> list with values in the same index corresponding to the
// euclidean vector

TEST_CASE("empty_vector_to_vec") {
	const auto vector = comp6771::euclidean_vector(0);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 0);
	const auto casted_vector = static_cast<std::vector<double>>(vector);
	REQUIRE(casted_vector.empty());
	const auto recreated_from_cast =
	   comp6771::euclidean_vector(casted_vector.begin(), casted_vector.end());
	REQUIRE(static_cast<size_t>(recreated_from_cast.dimensions()) == 0);
	REQUIRE(recreated_from_cast == vector);
}

// create euclidean vector with std vector, then cast it as std vector to see if same result
TEST_CASE("vector_recasts") {
	const size_t size = 500;
	const auto value = -500.434;
	auto stdvector = std::vector<double>(size);
	// values using iota will be steadily increasing so all different
	std::iota(stdvector.begin(), stdvector.end(), value);
	// creating a euclidean vector with standard vector
	const auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
	const auto casted_vector = comp6771_helpers::convert_to_vector_manually(vector);

	REQUIRE(std::equal(casted_vector.begin(), casted_vector.end(), stdvector.begin(), stdvector.end()));
	// now we will cast that euclidean vector we verified was the same as the standard vector used to
	// create it and compare the two vectors
	auto stdvector_casted = static_cast<std::vector<double>>(vector);
	REQUIRE(
	   std::equal(stdvector.begin(), stdvector.end(), stdvector_casted.begin(), stdvector_casted.end()));
}