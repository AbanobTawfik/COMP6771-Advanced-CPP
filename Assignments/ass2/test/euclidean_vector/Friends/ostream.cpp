#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>
#include <ostream>

// when we copy constructor, we want the created vector to be detatched from the original vector, this means
// changes to the copied vector do not carry through the original, however they start off the same!

auto compare_ostream(std::ostream& os1, std::ostream& os2) -> bool{
    std::stringstream check_os1;
    check_os1 << os1.rdbuf();
    const auto check_os2_value = check_os1.str();

    std::stringstream check_os2;
    check_os2 << os2.rdbuf();
    const auto check_os1_value = check_os2.str();

    return check_os1_value == check_os2_value;
}

TEST_CASE("os_works_correctly_equal_vectors_empty") {
    const auto vector = comp6771::euclidean_vector(0);
    REQUIRE(vector.dimensions() == 0);
    const auto empty_vector_string = "[]";
    std::cout.setstate(std::ios_base::badbit);
    std::ostream& os_vector = std::cout << vector << "\n";
    std::ostream& os_string = std::cout << empty_vector_string << "\n";

    REQUIRE(compare_ostream(os_vector, os_string));
    std::cout.clear();
}

TEST_CASE("os_works_correctly_equal_vectors_default_constructor_one_value") {
    const auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
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
    REQUIRE(vector.dimensions() == 10);
    REQUIRE(std::all_of(vector.begin(), vector.end(), [&](auto value) { return value == 5; }));
    // check if the equals now does the same thing
    const auto empty_vector_string = "[5 5 5 5 5 5 5 5 5 5]";
    std::cout.setstate(std::ios_base::badbit);
    std::ostream& os_vector = std::cout << vector << "\n";
    std::ostream& os_string = std::cout << empty_vector_string << "\n";
    REQUIRE(compare_ostream(os_vector, os_string));
    std::cout.clear();
}

