#include "comp6771/word_ladder.hpp"
#include <iostream>

//  Please note: it's not good practice to test your code via a main function that does
//  printing. Instead, you should be using your test folder. This file should only really
//  be used for more "primitive" debugging as we know that working solely with test
//  frameworks might be overwhelming for some.

auto main() -> int {
//    auto start = std::chrono::high_resolution_clock::now();
    auto const english_lexicon = word_ladder::read_lexicon("../test/word_ladder/english.txt");
//    auto const ladders = word_ladder_slow::generate_accurate("work", "play", english_lexicon);
    auto const ladders = ::word_ladder::generate("clachs", "comedo", english_lexicon);
//    auto const ladders = ::word_ladder::generate("hammers", "thumper", english_lexicon);
//    auto end = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    for(const auto &i : ladders){
        for(const auto &node : i){
            std::cout << node << " ";
        }
        std::cout <<  std::endl;
    }
//    std::cout << duration.count() << std::endl;
    std::cout << ladders.size() << std::endl;
    std::cout << ladders[0].size() << std::endl;
    return 0;
}
