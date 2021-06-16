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

// making this test more robust by checking exactly expected output for a
// extremely simple base case with 1 letter change, expecting 1 path
#include "comp6771/word_ladder.hpp"

#include <string>
#include <vector>
#include "catch2/catch.hpp"
#include "comp6771/testing/range/unique_ladders.hpp"
#include "comp6771/testing/range/contain.hpp"
#include "comp6771/testing/range/same_length.hpp"

TEST_CASE("at -> it") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
    auto const ladders_efficient = ::word_ladder::generate("at", "it", english_lexicon);
    auto const ladders_correct = ::word_ladder_slow::generate_accurate("at", "it", english_lexicon);

    // checks the correct solution for validity
    CHECK(std::size(ladders_correct) == 1);
    CHECK(testing::unique_ladders(ladders_correct));
    CHECK(testing::ladders_same_length(ladders_correct));
    CHECK(std::is_sorted(ladders_correct.begin(), ladders_correct.end()));
	CHECK(std::any_of(ladders_correct.begin(), ladders_correct.end(), testing::contain({"at", "it"})));

    //  now since we checked the correct solution, we just need to see if the optimal solution is the same!
    CHECK(std::equal(ladders_correct.begin(), ladders_correct.end(), ladders_efficient.begin()));
}
