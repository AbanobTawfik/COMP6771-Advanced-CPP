//
// Created by Abanob Tawfik on 11/06/2021.
//

// this test is designed to check the correctness of the more optimal search by comparing to a naive, guaranteed
// to work method. Since my optimised search uses a modification of a bidirectional BFS and a modification of DFS.
// The naive method simply uses a unidirectional BFS and the same modification of DFS.

// this is the simplest of the simplest test case to check correctness, at -> it, a simple 1 letter change, 1 ladder
// of length 1.

// this test will be done on a subset of the original lexicon, where only a few 4 letter words and 2 letter words exist
// and multiple paths to each solution are possible. This is done because a large lexicon is not required to see
// correct behaviour

// This test will compare the outcome of generating all word ladders from at -> it, and then will check the validity
// of the ladders and then compare the ladders from the naive and more optimised method.

// This test is important to make sure that the more optimised search still behaves correctly.

#include "comp6771/word_ladder.hpp"

#include <vector>

#include "catch2/catch.hpp"
#include "comp6771/testing/range/same_length.hpp"
#include "comp6771/testing/range/contain.hpp"
#include "comp6771/testing/range/unique_ladders.hpp"

TEST_CASE("at -> it simple") {
    // testing the naive and optimal solution on a small lexicon that only contains a few possible paths
    auto const english_lexicon = ::word_ladder::read_lexicon("./tiny_lexicon.txt");
    auto const ladders_efficient = ::word_ladder::generate("at", "it", english_lexicon);
    // NOT MADE CONST ON PURPOSE TO TEST THE TEST METHOD ITSELF
    auto ladders_correct = ::word_ladder_slow::generate_accurate("at", "it", english_lexicon);

    // LADDER VALIDITY CHECK ON CORRECT SOLUTION
    CHECK(std::size(ladders_efficient) == 1);
    CHECK(testing::ladders_same_length(ladders_correct));
    CHECK(testing::unique_ladders(ladders_correct));
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"at", "it"})));
    // PUSHIND IN A DUPLICATE TO TEST THE UNIQUE_LADDERS WORKS CORRECTLY
    ladders_correct.push_back({"at", "it"});
    CHECK(not testing::unique_ladders(ladders_correct));
    // removing duplicate now and checking
    ladders_correct.pop_back();
    CHECK(testing::unique_ladders(ladders_correct));
    CHECK(std::is_sorted(ladders_correct.begin(), ladders_correct.end()));

    // now since we checked the correct solution, we just need to see if the optimal solution is the same!
    CHECK(std::equal(ladders_correct.begin(), ladders_correct.end(), ladders_efficient.begin()));
}
