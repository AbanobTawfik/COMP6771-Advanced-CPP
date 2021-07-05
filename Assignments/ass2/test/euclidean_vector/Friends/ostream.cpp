#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <iostream>
#include <ostream>
#include <sstream>

// to test ostream works correctly, two ostreams will be made using cout's silenced input silenced
// by a bad bit the string literal vector (expected result) will be passed into one of the ostream
// and the other will take the vector in, and these two will be compared for equality. at the end of
// this, the cout stream is cleared to removed the bad bit.

// this function just compares the strings stored inside the ostream for compairson sake
auto compare_ostream(std::ostream& os1, std::ostream& os2) -> bool {
	std::stringstream check_os1;
	check_os1 << os1.rdbuf();
	const auto check_os2_value = check_os1.str();

	std::stringstream check_os2;
	check_os2 << os2.rdbuf();
	const auto check_os1_value = check_os2.str();

	return check_os1_value == check_os2_value;
}

// check that the empty euclidean vector outputs []
TEST_CASE("os_works_correctly_equal_vectors_empty") {
	const auto vector = comp6771::euclidean_vector(0);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 0);
	const auto empty_vector_string = "[]";
	std::cout.setstate(std::ios_base::badbit);
	std::ostream& os_vector = std::cout << vector << "\n";
	std::ostream& os_string = std::cout << empty_vector_string << "\n";

	REQUIRE(compare_ostream(os_vector, os_string));
	std::cout.clear();
}

TEST_CASE("os_works_correctly_equal_vectors_default_constructor_one_value") {
	const auto vector = comp6771::euclidean_vector();
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	REQUIRE(vector[0] == Approx(0).margin(0.000001));
	const auto empty_vector_string = "[0]";
	std::cout.setstate(std::ios_base::badbit);
	std::ostream& os_vector = std::cout << vector << "\n";
	std::ostream& os_string = std::cout << empty_vector_string << "\n";
	REQUIRE(compare_ostream(os_vector, os_string));
	std::cout.clear();
}

TEST_CASE("os_works_correctly_multiple_values") {
	const auto vector = comp6771::euclidean_vector(10, 5);
	// check vectors are equal first by checking properties of internals
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 10);
	const auto casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(std::all_of(casted_vector.begin(), casted_vector.end(), [&](auto value) {
		return value == Approx(5).margin(0.000001);
	}));
	// check if the equals now does the same thing
	const auto empty_vector_string = "[5 5 5 5 5 5 5 5 5 5]";
	std::cout.setstate(std::ios_base::badbit);
	std::ostream& os_vector = std::cout << vector << "\n";
	std::ostream& os_string = std::cout << empty_vector_string << "\n";
	REQUIRE(compare_ostream(os_vector, os_string));
	std::cout.clear();
}
