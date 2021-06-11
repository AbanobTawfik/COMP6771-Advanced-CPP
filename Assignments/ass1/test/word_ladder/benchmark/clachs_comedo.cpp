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

// this test will check more difficult word ladders, this case hammer -> thumper is a word ladder of length 26, with
// 342 solutions. the correctness of the output has been validated in previous tests using the naive solution, so we
// just need to check the efficient solution matches

#include "comp6771/word_ladder.hpp"

#include <string>
#include <vector>

#include "catch2/catch.hpp"
#include "comp6771/testing/range/same_length.hpp"
#include "comp6771/testing/range/unique_ladders.hpp"

TEST_CASE("clachs -> comedo") {
auto const english_lexicon = ::word_ladder::read_lexicon("./english.txt");
auto const ladders_efficient = ::word_ladder::generate("clachs", "comedo", english_lexicon);
auto const ladders_correct = ::word_ladder_slow::generate_accurate("clachs", "comedo", english_lexicon);

CHECK(std::size(ladders_correct) == 20);
CHECK(ladders_correct[0].size() == 22);
CHECK(testing::ladders_same_length(ladders_correct));
CHECK(testing::unique_ladders(ladders_correct));
CHECK(std::is_sorted(ladders_correct.begin(), ladders_correct.begin()));

CHECK(std::equal(ladders_correct.begin(), ladders_correct.end(), ladders_efficient.begin()));
}
