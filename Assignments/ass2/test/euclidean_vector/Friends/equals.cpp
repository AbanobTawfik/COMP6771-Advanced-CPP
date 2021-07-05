#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// to check equals works correctly, there are two cases to test
// 1. equals for the case where they are equal -> TRUE
// 2. equals for the case where they are not equal -> FALSE
// to test cases where they are equal, we will compare the two vectors to a standard, and if they
// pass that, then when we check equals gives us true we know it is correct similair for the case
// where they aren't equal, we will compare the two vectors to a similair standard, and expect them
// to fail that, then we will check that equals gives us false which we know is correct

// weird cases to also handle, empty vectors which are always equal, [] == []
// vectors created from each other
// vectors created from common objects
// vectors created from different methods expecting the same results

TEST_CASE("equals_works_correctly_equal_vectors_empty") {
	const auto vector_one = comp6771::euclidean_vector(0);
	const auto vector_two = comp6771::euclidean_vector(0);
	REQUIRE(static_cast<size_t>(vector_one.dimensions()) == 0);
	REQUIRE(static_cast<size_t>(vector_two.dimensions()) == 0);
	auto equal = (vector_one == vector_two);
	REQUIRE(equal);
}

// this specific case tests a euclidean vector with size 0, and a euclidean vector made from an
// empty standard vector returns equals true

TEST_CASE("equals_works_correctly_equal_vectors_empty2") {
	const auto vector_one = comp6771::euclidean_vector(0);
	const auto empty_vector = std::vector<double>();
	const auto vector_two = comp6771::euclidean_vector(empty_vector.begin(), empty_vector.end());
	REQUIRE(static_cast<size_t>(vector_one.dimensions()) == 0);
	REQUIRE(static_cast<size_t>(vector_two.dimensions()) == 0);
	auto equal = (vector_one == vector_two);
	REQUIRE(equal);
}

// this specific case just checks equals works on default constructor
TEST_CASE("equals_works_correctly_equal_vectors_default_constructor") {
	const auto vector_one = comp6771::euclidean_vector();
	const auto vector_two = comp6771::euclidean_vector();
	REQUIRE(static_cast<size_t>(vector_one.dimensions()) == 1);
	REQUIRE(vector_one[0] == Approx(0).margin(0.000001));
	REQUIRE(static_cast<size_t>(vector_two.dimensions()) == 1);
	REQUIRE(vector_two[0] == Approx(0).margin(0.000001));
	auto equal = (vector_one == vector_two);
	REQUIRE(equal);
}

// this specific case checks two vectors with values created the same way are also equal
TEST_CASE("equals_works_correctly_equal_vectors") {
	const auto vector_one = comp6771::euclidean_vector(10, 5);
	const auto vector_two = comp6771::euclidean_vector(10, 5);
	// check vectors are equal first by checking properties of internals
	REQUIRE(static_cast<size_t>(vector_one.dimensions()) == 10);
	const auto casted_vector_one = comp6771_helpers::convert_to_vector_manually(vector_one);
	const auto casted_vector_two = comp6771_helpers::convert_to_vector_manually(vector_two);
	REQUIRE(std::all_of(casted_vector_one.begin(), casted_vector_one.end(), [&](auto value) {
		return value == Approx(5).margin(0.000001);
	}));
	REQUIRE(static_cast<size_t>(vector_two.dimensions()) == 10);
	REQUIRE(std::all_of(casted_vector_two.begin(), casted_vector_two.end(), [&](auto value) {
		return value == Approx(5).margin(0.000001);
	}));
	// check if the equals now does the same thing
	auto equal = (vector_one == vector_two);
	REQUIRE(equal);
}

// this specific case checks that when you create a vector from another vector, they are equal
TEST_CASE("equals_works_correctly_equal_vectors_assigned1") {
	const auto vector_one = comp6771::euclidean_vector(10, 5);
	const auto vector_two = comp6771::euclidean_vector(vector_one);
	REQUIRE(static_cast<size_t>(vector_one.dimensions()) == 10);
	const auto casted_vector_one = comp6771_helpers::convert_to_vector_manually(vector_one);
	const auto casted_vector_two = comp6771_helpers::convert_to_vector_manually(vector_two);
	REQUIRE(std::all_of(casted_vector_one.begin(), casted_vector_one.end(), [&](auto value) {
		return value == Approx(5).margin(0.000001);
	}));
	REQUIRE(static_cast<size_t>(vector_two.dimensions()) == 10);
	REQUIRE(std::all_of(casted_vector_two.begin(), casted_vector_two.end(), [&](auto value) {
		return value == Approx(5).margin(0.000001);
	}));
	auto equal = (vector_one == vector_two);
	REQUIRE(equal);
}

// this final equals case checks the copy vector also returns equal as true
TEST_CASE("equals_works_correctly_equal_vectors_assigned2") {
	const auto vector_one = comp6771::euclidean_vector(10, 5);
	const auto vector_two = vector_one;
	REQUIRE(static_cast<size_t>(vector_one.dimensions()) == 10);
	const auto casted_vector_one = comp6771_helpers::convert_to_vector_manually(vector_one);
	const auto casted_vector_two = comp6771_helpers::convert_to_vector_manually(vector_two);
	REQUIRE(std::all_of(casted_vector_one.begin(), casted_vector_one.end(), [&](auto value) {
		return value == Approx(5).margin(0.000001);
	}));
	REQUIRE(static_cast<size_t>(vector_two.dimensions()) == 10);
	REQUIRE(std::all_of(casted_vector_two.begin(), casted_vector_two.end(), [&](auto value) {
		return value == Approx(5).margin(0.000001);
	}));
	auto equal = (vector_one == vector_two);
	REQUIRE(equal);
}

// check if vector with different size and values are not equal
TEST_CASE("equals_works_correctly_unequal_vectors") {
	const auto vector_one = comp6771::euclidean_vector(10, 5);
	const auto vector_two = comp6771::euclidean_vector(15, 5);
	REQUIRE(static_cast<size_t>(vector_one.dimensions()) == 10);
	const auto casted_vector_one = comp6771_helpers::convert_to_vector_manually(vector_one);
	const auto casted_vector_two = comp6771_helpers::convert_to_vector_manually(vector_two);
	REQUIRE(std::all_of(casted_vector_one.begin(), casted_vector_one.end(), [&](auto value) {
		return value == Approx(5).margin(0.000001);
	}));
	REQUIRE(static_cast<size_t>(vector_two.dimensions()) == 15);
	REQUIRE(std::all_of(casted_vector_two.begin(), casted_vector_two.end(), [&](auto value) {
		return value == Approx(5).margin(0.000001);
	}));
	auto equal = (vector_one == vector_two);
	REQUIRE(!equal);
}