configure_file("english.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("tiny_lexicon.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

cxx_test(
        TARGET word_ladder_test1
        FILENAME simple_base_case/at_it.cpp
        LINK word_ladder lexicon Catch2::Catch2 test_main
)

cxx_test(
        TARGET word_ladder_test_benchmark
        FILENAME benchmark/atlases_cabaret.cpp
        LINK word_ladder lexicon Catch2::Catch2 test_main
)

cxx_test(
        TARGET simple_complex_match1
        FILENAME correctness/simple_complex_match1.cpp
        LINK word_ladder lexicon Catch2::Catch2 test_main word_ladder_slow
)


cxx_test(
        TARGET simple_complex_match2
        FILENAME correctness/simple_complex_match2.cpp
        LINK word_ladder lexicon Catch2::Catch2 test_main word_ladder_slow
)

