//
// Created by Abanob Tawfik on 11/06/2021.
//

// These tests are designed to check the behaviour on invalid input, or finding paths that are unable to be
// completed. The aim is to use our simple model to validate output, and then compare the validated simple model
// to the more complex and efficient model. It is very important to handle error cases in testing as testing
// correct input is only partially the cases we handle.

// this test is slightly complicated but tests two different aspects of the word ladder code. first the custom
// build lexicon has been inserted with words such as the path to be constructed is missing exactly 1 hop. This means
// that before any modifications the search should result in nothing.

// Once this behaviour has been observed, 2 different linking words that fill in the missing hop are added to the lexicon
// and the search is reprocessed. This is expected to result in 2 ladders in the solution.

// This test also compared to a known working naive solution that uses a simple 1 way bfs and DFS

#include "comp6771/word_ladder.hpp"

#include <vector>
#include "catch2/catch.hpp"

#include "comp6771/testing/range/same_length.hpp"
#include "comp6771/testing/range/contain.hpp"
#include "comp6771/testing/range/unique_ladders.hpp"

TEST_CASE("no valid paths") {
    // testing the naive and optimal solution on a small lexicon that only contains a few possible paths
    auto english_lexicon = ::word_ladder::read_lexicon("./tiny_lexicon.txt");
    auto ladders_efficient = ::word_ladder::generate("onewordhop", "twowordhop", english_lexicon);
    auto ladders_correct = ::word_ladder_slow::generate_accurate("onewordhop", "twowordhop", english_lexicon);
    //  LADDER VALIDITY CHECK ON CORRECT SOLUTION
    //  CHECKS 0 ladders
    CHECK(std::size(ladders_correct) == 0);

    //  check the optimal and correct solution match exactly
    CHECK(std::equal(ladders_correct.begin(), ladders_correct.end(), ladders_efficient.begin()));

    // now check when we add missing path links that it can find a solution that was exactly mapped out in the custom
    // lexicon
    english_lexicon.insert("twewordhop");
    english_lexicon.insert("twowordhep");
    ladders_efficient = ::word_ladder::generate("onewordhop", "twowordhop", english_lexicon);
    ladders_correct = ::word_ladder_slow::generate_accurate("onewordhop", "twowordhop", english_lexicon);
    CHECK(std::size(ladders_correct) == 2);
    CHECK(testing::unique_ladders(ladders_correct));
    CHECK(testing::ladders_same_length(ladders_correct));
    CHECK(std::is_sorted(ladders_correct.begin(), ladders_correct.end()));
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"onewordhop", "onewordhep", "onewerdhep", "tnewerdhep", "twewerdhep", "twewordhep", "twewordhop","twowordhop"})));
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"onewordhop", "onewordhep", "onewerdhep", "tnewerdhep", "twewerdhep", "twewordhep", "twowordhep","twowordhop"})));
    CHECK(std::equal(ladders_correct.begin(), ladders_correct.end(), ladders_efficient.begin()));
}
