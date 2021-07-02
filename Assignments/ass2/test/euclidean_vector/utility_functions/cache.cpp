#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <iostream>
#include <vector>

TEST_CASE("cache_storing_correctly") {
    const auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
    // initialised with invalidation
    REQUIRE(vector.check_cached_norm() == -1);
    const auto euclidean_norm = comp6771::euclidean_norm(vector);
    REQUIRE(euclidean_norm == 0);
    // O(1)
    const auto cached_norm = vector.check_cached_norm();
    REQUIRE(cached_norm == euclidean_norm);
}

// we will see how many more nanoseconds caching saves as to not caching on a VERY LARGE VECTOR
TEST_CASE("cache_speeds_up_code") {
    const auto size = 1000000;
    const auto value = -459.34234978;
    auto stdvector = std::vector<double>(size);
    std::iota(stdvector.begin(), stdvector.end(), value);
    auto vector = comp6771::euclidean_vector(stdvector.begin(), stdvector.end());

    auto cache_before_call = vector.check_cached_norm();
    REQUIRE(cache_before_call == -1);

    auto start = std::chrono::high_resolution_clock::now();
    auto norm = comp6771::euclidean_norm(vector);
    auto end = std::chrono::high_resolution_clock::now();
    auto cache_after_call = vector.check_cached_norm();
    REQUIRE(norm == cache_after_call);
    auto duration_uncached = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    auto start_cached = std::chrono::high_resolution_clock::now();
    auto norm_after_one_call = comp6771::euclidean_norm(vector);
    auto end_cached = std::chrono::high_resolution_clock::now();
    auto duration_cached = std::chrono::duration_cast<std::chrono::nanoseconds>(end_cached - start_cached);
    REQUIRE(norm == norm_after_one_call);
    REQUIRE(norm_after_one_call == cache_after_call);

    // since this vector is very large we will just make sure it is atleast 1000x more faster in terms of milliseconds
    // to computer
    // since caching is meant to be O(1),
    REQUIRE(duration_cached.count() * 1000 < duration_uncached.count());
    // for debug purpose if needed
    //std::cout << "uncached: "<< duration_uncached.count() << std::endl << "cached: " << duration_cached.count() << std::endl;
}

TEST_CASE("cache_invalidation_on_initialisation") {
    const auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == 0);
    // initialised with invalidation
    const auto cached_norm = vector.check_cached_norm();
    REQUIRE(cached_norm == -1);
}

TEST_CASE("cache_invalidation_before_calling_norm") {
    const auto vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(vector.dimensions() == 10);
    auto count = 0;
    bool all_values_same = std::all_of(vector.begin(), vector.end(), [&](auto value) { return value == count++; });
    REQUIRE(all_values_same);
    // initialised with invalidation
    const auto cached_norm_before_calling_norm = vector.check_cached_norm();
    REQUIRE(cached_norm_before_calling_norm == -1);
    const auto euclidean_norm = comp6771::euclidean_norm(vector);
    const auto cached_norm_before_mutation_calculated = vector.check_cached_norm();
    REQUIRE(cached_norm_before_calling_norm != cached_norm_before_mutation_calculated);
    REQUIRE(euclidean_norm == cached_norm_before_mutation_calculated);
}

TEST_CASE("cache_invalidation_on_at") {
    auto vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const auto index_to_change = 3;
    REQUIRE(index_to_change >= 0);
    REQUIRE(index_to_change < vector.dimensions());
    const auto value_to_change = 69;
    REQUIRE(vector.dimensions() == 10);
    auto count = 0;
    bool all_values_same = std::all_of(vector.begin(), vector.end(), [&](auto value) { return value == count++; });
    REQUIRE(all_values_same);
    // initialised with invalidation
    const auto cached_norm_before_calculation = vector.check_cached_norm();
    REQUIRE(cached_norm_before_calculation == -1);
    const auto euclidean_norm_pre_mutation = comp6771::euclidean_norm(vector);
    const auto cached_norm_before_mutation_calculated = vector.check_cached_norm();
    const auto euclidean_norm_again = comp6771::euclidean_norm(vector);
    REQUIRE(cached_norm_before_calculation != cached_norm_before_mutation_calculated);
    REQUIRE(euclidean_norm_pre_mutation == cached_norm_before_mutation_calculated);
    REQUIRE(euclidean_norm_again == cached_norm_before_mutation_calculated);
    vector.at(index_to_change) = value_to_change;

    const auto cached_norm_after_mutation = vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation == -1);
    const auto euclidean_norm_post_mutation = comp6771::euclidean_norm(vector);
    const auto cached_norm_after_mutation_calculated = vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation_calculated == euclidean_norm_post_mutation);
    REQUIRE(cached_norm_after_mutation_calculated != cached_norm_before_mutation_calculated);
}

TEST_CASE("cache_invalidation_on_subscript") {
    auto vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const auto index_to_change = 3;
    REQUIRE(index_to_change >= 0);
    REQUIRE(index_to_change < vector.dimensions());
    const auto value_to_change = 69;
    REQUIRE(vector.dimensions() == 10);
    auto count = 0;
    bool all_values_same = std::all_of(vector.begin(), vector.end(), [&](auto value) { return value == count++; });
    REQUIRE(all_values_same);
    // initialised with invalidation
    const auto cached_norm_before_calculation = vector.check_cached_norm();
    REQUIRE(cached_norm_before_calculation == -1);
    const auto euclidean_norm_pre_mutation = comp6771::euclidean_norm(vector);
    const auto cached_norm_before_mutation_calculated = vector.check_cached_norm();
    const auto euclidean_norm_again = comp6771::euclidean_norm(vector);
    REQUIRE(cached_norm_before_calculation != cached_norm_before_mutation_calculated);
    REQUIRE(euclidean_norm_pre_mutation == cached_norm_before_mutation_calculated);
    REQUIRE(euclidean_norm_again == cached_norm_before_mutation_calculated);
    vector[index_to_change] = value_to_change;

    const auto cached_norm_after_mutation = vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation == -1);
    const auto euclidean_norm_post_mutation = comp6771::euclidean_norm(vector);
    const auto cached_norm_after_mutation_calculated = vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation_calculated == euclidean_norm_post_mutation);
    REQUIRE(cached_norm_after_mutation_calculated != cached_norm_before_mutation_calculated);
}


TEST_CASE("cache_invalidation_on_compound_add") {
    auto base_vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(base_vector.dimensions() == 10);
    auto count = 0;
    bool all_values_same = std::all_of(base_vector.begin(), base_vector.end(),
                                       [&](auto value) { return value == count++; });
    REQUIRE(all_values_same);
    auto vector_right = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(vector_right.dimensions() == 10);
    count = 0;
    all_values_same = std::all_of(vector_right.begin(), vector_right.end(),
                                  [&](auto value) { return value == count++; });
    REQUIRE(all_values_same);
    // initialised with invalidation
    const auto cached_norm_before_calculation = base_vector.check_cached_norm();
    REQUIRE(cached_norm_before_calculation == -1);
    const auto euclidean_norm_pre_mutation = comp6771::euclidean_norm(base_vector);
    const auto cached_norm_before_mutation_calculated = base_vector.check_cached_norm();
    const auto euclidean_norm_again = comp6771::euclidean_norm(base_vector);
    REQUIRE(cached_norm_before_calculation != cached_norm_before_mutation_calculated);
    REQUIRE(euclidean_norm_pre_mutation == cached_norm_before_mutation_calculated);
    REQUIRE(euclidean_norm_again == cached_norm_before_mutation_calculated);
    base_vector += vector_right;

    const auto cached_norm_after_mutation = base_vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation == -1);
    const auto euclidean_norm_post_mutation = comp6771::euclidean_norm(base_vector);
    const auto cached_norm_after_mutation_calculated = base_vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation_calculated == euclidean_norm_post_mutation);
    REQUIRE(cached_norm_after_mutation_calculated != cached_norm_before_mutation_calculated);
}


TEST_CASE("cache_invalidation_on_compound_subtract") {
    auto base_vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(base_vector.dimensions() == 10);
    auto count = 0;
    bool all_values_same = std::all_of(base_vector.begin(), base_vector.end(),
                                       [&](auto value) { return value == count++; });
    REQUIRE(all_values_same);
    auto vector_right = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(vector_right.dimensions() == 10);
    count = 0;
    all_values_same = std::all_of(vector_right.begin(), vector_right.end(),
                                  [&](auto value) { return value == count++; });
    REQUIRE(all_values_same);
    // initialised with invalidation
    const auto cached_norm_before_calculation = base_vector.check_cached_norm();
    REQUIRE(cached_norm_before_calculation == -1);
    const auto euclidean_norm_pre_mutation = comp6771::euclidean_norm(base_vector);
    const auto cached_norm_before_mutation_calculated = base_vector.check_cached_norm();
    const auto euclidean_norm_again = comp6771::euclidean_norm(base_vector);
    REQUIRE(cached_norm_before_calculation != cached_norm_before_mutation_calculated);
    REQUIRE(euclidean_norm_pre_mutation == cached_norm_before_mutation_calculated);
    REQUIRE(euclidean_norm_again == cached_norm_before_mutation_calculated);
    base_vector -= vector_right;

    const auto cached_norm_after_mutation = base_vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation == -1);
    const auto euclidean_norm_post_mutation = comp6771::euclidean_norm(base_vector);
    const auto cached_norm_after_mutation_calculated = base_vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation_calculated == euclidean_norm_post_mutation);
    REQUIRE(cached_norm_after_mutation_calculated != cached_norm_before_mutation_calculated);
}

TEST_CASE("cache_invalidation_on_compound_multiplication") {
    auto base_vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(base_vector.dimensions() == 10);
    auto count = 0;
    bool all_values_same = std::all_of(base_vector.begin(), base_vector.end(),
                                       [&](auto value) { return value == count++; });
    REQUIRE(all_values_same);
    auto scale = 5;
    // initialised with invalidation
    const auto cached_norm_before_calculation = base_vector.check_cached_norm();
    REQUIRE(cached_norm_before_calculation == -1);
    const auto euclidean_norm_pre_mutation = comp6771::euclidean_norm(base_vector);
    const auto cached_norm_before_mutation_calculated = base_vector.check_cached_norm();
    const auto euclidean_norm_again = comp6771::euclidean_norm(base_vector);
    REQUIRE(cached_norm_before_calculation != cached_norm_before_mutation_calculated);
    REQUIRE(euclidean_norm_pre_mutation == cached_norm_before_mutation_calculated);
    REQUIRE(euclidean_norm_again == cached_norm_before_mutation_calculated);
    base_vector *= scale;

    const auto cached_norm_after_mutation = base_vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation == -1);
    const auto euclidean_norm_post_mutation = comp6771::euclidean_norm(base_vector);
    const auto cached_norm_after_mutation_calculated = base_vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation_calculated == euclidean_norm_post_mutation);
    REQUIRE(cached_norm_after_mutation_calculated != cached_norm_before_mutation_calculated);
}

TEST_CASE("cache_invalidation_on_compound_division") {
    auto base_vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(base_vector.dimensions() == 10);
    auto count = 0;
    bool all_values_same = std::all_of(base_vector.begin(), base_vector.end(),
                                       [&](auto value) { return value == count++; });
    REQUIRE(all_values_same);
    auto scale = 5;
    REQUIRE(scale == 0);
    // initialised with invalidation
    const auto cached_norm_before_calculation = base_vector.check_cached_norm();
    REQUIRE(cached_norm_before_calculation == -1);
    const auto euclidean_norm_pre_mutation = comp6771::euclidean_norm(base_vector);
    const auto cached_norm_before_mutation_calculated = base_vector.check_cached_norm();
    const auto euclidean_norm_again = comp6771::euclidean_norm(base_vector);
    REQUIRE(cached_norm_before_calculation != cached_norm_before_mutation_calculated);
    REQUIRE(euclidean_norm_pre_mutation == cached_norm_before_mutation_calculated);
    REQUIRE(euclidean_norm_again == cached_norm_before_mutation_calculated);
    base_vector *= scale;

    const auto cached_norm_after_mutation = base_vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation == -1);
    const auto euclidean_norm_post_mutation = comp6771::euclidean_norm(base_vector);
    const auto cached_norm_after_mutation_calculated = base_vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation_calculated == euclidean_norm_post_mutation);
    REQUIRE(cached_norm_after_mutation_calculated != cached_norm_before_mutation_calculated);
}