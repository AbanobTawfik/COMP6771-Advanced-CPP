#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// to test dot product we have a few weird cases and exception cases to test, alongside default
// behaviour
// 1. two empty vectors, [].[] = 0
// 2. dot product with values should return the correct dot product value
// 3. different sized vectors should throw the correct exception

TEST_CASE("dot_product_empty_vectors") {
	const auto left_vector = comp6771::euclidean_vector();
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == 1);
	REQUIRE(left_vector[0] == Approx(0).margin(0.000001));

	const auto right_vector = comp6771::euclidean_vector();
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == 1);
	REQUIRE(right_vector[0] == Approx(0).margin(0.000001));

	const auto dot_product = comp6771::dot(left_vector, right_vector);

	// make sure dot product is correctly calculated
	// [0] . [0] = 0 + 0 -> 0
	REQUIRE(dot_product == Approx(0).margin(0.000001));
}

TEST_CASE("dot_product_with_different_values") {
	const size_t size = 500;
	const auto value = -500.434;
	auto left_stdvector = std::vector<double>(size);

	std::iota(left_stdvector.begin(), left_stdvector.end(), value);
	auto left_vector = comp6771::euclidean_vector(left_stdvector.begin(), left_stdvector.end());
	const auto casted_left_vector = comp6771_helpers::convert_to_vector_manually(left_vector);
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
	const auto dot_product = comp6771::dot(left_vector, right_vector);
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == size);
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == size);
	// make sure right vector and left vector doesn't change
	REQUIRE(std::equal(casted_right_vector.begin(),
	                   casted_right_vector.end(),
	                   right_stdvector.begin(),
	                   right_stdvector.end()));
	REQUIRE(std::equal(casted_left_vector.begin(),
	                   casted_left_vector.end(),
	                   left_stdvector.begin(),
	                   left_stdvector.end()));

	// now i need to check the dot product contains, the right value, the dot product is simply just
	// the sum of all vector values at the same index multiplied together, [1 2 3] [3 2 1] -> 1*3 +
	// 2*2 + 3*1 = 10 so we will manually compute this the long way here and compare to the much more
	// concise solution found in the class
	double dot_product_compare = 0;
	for (auto i = 0; i < static_cast<int>(size); i++) {
		dot_product_compare += left_vector[static_cast<int>(i)] * right_vector[static_cast<int>(i)];
	}
	REQUIRE(dot_product == Approx(dot_product_compare).margin(0.000001));
}

// Exception, different sizes
TEST_CASE("dot_product_different_size") {
	const auto size1 = 3;
	const auto size2 = 5;
	REQUIRE(size1 != size2);
	const auto val = 3;
	auto left_vector = comp6771::euclidean_vector(size1, val);
	auto right_vector = comp6771::euclidean_vector(size2, val);
	const auto casted_left_vector = comp6771_helpers::convert_to_vector_manually(left_vector);
	const auto casted_right_vector = comp6771_helpers::convert_to_vector_manually(right_vector);
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == size1);
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == size2);
	REQUIRE(std::all_of(casted_left_vector.begin(), casted_left_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));
	REQUIRE(std::all_of(casted_right_vector.begin(), casted_right_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));
	REQUIRE_THROWS_WITH(comp6771::dot(left_vector, right_vector),
	                    "Dimensions of LHS(" + std::to_string(size1) + ") and RHS ("
	                       + std::to_string(size2) + ") do not match");
	// make sure the original vectors are unchanged!
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == size1);
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == size2);
	REQUIRE(std::all_of(casted_left_vector.begin(), casted_left_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));
	REQUIRE(std::all_of(casted_right_vector.begin(), casted_right_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));
}