//
//  Copyright UNSW Sydney School of Computer Science and Engineering
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// just to test all examples work correctly given in specification, work->play was used to test correctness, see
// correctness/simple_complex_match2.cpp to see, this is another test case found in the specification where only
// 2 solutions exist from the words awake -> sleep

#include "comp6771/word_ladder.hpp"

#include <string>
#include <vector>
#include "catch2/catch.hpp"
#include "comp6771/testing/range/unique_ladders.hpp"
#include "comp6771/testing/range/contain.hpp"
#include "comp6771/testing/range/same_length.hpp"

TEST_CASE("awake -> sleep") {
    auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
    auto const ladders_efficient = ::word_ladder::generate("awake", "sleep", english_lexicon);
    auto const ladders_correct = ::word_ladder_slow::generate_accurate("awake", "sleep", english_lexicon);

    // checks the correct solution for validity
    CHECK(std::size(ladders_correct) == 2);
    CHECK(testing::unique_ladders(ladders_correct));
    CHECK(testing::ladders_same_length(ladders_correct));
    CHECK(std::is_sorted(ladders_correct.begin(), ladders_correct.end()));
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"awake", "aware", "sware",
                                                                                        "share", "sharn", "shawn",
                                                                                        "shewn", "sheen", "sheep",
                                                                                        "sleep"})));
    CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"awake", "aware", "sware",
                                                                                        "share", "shire", "shirr",
                                                                                        "shier", "sheer", "sheep",
                                                                                        "sleep"})));

    //  now since we checked the correct solution, we just need to see if the optimal solution is the same!
    CHECK(std::equal(ladders_correct.begin(), ladders_correct.end(), ladders_efficient.begin()));
}
