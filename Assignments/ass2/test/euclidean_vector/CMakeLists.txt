cxx_library(
        TARGET "euclidean_vector_helpers"
        FILENAME "euclidean_vector_helpers.cpp"
)

cxx_test(
        TARGET euclidean_vector_test1
        FILENAME "euclidean_vector_test1.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET default_constructor
        FILENAME "Constructors/default_constructor.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET size_constructor
        FILENAME "Constructors/size_constructor.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET size_initial_constructor
        FILENAME "Constructors/size_initial_value_constructor.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET stdvector_constructor
        FILENAME "Constructors/stdvector_constructor.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET initialiser_list_constructor
        FILENAME "Constructors/initialiser_list_constructor.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET move_constructor
        FILENAME "Constructors/move_constructor.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET copy_constructor
        FILENAME "Constructors/copy_constructor.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET copy_assignment
        FILENAME "Operations/copy_asignment.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET move_assignment
        FILENAME "Operations/move_assignment.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET subscripts
        FILENAME "Operations/subscript.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET unary
        FILENAME "Operations/unary.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET negation
        FILENAME "Operations/negation.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET compound_addition
        FILENAME "Operations/compound_addition.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET compound_subtraction
        FILENAME "Operations/compound_subtraction.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET compound_multiplication
        FILENAME "Operations/compound_multiplication.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET compound_divison
        FILENAME "Operations/compound_division.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET list_cast
        FILENAME "Operations/list_cast.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET vector_cast
        FILENAME "Operations/vector_cast.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET at
        FILENAME "member_functions/at.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET dimensions
        FILENAME "member_functions/dimensions.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET equals
        FILENAME "Friends/equals.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET not_equals
        FILENAME "Friends/not_equals.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET addition
        FILENAME "Friends/addition.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET subtraction
        FILENAME "Friends/subtraction.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET multiplication
        FILENAME "Friends/multiplication.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET division
        FILENAME "Friends/division.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET ostream
        FILENAME "Friends/ostream.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET euclidean_norm
        FILENAME "utility_functions/euclidean_norm.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET unit
        FILENAME "utility_functions/unit.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)

cxx_test(
        TARGET dot
        FILENAME "utility_functions/dot.cpp"
        LINK euclidean_vector euclidean_vector_helpers
)