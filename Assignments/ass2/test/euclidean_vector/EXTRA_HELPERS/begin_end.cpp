#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <vector>

// to test begin and end we have the following test cases, and compare the result to a standard vector
// 1. using begin and end, we will iterate over the euclidean vector, pushing the value at each iteration into a initially
//    empty standard vector. To then verify we check that the value of each index at the original euclidean vector is the same
//    as the value in our standard vector.
// 2. make sure empty vector has correct behaviour

TEST_CASE("iterates_correctly_empty") {
    // empty euclidean vector -> empty standard vector
    const auto vector = comp6771::euclidean_vector(0);
    const auto stdvector_empty = std::vector<double>();
    // to check iterating accross has the correct values i will store the results of pushing into a new array
    // in another vector, and compare with a casted stdvector of the original vector
    auto iterate_vector = std::vector<double>();
    std::for_each(vector.begin(), vector.end(), [&](auto value){iterate_vector.push_back(value);});
    REQUIRE(std::equal(stdvector_empty.begin(), stdvector_empty.end(), iterate_vector.begin(), iterate_vector.end()));
}

TEST_CASE("iterates_correctly_begin_end_no_cast") {
    const size_t size = 100000;
    const auto value = 5;
    const auto vector = comp6771::euclidean_vector(size, value);
    // to check iterating accross has the correct values i will store the results of pushing into a new array
    // in another vector, and compare with a casted stdvector of the original vector
    // i will perform this iteration more naturally however using begin and end just to make sure it works
    auto iterate_vector = std::vector<double>();
    for(auto i = vector.begin(); i != vector.end(); i++){
        iterate_vector.push_back(*i);
    }
    REQUIRE(static_cast<size_t>(vector.dimensions()) == size);
    REQUIRE(iterate_vector.size() == static_cast<size_t>(vector.dimensions()));
    // now that we ITERATED over the vector using begin and end, we know that we want the new vector to have MATCHING
    // VALUES AT ALL INDEXES TO ORIGINAL VECTOR
    for(size_t i = 0; i < size; i++){
        REQUIRE(iterate_vector.at(i) == Approx(vector.at(static_cast<int>(i))).margin(0.000001));
    }
}