// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/word_ladder.hpp"

#include <unordered_set>
#include <fstream>
#include <stdexcept>
#include <string>
#include <iterator>
#include <iostream>
#include <map>

namespace word_ladder {

    auto read_lexicon(std::string const &path) -> std::unordered_set<std::string> {

        auto in = std::ifstream(path.data());
        if (not in) {
            throw std::runtime_error("Unable to open file.");
        }

        std::unordered_set<std::string> lexicon;
        std::copy(std::istream_iterator<std::string>(in), {}, std::inserter(lexicon, lexicon.end()));
        if (in.bad()) {
            std::runtime_error("I/O error while reading");
        }
        if (!in.eof()) {
            std::runtime_error("Didn't reach end of file");
        }
        return lexicon;
    }

}// namespace word_ladder