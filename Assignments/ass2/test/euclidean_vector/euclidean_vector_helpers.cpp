// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/euclidean_vector.hpp"
#include <vector>

namespace comp6771_helpers {
    auto convert_to_vector_manually(comp6771::euclidean_vector vector) -> std::vector<double>{
        auto converted_to_vector = std::vector<double>();
        for(auto i = 0; i < vector.dimensions(); i++){
            converted_to_vector.push_back(vector.at(i));
        }
        return converted_to_vector;
    }
} // namespace comp6771_helpers