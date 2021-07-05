#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// since subtraction is something that can be done compoundly, many test cases had to be done to
// make sure it behaved properly for all use cases, all use cases handle all possible uses for the -
// operator, and are expected to work correctly
// 1. use case 1. 2 empty vectors [] = [] - []
// 2. use case 2. 2 vectors with values are correctly added and stored into third vector
// 3. use case 3. multiple vectors being added correctly, vec1 = vec2 - vec3 - vec4, must add all 3
// correctly
// 4. use case 4. multiple operations with vector addition, vec1 = vec2 - vec3 + vec4, must perform
// operation correctly
// 5. use case 5. vectors have different size, must throw the correct exception

TEST_CASE("basic_subtraction_empty_vectors") {
	auto left_vector = comp6771::euclidean_vector(0);
	auto right_vector = comp6771::euclidean_vector(0);
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == 0);
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == 0);

	const auto subtracted_vector = left_vector - right_vector;
	// make sure dimensions dont change, nothing should happen, [] + [] = []
	REQUIRE(static_cast<size_t>(subtracted_vector.dimensions()) == 0);
	REQUIRE(static_cast<size_t>(subtracted_vector.dimensions()) == 0);
}

TEST_CASE("basic_subtraction_case_different_values") {
	const size_t size = 500;
	const auto value = -500.434;
	auto left_stdvector = std::vector<double>(size);
	// values using iota will be steadily increasing so all different
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
	const auto casted_right_vector = comp6771_helpers::convert_to_vector_manually(right_vector);
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == right_stdvector.size());
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == size);
	REQUIRE(std::equal(casted_right_vector.begin(),
	                   casted_right_vector.end(),
	                   right_stdvector.begin(),
	                   right_stdvector.end()));
	// keep in mind our original 2 std vectors stay the same, so we will compare the values in them
	// to the result below
	const auto subtracted_vector = left_vector - right_vector;
	const auto casted_subtracted_vector =
	   comp6771_helpers::convert_to_vector_manually(subtracted_vector);
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == size);
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == size);
	REQUIRE(static_cast<size_t>(subtracted_vector.dimensions()) == size);
	// make sure the 2 vectors dont change!
	REQUIRE(std::equal(casted_left_vector.begin(),
	                   casted_left_vector.end(),
	                   left_stdvector.begin(),
	                   left_stdvector.end()));
	REQUIRE(std::equal(casted_right_vector.begin(),
	                   casted_right_vector.end(),
	                   right_stdvector.begin(),
	                   right_stdvector.end()));
	size_t count = 0;
	size_t count2 = 0;
	REQUIRE(
	   std::all_of(casted_subtracted_vector.begin(), casted_subtracted_vector.end(), [&](auto value) {
		   return value
		          == Approx(left_stdvector.at(count++) - right_stdvector.at(count2++)).margin(0.000001);
	   }));
}

TEST_CASE("basic_subtraction_case_multiple_vectors") {
	const size_t size = 3;
	auto l_value = 3;
	auto r_value = 4;
	auto m_value = 5;
	const auto left_vector = comp6771::euclidean_vector(size, l_value);
	const auto casted_left_vector = comp6771_helpers::convert_to_vector_manually(left_vector);
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == size);
	REQUIRE(std::all_of(casted_left_vector.begin(), casted_left_vector.end(), [&](auto value) {
		return value == Approx(l_value).margin(0.000001);
	}));
	const auto right_vector = comp6771::euclidean_vector(size, r_value);
	const auto casted_right_vector = comp6771_helpers::convert_to_vector_manually(right_vector);
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == size);
	REQUIRE(std::all_of(casted_right_vector.begin(), casted_right_vector.end(), [&](auto value) {
		return value == Approx(r_value).margin(0.000001);
	}));
	const auto middle_vector = comp6771::euclidean_vector(size, m_value);
	const auto casted_middle_vector = comp6771_helpers::convert_to_vector_manually(middle_vector);
	REQUIRE(static_cast<size_t>(middle_vector.dimensions()) == size);
	REQUIRE(std::all_of(casted_middle_vector.begin(), casted_middle_vector.end(), [&](auto value) {
		return value == Approx(m_value).margin(0.000001);
	}));
	const auto added_vector = left_vector - right_vector - middle_vector;
	const auto casted_added_vector = comp6771_helpers::convert_to_vector_manually(added_vector);
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == 3);
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == 3);
	REQUIRE(static_cast<size_t>(middle_vector.dimensions()) == 3);
	// make sure both vectors are  unaffected
	REQUIRE(std::all_of(casted_left_vector.begin(), casted_left_vector.end(), [&](auto value) {
		return value == Approx(l_value).margin(0.000001);
	}));
	REQUIRE(std::all_of(casted_right_vector.begin(), casted_right_vector.end(), [&](auto value) {
		return value == Approx(r_value).margin(0.000001);
	}));
	REQUIRE(std::all_of(casted_middle_vector.begin(), casted_middle_vector.end(), [&](auto value) {
		return value == Approx(m_value).margin(0.000001);
	}));
	// check the addition worked correctly
	REQUIRE(static_cast<size_t>(added_vector.dimensions()) == size);
	REQUIRE(std::all_of(casted_added_vector.begin(), casted_added_vector.end(), [&](auto value) {
		return value == Approx(l_value - r_value - m_value).margin(0.000001);
	}));
}

// HANDLE EXCEPTIONS NOW
TEST_CASE("subtraction_different_size") {
	const auto size1 = 3;
	const auto size2 = 5;
	REQUIRE(size1 != size2);
	const auto val = 3;
	auto left_vector = comp6771::euclidean_vector(size1, val);
	auto right_vector = comp6771::euclidean_vector(size2, val);
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == size1);
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == size2);
	const auto casted_left_vector = comp6771_helpers::convert_to_vector_manually(left_vector);
	const auto casted_right_vector = comp6771_helpers::convert_to_vector_manually(right_vector);
	REQUIRE(std::all_of(casted_left_vector.begin(), casted_left_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));
	REQUIRE(std::all_of(casted_right_vector.begin(), casted_right_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));
	comp6771::euclidean_vector subtracted_vector;
	REQUIRE_THROWS_WITH(subtracted_vector = left_vector - right_vector,
	                    "Dimensions of LHS(" + std::to_string(size1) + ") and RHS ("
	                       + std::to_string(size2) + ") do not match");
	// NO CHANGES!
	REQUIRE(static_cast<size_t>(left_vector.dimensions()) == size1);
	REQUIRE(std::all_of(casted_left_vector.begin(), casted_left_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));
	REQUIRE(static_cast<size_t>(right_vector.dimensions()) == size2);
	REQUIRE(std::all_of(casted_right_vector.begin(), casted_right_vector.end(), [&](auto value) {
		return value == Approx(val).margin(0.000001);
	}));
}