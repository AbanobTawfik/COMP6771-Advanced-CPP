cxx_library(
        TARGET word_ladder
        FILENAME word_ladder.cpp
)

cxx_library(
        TARGET word_ladder_slow
        FILENAME naive_testing_word_ladder.cpp
)

cxx_library(
        TARGET lexicon
        FILENAME lexicon.cpp
)

cxx_executable(
        TARGET debugging_main
        FILENAME debugging_main.cpp
        LINK word_ladder lexicon word_ladder_slow
)
