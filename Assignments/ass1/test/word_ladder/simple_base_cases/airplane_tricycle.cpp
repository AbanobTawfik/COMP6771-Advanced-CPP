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

// making this simple case where no path exists from the origin to end word, just to make sure no path
// inputs behave correctly.
#include "comp6771/word_ladder.hpp"

#include <string>
#include <vector>
#include "catch2/catch.hpp"
#include "comp6771/testing/range/unique_ladders.hpp"
#include "comp6771/testing/range/contain.hpp"
#include "comp6771/testing/range/same_length.hpp"

TEST_CASE("airplane -> tricycle") {
    auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
    auto const ladders_efficient = ::word_ladder::generate("airplane", "tricycle", english_lexicon);
    auto const ladders_correct = ::word_ladder_slow::generate_accurate("airplane", "tricycle", english_lexicon);

// checks the correct solution for validity
    CHECK(std::size(ladders_correct) == 0);

// now since we checked the correct solution, we just need to see if the optimal solution is the same!
    CHECK(std::equal(ladders_correct.begin(), ladders_correct.end(), ladders_efficient.begin()));
}
