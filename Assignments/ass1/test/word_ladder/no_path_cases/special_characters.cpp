//
// Created by Abanob Tawfik on 11/06/2021.
//

// These tests are designed to check the behaviour on invalid input, or finding paths that are unable to be
// completed. The aim is to use our simple model to validate output, and then compare the validated simple model
// to the more complex and efficient model. It is very important to handle error cases in testing as testing
// correct input is only partially the cases we handle.

// this test simply tries to find word ladders from two words that contain special characters, this behaviour should
// result in no ladders as this is impossible behaviour.

#include "comp6771/word_ladder.hpp"

#include <vector>

#include "catch2/catch.hpp"


TEST_CASE("special characters") {
// testing the naive and optimal solution on a small lexicon that only contains a few possible paths
auto const english_lexicon = ::word_ladder::read_lexicon("./english.txt");
auto const ladders_efficient = ::word_ladder::generate("w()rd", "w[]rd", english_lexicon);
// NOT MADE CONST ON PURPOSE TO TEST THE TEST METHOD ITSELF
auto ladders_correct = ::word_ladder_slow::generate_accurate("w()rd", "w[]rd", english_lexicon);

//  LADDER VALIDITY CHECK ON CORRECT SOLUTION
//  CHECKS 0 ladders
CHECK(std::size(ladders_correct) == 0);

//  now since we checked the correct solution, we just need to see if the optimal solution is the same!
CHECK(std::equal(ladders_correct.begin(), ladders_correct.end(), ladders_efficient.begin()));
}
