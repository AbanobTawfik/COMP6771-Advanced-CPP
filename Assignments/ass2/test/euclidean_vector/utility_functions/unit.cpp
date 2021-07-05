#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// here we want to test all behaviour of unit vector including all edge cases
// 1. unit vector of size 1 e.g. [1] -> [1/1] == [1]
// 2. unit vector that contains many values is computed correctly, to do this we will check the unit
// vector
//    is equivalent to the original vector divided by the euclidean norm
// 3. case where euclidean norm = 0, i.e. 0 vector [0] n times
// 4. case where vector is dimensionless i.e [] empty vector

TEST_CASE("unit_vector_size1") {
	const auto vector = comp6771::euclidean_vector(1, 1);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	REQUIRE(vector[0] == Approx(1).margin(0.000001));
	const auto euclidean_norm = comp6771::euclidean_norm(vector);
	// sqrt(1*1) = 1
	REQUIRE(euclidean_norm == Approx(1).margin(0.000001));
	const auto unit_vector = comp6771::unit(vector);
	REQUIRE(static_cast<size_t>(unit_vector.dimensions() == vector.dimensions()));
	// now we need to check the unit vector gave us the correct value, since the unit vector is just
	// all values, divided by the euclidean norm, in this case 1, it should return just the same
	// vector
	REQUIRE(unit_vector == vector / 1); // <-- vector = vector/1, where 1 is the euclidean norm
}

TEST_CASE("euclidean_vector_alot_of_values") {
	const size_t size = 500;
	const auto value = -500.434;
	auto stdvector = std::vector<double>(size);
	std::iota(stdvector.begin(), stdvector.end(), value);
	const auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());
	REQUIRE(static_cast<size_t>(static_cast<size_t>(vector.dimensions())) == stdvector.size());
	REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
	const auto casted_vector = comp6771_helpers::convert_to_vector_manually(vector);
	REQUIRE(std::equal(casted_vector.begin(), casted_vector.end(), stdvector.begin(), stdvector.end()));
	// actually computing the euclidean norm to verify its the correct norm
	const auto euclidean_norm = comp6771::euclidean_norm(vector);
	REQUIRE(euclidean_norm >= 0);
	double actual_euclidean_norm = 0;
	for (auto val : casted_vector) {
		actual_euclidean_norm += val * val;
	}
	actual_euclidean_norm = std::sqrt(actual_euclidean_norm);
	// comparing actual euclidean norm computed by hand with the internal one from the comp6771
	// namespace
	REQUIRE(euclidean_norm == Approx(actual_euclidean_norm).margin(0.000001));
	const auto unit_vector = comp6771::unit(vector);
	REQUIRE(static_cast<size_t>(unit_vector.dimensions() == vector.dimensions()));
	REQUIRE(unit_vector == vector / euclidean_norm);
}

// Exceptions
TEST_CASE("unit_vector_0_euclidean_norm") {
	// creating 0 vector, dimension 1 aka default vector
	const auto vector = comp6771::euclidean_vector();
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	REQUIRE(vector[0] == Approx(0).margin(0.000001));
	// euclidean norm will be 0
	auto euclidean_norm = comp6771::euclidean_norm(vector);
	// sqrt(0*0) = 0
	REQUIRE(euclidean_norm == Approx(0).margin(0.000001));

	REQUIRE_THROWS_WITH(comp6771::unit(vector),
	                    "euclidean_vector with zero euclidean normal does not have a unit vector");
	// original vector is unmodified!
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 1);
	REQUIRE(vector[0] == Approx(0).margin(0.000001));
	euclidean_norm = comp6771::euclidean_norm(vector);
	REQUIRE(euclidean_norm == Approx(0).margin(0.000001));
}

// empty unit vector case dimensionless takes precedence over 0 euclidean norm error case
TEST_CASE("unit_vector_0_dimensions") {
	// creating 0 vector, dimension 1 aka default vector
	const auto vector = comp6771::euclidean_vector(0);
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 0);
	// euclidean norm will be 0
	const auto euclidean_norm = comp6771::euclidean_norm(vector);
	// sqrt(0*0) = 0
	REQUIRE(euclidean_norm == 0);
	REQUIRE_THROWS_WITH(comp6771::unit(vector),
	                    "euclidean_vector with no dimensions does not have a unit vector");
	// original vector is unmodified
	REQUIRE(static_cast<size_t>(vector.dimensions()) == 0);
}