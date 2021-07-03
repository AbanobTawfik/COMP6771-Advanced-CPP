#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
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
    REQUIRE(scale != 0);
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