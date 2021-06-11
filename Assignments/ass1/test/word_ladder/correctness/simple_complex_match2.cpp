//
// Created by Abanob Tawfik on 11/06/2021.
//

// this is the slightly more complicated test case in comparison to simple_complex_match1 where instead of a simple
// solution of length 1 and 1 hop, there are multiple solutions for the shortest path
// this test will do the example in the specification "work -> play"
// expected output is 12 solutions of length 7 as copied from the specification exactly

//    work fork form foam flam flay play
//    work pork perk peak pean plan play
//    work pork perk peak peat plat play
//    work pork perk pert peat plat play
//    work pork porn pirn pian plan play
//    work pork port pert peat plat play
//    work word wood pood plod ploy play
//    work worm form foam flam flay play
//    work worn porn pirn pian plan play
//    work wort bort boat blat plat play
//    work wort port pert peat plat play
//    work wort wert pert peat plat play

// the same simplified lexicon used in the previous test will also be used in this test

#include "comp6771/word_ladder.hpp"

#include <vector>

#include "catch2/catch.hpp"
#include "comp6771/testing/range/same_length.hpp"
#include "comp6771/testing/range/contain.hpp"
#include "comp6771/testing/range/unique_ladders.hpp"

TEST_CASE("work -> play simple") {
    // testing the naive and optimal solution on a small lexicon that only contains a few possible paths
    auto const english_lexicon = ::word_ladder::read_lexicon("./tiny_lexicon.txt");
    auto const ladders_efficient = ::word_ladder::generate("work", "play", english_lexicon);
    auto const ladders_correct = ::word_ladder_slow::generate_accurate("work", "play", english_lexicon);

    // LADDER VALIDITY CHECK ON CORRECT SOLUTION
    // CHECKS 12 LADDERS OF SIZE 7
    CHECK(std::size(ladders_correct) == 12);
    CHECK(std::size(ladders_correct[0]) == 7);
    CHECK(testing::ladders_same_length(ladders_correct));
    // CHECKS ALL LADDERS ARE UNIQUE
    CHECK(testing::unique_ladders(ladders_correct));
    // CHECK ALL LADDERS ARE SORTED
    CHECK(std::is_sorted(ladders_correct.begin(), ladders_correct.end()));
    // CHECK ALL THE SOLUTIONS ARE IN THE LADDER
    // i used regex to do this, don't reccommend manually inserting each one, but all the solutions for work -> play
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"work", "fork", "form", "foam", "flam", "flay", "play"})));
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"work", "pork", "perk", "peak", "pean", "plan", "play"})));
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"work", "pork", "perk", "peak", "peat", "plat", "play"})));
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"work", "pork", "perk", "pert", "peat", "plat", "play"})));
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"work", "pork", "porn", "pirn", "pian", "plan", "play"})));
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"work", "pork", "port", "pert", "peat", "plat", "play"})));
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"work", "word", "wood", "pood", "plod", "ploy", "play"})));
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"work", "worm", "form", "foam", "flam", "flay", "play"})));
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"work", "worn", "porn", "pirn", "pian", "plan", "play"})));
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"work", "wort", "bort", "boat", "blat", "plat", "play"})));
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"work", "wort", "port", "pert", "peat", "plat", "play"})));
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"work", "wort", "wert", "pert", "peat", "plat", "play"})));

    // now since we checked the correct solution, we just need to see if the optimal solution is the same!
    CHECK(std::equal(ladders_correct.begin(), ladders_correct.end(), ladders_efficient.begin()));
}
