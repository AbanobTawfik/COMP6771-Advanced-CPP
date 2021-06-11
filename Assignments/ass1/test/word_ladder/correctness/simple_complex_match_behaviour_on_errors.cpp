//
// Created by Abanob Tawfik on 11/06/2021.
//

// this test will simply be used to check if the simple solution behaves the same as the optimised solution
// when handling an error case, in this case having special characters. it is worth noting this code can find all
// paths from wo_k -> play if needed by a simple change to the generate's initial check.

// the same simplified lexicon used in the previous test will also be used in this test

#include "comp6771/word_ladder.hpp"

#include <vector>

#include "catch2/catch.hpp"


TEST_CASE("wo_k -> play simple") {
    // testing the naive and optimal solution on a small lexicon that only contains a few possible paths
    // invalid inputs should return no ladders since the words are not in the lexicon
    auto const english_lexicon = ::word_ladder::read_lexicon("./tiny_lexicon.txt");
    auto const ladders_efficient = ::word_ladder::generate("wo_k", "play", english_lexicon);
    auto const ladders_correct = ::word_ladder_slow::generate_accurate("wo_k", "play", english_lexicon);

    // LADDER VALIDITY CHECK ON CORRECT SOLUTION
    // CHECKS 0 ladders
    CHECK(std::size(ladders_correct) == 0);

    // now since we checked the correct solution, we just need to see if the optimal solution is the same!
    CHECK(std::equal(ladders_correct.begin(), ladders_correct.end(), ladders_efficient.begin()));
}
