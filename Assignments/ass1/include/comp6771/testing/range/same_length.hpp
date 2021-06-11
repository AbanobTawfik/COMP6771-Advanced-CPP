// my own added in further validity testing
#ifndef AMCXX_TESTING_RANGE_SAME_LENGTH_HPP
#define AMCXX_TESTING_RANGE_SAME_LENGTH_HPP

#include <string>
#include <utility>
#include <vector>

namespace testing {
	inline auto ladders_same_length(const std::vector<std::vector<std::string>> &ladders){
        if(ladders.empty()){
            return true;
        }
        const auto &first_length = ladders[0].size();
        for(const auto &ladder : ladders){
            if(ladder.size() != first_length){
                return false;
            }
        }
        return true;
    }
} // namespace testing

#endif // AMCXX_TESTING_RANGE_SAME_LENGTH_HPP
