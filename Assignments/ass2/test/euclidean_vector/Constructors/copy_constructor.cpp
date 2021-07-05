#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// i wrote 3 tests to check all possible behaviour and expected outcome of using copy constructor
// Test 1 : tests that creating a copy of an empty vector returns a correct empty vector
// Test 2 : just makes sure that when copying a vector, all values are identical to the original
// vector Test 3 : makes sure that when changing a value, the other vector it was copied from is
// unaffected

TEST_CASE("empty_copy_constructor") {
	const auto empty_constructor = comp6771::euclidean_vector();
	const auto copy_empty_constructor = comp6771::euclidean_vector(empty_constructor);
	REQUIRE(empty_constructor.dimensions() == 1);
	REQUIRE(copy_empty_constructor.dimensions() == 1);
	REQUIRE(empty_constructor[0] == Approx(0).margin(0.000001));
	REQUIRE(copy_empty_constructor[0] == Approx(empty_constructor[0]).margin(0.000001));
}

TEST_CASE("copy_with_values_no_change") {
	const size_t size = 500;
	const auto value = -500.434;
	auto stdvector = std::vector<double>(size);
	// values using iota will be steadily increasing so all different
	std::iota(stdvector.begin(), stdvector.end(), value);
	const auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
	const auto copy_vector = comp6771::euclidean_vector(vector);

	REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
	REQUIRE(vector.dimensions() == copy_vector.dimensions());
	const auto vector_casted = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(std::equal(vector_casted.begin(), vector_casted.end(), stdvector.begin(), stdvector.end()));
}

TEST_CASE("copy_with_values_change_after") {
	const size_t size = 500;
	const auto value = -500.434;
	auto stdvector = std::vector<double>(size);
	// values using iota will be steadily increasing so all different
	std::iota(stdvector.begin(), stdvector.end(), value);
	auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
	auto check_no_changes = comp6771::euclidean_vector(vector);
	auto copy_vector = comp6771::euclidean_vector(vector);
	REQUIRE(vector.dimensions() == size);
	REQUIRE(vector.dimensions() == copy_vector.dimensions());
	const auto vector_casted = comp6771_helpers::convert_to_vector_manually(vector);
	const auto copy_vector_casted = comp6771_helpers::convert_to_vector_manually(copy_vector);
	const auto check_no_changed_casted =
	   comp6771_helpers::convert_to_vector_manually(check_no_changes);
	REQUIRE(std::equal(vector_casted.begin(),
	                   vector_casted.end(),
	                   copy_vector_casted.begin(),
	                   copy_vector_casted.end()));
	// add 1 to all values in vector
	copy_vector[0]++;
	// first check all values are unchanged on original vector, then check changes occured
	REQUIRE(std::equal(vector_casted.begin(),
	                   vector_casted.end(),
	                   check_no_changed_casted.begin(),
	                   check_no_changed_casted.end()));

	REQUIRE(copy_vector[0] == Approx(vector[0] + 1).margin(0.000001));
	REQUIRE(std::equal(vector_casted.begin() + 1,
	                   vector_casted.end(),
	                   copy_vector_casted.begin() + 1,
	                   copy_vector_casted.end()));
}