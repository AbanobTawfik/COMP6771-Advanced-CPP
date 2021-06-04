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
#include <unordered_map>
#include <map>

namespace word_ladder {
    auto get_neighbours(std::string word,
                        std::unordered_map<std::string, std::unordered_set<std::string>> neighbour_map) -> std::unordered_set<std::string>;

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

    auto generate_all_1nn(
            std::unordered_set<std::string> lexicon, int length) -> std::unordered_map<std::string, std::unordered_set<std::string>> {
        std::unordered_map<std::string, std::unordered_set<std::string>> all_1nn;
        for (auto word : lexicon) {
            if(word.size() != length){
                continue;
            }
            for (int i = 0; i < word.length(); i++) {
                auto cloned_word = word;
                cloned_word[i] = '_';
                all_1nn[cloned_word].insert(word);
            }
        }
        return all_1nn;
    }

}// namespace word_ladder