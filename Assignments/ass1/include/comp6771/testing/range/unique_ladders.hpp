// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef AMCXX_TESTING_RANGE_UNIQUE_LADDERS_HPP
#define AMCXX_TESTING_RANGE_UNIQUE_LADDERS_HPP

#include <string>
#include <vector>

#include "range/v3/iterator.hpp"
#include "range/v3/view/unique.hpp"

namespace testing {
    inline auto unique_ladders(std::vector<std::vector<std::string>> const &ladders) -> bool {
        for (std::vector<std::string>::size_type i = 0; i < ladders.size(); i++) {
            const auto current_ladder = ladders[i];
            for (std::vector<std::string>::size_type j = 0; j < ladders.size(); j++) {
                if (i == j) {
                    continue;
                }
                auto count = 0;
                for (std::vector<std::string>::size_type k = 0; k < current_ladder.size(); k++){
                    if(ladders[i][k] == ladders[j][k]){
                        count++;
                    }
                }
                if(count == current_ladder.size()){
                    return false;
                }
            }
        }
        return true;
    }
} // namespace testing

#endif // AMCXX_TESTING_RANGE_UNIQUE_LADDERS_HPP
