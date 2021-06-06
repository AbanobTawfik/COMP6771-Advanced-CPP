#include "comp6771/word_ladder.hpp"
//#include "../include/comp6771/word_ladder.hpp"
#include <iostream>
#include <chrono>

// Please note: it's not good practice to test your code via a main function that does
//  printing. Instead, you should be using your test folder. This file should only really
//  be used for more "primitive" debugging as we know that working solely with test
//  frameworks might be overwhelming for some.

auto main() -> int {
    auto start = std::chrono::high_resolution_clock::now();
    auto const english_lexicon = word_ladder::read_lexicon("../test/word_ladder/english.txt");
//	auto const ladders = word_ladder::generate("play", "work", english_lexicon);
    auto const ladders = ::word_ladder::generate("atlases", "cabaret", english_lexicon);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << duration.count() << std::endl;
	// debug here
}
