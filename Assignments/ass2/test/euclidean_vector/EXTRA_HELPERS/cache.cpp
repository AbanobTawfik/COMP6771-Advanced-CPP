#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>

// EUCLIDEAN NORM IS ALWAYS >= 0 THIS IS BECAUSE ALL NUMBERS SQUARED ARE POSITIVE, AND TAKING A SUM OF POSITIVE
// NUMBERS AND SQUARE ROOTING THEM WILL ALWAYS GIVE A POSITIVE NUMBER. SO RATHER THAN USING ANOTHER VARIABLE TO KEEP
// TRACK OF THE CACHE STATUS (INVALID/VALID) I CAN USE -1 WHICH IS AN IMPOSSIBLE VALUE TO HAVE, SO -1 WILL BE
// INVALID CACHE VALUE, AND ALL POSITIVE VALUES >= 0 ARE VALID CACHE

// here we are testing the extra functionality of caching, not core to the actual class but provides huge benefits
// to check caching we need to do the following
// check the caching is stored correctly, its worth noting i have timed the results of caching, its 100 nanoseconds
// to retrieve from cache, and over 10 million nanoseconds to compute the euclidean norm of a vector length 100000 on
// my computer.

// first test cache is storing the correct value of euclidean norm, this is done by calling check cached norm before
// and after calling euclidean norm, before it is invalid (-1) and after it is the value of euclidean norm

// remainder of test checks the cache invalidaiton works correctly when the vector is mutated or iniitialised
// this means we check cache invalidation for the following operations
// 1. initialisation, cache is invalid on new objects
// 2. before computing euclidean norm (we only compute when we need to)
// 3. using at operation to MODIFY THE VECTOR
// 4. using subscript operation to MODIFY THE VECTOR
// 5. using compound add
// 6. using compound subtract
// 7. using compound multiplication IF THE SCALE IS NOT EXACTLY 1
// 8. using compound division IF THE SCALE IS NOT EXACTLY 1

// to check cache invalidaiton works correctly, we will see whats stored inside the cache AFTER modification, we will
// then recompute the euclidean norm, and want to see whats now stored in the cache, to make sure it updated the cache
// correctly and clears the cache correctly on modifications!

TEST_CASE("cache_storing_correctly") {
    const auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == Approx(0).margin(0.000001));
    // initialised with invalidation
    REQUIRE(vector.check_cached_norm() == Approx(-1).margin(0.000001));
    const auto euclidean_norm = comp6771::euclidean_norm(vector);
    REQUIRE(euclidean_norm == 0);
    // O(1)
    const auto cached_norm = vector.check_cached_norm();
    REQUIRE(cached_norm == Approx(euclidean_norm).margin(0.000001));
}

TEST_CASE("cache_invalidation_on_initialisation") {
    const auto vector = comp6771::euclidean_vector();
    REQUIRE(vector.dimensions() == 1);
    REQUIRE(vector[0] == Approx(0).margin(0.000001));
    // initialised with invalidation
    const auto cached_norm = vector.check_cached_norm();
    REQUIRE(cached_norm == Approx(-1).margin(0.000001));
}

TEST_CASE("cache_invalidation_before_calling_norm") {
    const auto vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(vector.dimensions() == 10);
    auto count = 0;
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == Approx(count++).margin(0.000001); }));
    // initialised with invalidation
    const auto cached_norm_before_calling_norm = vector.check_cached_norm();
    REQUIRE(cached_norm_before_calling_norm == Approx(-1).margin(0.000001));
    const auto euclidean_norm = comp6771::euclidean_norm(vector);
    const auto cached_norm_before_mutation_calculated = vector.check_cached_norm();
    REQUIRE(cached_norm_before_calling_norm != Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    REQUIRE(euclidean_norm == Approx(cached_norm_before_mutation_calculated).margin(0.000001));
}

TEST_CASE("cache_invalidation_on_at_modify") {
    auto vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const auto index_to_change = 3;
    REQUIRE(index_to_change >= 0);
    REQUIRE(index_to_change < vector.dimensions());
    const auto value_to_change = 69;
    REQUIRE(vector.dimensions() == 10);
    auto count = 0;
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == Approx(count++).margin(0.000001); }));
    // initialised with invalidation
    const auto cached_norm_before_calculation = vector.check_cached_norm();
    REQUIRE(cached_norm_before_calculation == Approx(-1).margin(0.000001));
    const auto euclidean_norm_pre_mutation = comp6771::euclidean_norm(vector);
    const auto cached_norm_before_mutation_calculated = vector.check_cached_norm();
    const auto euclidean_norm_again = comp6771::euclidean_norm(vector);
    REQUIRE(cached_norm_before_calculation != Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    REQUIRE(euclidean_norm_pre_mutation == Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    REQUIRE(euclidean_norm_again == Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    vector.at(index_to_change) = value_to_change;

    const auto cached_norm_after_mutation = vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation == Approx(-1).margin(0.000001));
    const auto euclidean_norm_post_mutation = comp6771::euclidean_norm(vector);
    const auto cached_norm_after_mutation_calculated = vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation_calculated == Approx(euclidean_norm_post_mutation).margin(0.000001));
    REQUIRE(cached_norm_after_mutation_calculated != Approx(cached_norm_before_mutation_calculated).margin(0.000001));
}

TEST_CASE("cache_invalidation_on_subscript_modify") {
    auto vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const auto index_to_change = 3;
    REQUIRE(index_to_change >= 0);
    REQUIRE(index_to_change < vector.dimensions());
    const auto value_to_change = 69;
    REQUIRE(vector.dimensions() == 10);
    auto count = 0;
    REQUIRE(std::all_of(vector.begin(), vector.end(),
                        [&](auto value) { return value == Approx(count++).margin(0.000001); }));
    // initialised with invalidation
    const auto cached_norm_before_calculation = vector.check_cached_norm();
    REQUIRE(cached_norm_before_calculation == Approx(-1).margin(0.000001));
    const auto euclidean_norm_pre_mutation = comp6771::euclidean_norm(vector);
    const auto cached_norm_before_mutation_calculated = vector.check_cached_norm();
    const auto euclidean_norm_again = comp6771::euclidean_norm(vector);
    REQUIRE(cached_norm_before_calculation != Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    REQUIRE(euclidean_norm_pre_mutation == Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    REQUIRE(euclidean_norm_again == Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    vector[index_to_change] = value_to_change;

    const auto cached_norm_after_mutation = vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation == Approx(-1).margin(0.000001));
    const auto euclidean_norm_post_mutation = comp6771::euclidean_norm(vector);
    const auto cached_norm_after_mutation_calculated = vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation_calculated == Approx(euclidean_norm_post_mutation).margin(0.000001));
    REQUIRE(cached_norm_after_mutation_calculated != Approx(cached_norm_before_mutation_calculated).margin(0.000001));
}


TEST_CASE("cache_invalidation_on_compound_add") {
    auto base_vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(static_cast<size_t>(base_vector.dimensions()) == 10);
    auto count = 0;
    REQUIRE(std::all_of(base_vector.begin(), base_vector.end(),
                        [&](auto value) { return value == Approx(count++).margin(0.000001); }));
    auto vector_right = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(static_cast<size_t>(vector_right.dimensions()) == 10);
    count = 0;
    REQUIRE(std::all_of(vector_right.begin(), vector_right.end(),
                        [&](auto value) { return value == Approx(count++).margin(0.000001); }));
    // initialised with invalidation
    const auto cached_norm_before_calculation = base_vector.check_cached_norm();
    REQUIRE(cached_norm_before_calculation == Approx(-1).margin(0.000001));
    const auto euclidean_norm_pre_mutation = comp6771::euclidean_norm(base_vector);
    const auto cached_norm_before_mutation_calculated = base_vector.check_cached_norm();
    const auto euclidean_norm_again = comp6771::euclidean_norm(base_vector);
    REQUIRE(cached_norm_before_calculation != Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    REQUIRE(euclidean_norm_pre_mutation == Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    REQUIRE(euclidean_norm_again == Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    base_vector += vector_right;

    const auto cached_norm_after_mutation = base_vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation == Approx(-1).margin(0.000001));
    const auto euclidean_norm_post_mutation = comp6771::euclidean_norm(base_vector);
    const auto cached_norm_after_mutation_calculated = base_vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation_calculated == Approx(euclidean_norm_post_mutation).margin(0.000001));
    REQUIRE(cached_norm_after_mutation_calculated != Approx(cached_norm_before_mutation_calculated).margin(0.000001));
}


TEST_CASE("cache_invalidation_on_compound_subtract") {
    auto base_vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(static_cast<size_t>(base_vector.dimensions()) == 10);
    auto count = 0;
    REQUIRE(std::all_of(base_vector.begin(), base_vector.end(),
                                       [&](auto value) { return value == Approx(count++).margin(0.000001); }));
    auto vector_right = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(vector_right.dimensions() == 10);
    count = 0;
    REQUIRE(std::all_of(vector_right.begin(), vector_right.end(),
                                  [&](auto value) { return value == Approx(count++).margin(0.000001); }));
    // initialised with invalidation
    const auto cached_norm_before_calculation = base_vector.check_cached_norm();
    REQUIRE(cached_norm_before_calculation == Approx(-1).margin(0.000001));
    const auto euclidean_norm_pre_mutation = comp6771::euclidean_norm(base_vector);
    const auto cached_norm_before_mutation_calculated = base_vector.check_cached_norm();
    const auto euclidean_norm_again = comp6771::euclidean_norm(base_vector);
    REQUIRE(cached_norm_before_calculation != Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    REQUIRE(euclidean_norm_pre_mutation == Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    REQUIRE(euclidean_norm_again == Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    base_vector -= vector_right;

    const auto cached_norm_after_mutation = base_vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation == Approx(-1).margin(0.000001));
    const auto euclidean_norm_post_mutation = comp6771::euclidean_norm(base_vector);
    const auto cached_norm_after_mutation_calculated = base_vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation_calculated == Approx(euclidean_norm_post_mutation).margin(0.000001));
    REQUIRE(cached_norm_after_mutation_calculated != Approx(cached_norm_before_mutation_calculated).margin(0.000001));
}

TEST_CASE("cache_invalidation_on_compound_multiplication") {
    auto base_vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(static_cast<size_t>(base_vector.dimensions()) == 10);
    auto count = 0;
    REQUIRE(std::all_of(base_vector.begin(), base_vector.end(),
                                       [&](auto value) { return value == Approx(count++).margin(0.000001); }));
    auto scale = 5;
    // initialised with invalidation
    const auto cached_norm_before_calculation = base_vector.check_cached_norm();
    REQUIRE(cached_norm_before_calculation == Approx(-1).margin(0.000001));
    const auto euclidean_norm_pre_mutation = comp6771::euclidean_norm(base_vector);
    const auto cached_norm_before_mutation_calculated = base_vector.check_cached_norm();
    const auto euclidean_norm_again = comp6771::euclidean_norm(base_vector);
    REQUIRE(cached_norm_before_calculation != Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    REQUIRE(euclidean_norm_pre_mutation == Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    REQUIRE(euclidean_norm_again == Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    base_vector *= scale;

    const auto cached_norm_after_mutation = base_vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation == -1);
    const auto euclidean_norm_post_mutation = comp6771::euclidean_norm(base_vector);
    const auto cached_norm_after_mutation_calculated = base_vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation_calculated == Approx(euclidean_norm_post_mutation).margin(0.000001));
    REQUIRE(cached_norm_after_mutation_calculated != Approx(cached_norm_before_mutation_calculated).margin(0.000001));
}

TEST_CASE("cache_invalidation_on_compound_division") {
    auto base_vector = comp6771::euclidean_vector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    REQUIRE(static_cast<size_t>(base_vector.dimensions()) == 10);
    auto count = 0;
    REQUIRE(std::all_of(base_vector.begin(), base_vector.end(),
                                       [&](auto value) { return value == Approx(count++).margin(0.000001); }));
    auto scale = 5;
    REQUIRE(scale != 0);
    // initialised with invalidation
    const auto cached_norm_before_calculation = base_vector.check_cached_norm();
    REQUIRE(cached_norm_before_calculation == Approx(-1).margin(0.000001));
    const auto euclidean_norm_pre_mutation = comp6771::euclidean_norm(base_vector);
    const auto cached_norm_before_mutation_calculated = base_vector.check_cached_norm();
    const auto euclidean_norm_again = comp6771::euclidean_norm(base_vector);
    REQUIRE(cached_norm_before_calculation != Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    REQUIRE(euclidean_norm_pre_mutation == Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    REQUIRE(euclidean_norm_again == Approx(cached_norm_before_mutation_calculated).margin(0.000001));
    base_vector *= scale;

    const auto cached_norm_after_mutation = base_vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation == Approx(-1).margin(0.000001));
    const auto euclidean_norm_post_mutation = comp6771::euclidean_norm(base_vector);
    const auto cached_norm_after_mutation_calculated = base_vector.check_cached_norm();
    REQUIRE(cached_norm_after_mutation_calculated == Approx(euclidean_norm_post_mutation).margin(0.000001));
    REQUIRE(cached_norm_after_mutation_calculated != Approx(cached_norm_before_mutation_calculated).margin(0.000001));
}