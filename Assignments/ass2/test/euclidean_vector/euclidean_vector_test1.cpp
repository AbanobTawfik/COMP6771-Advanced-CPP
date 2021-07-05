#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>

TEST_CASE("basic test") {
	// Please note - this test may not function, it's just here for stubbing purposes
	auto  a1 = comp6771::euclidean_vector(3, 3.0);
	auto  a2 = comp6771::euclidean_vector(3, 3.0);
	auto  a3 = comp6771::euclidean_vector(3, 3.0);

	auto oss = std::ostringstream{};
	oss << (a1 + a2 + a3);
	CHECK(oss.str() == "[9 9 9]");

}