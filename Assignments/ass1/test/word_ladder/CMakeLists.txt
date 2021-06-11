configure_file("english.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file("tiny_lexicon.txt" ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

cxx_test(
        TARGET word_ladder_test1
        FILENAME simple_base_cases/at_it.cpp
        LINK word_ladder lexicon Catch2::Catch2 test_main word_ladder_slow
)

cxx_test(
        TARGET word_ladder_test_benchmark
        FILENAME benchmark/atlases_cabaret.cpp
        LINK word_ladder lexicon Catch2::Catch2 test_main word_ladder_slow
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

cxx_test(
        TARGET simple_complex_match_behaviour_on_errors
        FILENAME correctness/simple_complex_match_behaviour_on_errors.cpp
        LINK word_ladder lexicon Catch2::Catch2 test_main word_ladder_slow
)

cxx_test(
        TARGET no_path_different_lengths
        FILENAME no_path_cases/different_lengths.cpp
        LINK word_ladder lexicon Catch2::Catch2 test_main word_ladder_slow
)

cxx_test(
        TARGET no_path_not_in_lexicon
        FILENAME no_path_cases/not_in_lexicon.cpp
        LINK word_ladder lexicon Catch2::Catch2 test_main word_ladder_slow
)

cxx_test(
        TARGET no_path_special_characters
        FILENAME no_path_cases/special_characters.cpp
        LINK word_ladder lexicon Catch2::Catch2 test_main word_ladder_slow
)

cxx_test(
        TARGET no_path_whitespaces
        FILENAME no_path_cases/word_ladder_test_whitespace.cpp
        LINK word_ladder lexicon Catch2::Catch2 test_main word_ladder_slow
)

cxx_test(
        TARGET no_valid_path
        FILENAME no_path_cases/no_valid_paths.cpp
        LINK word_ladder lexicon Catch2::Catch2 test_main word_ladder_slow
)

cxx_test(
        TARGET awake_sleep
        FILENAME simple_base_cases/awake_sleep.cpp
        LINK word_ladder lexicon Catch2::Catch2 test_main word_ladder_slow
)

cxx_test(
        TARGET airplane_tricycle
        FILENAME simple_base_cases/airplane_tricycle.cpp
        LINK word_ladder lexicon Catch2::Catch2 test_main word_ladder_slow
)

cxx_test(
        TARGET hammers_thumper
        FILENAME benchmark/hammers_thumper.cpp
        LINK word_ladder lexicon Catch2::Catch2 test_main word_ladder_slow
)

cxx_test(
        TARGET clachs_coemdo
        FILENAME benchmark/clachs_comedo.cpp
        LINK word_ladder lexicon Catch2::Catch2 test_main word_ladder_slow
)