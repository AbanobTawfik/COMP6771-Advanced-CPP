cxx_test(
   TARGET euclidean_vector_test1
   FILENAME "euclidean_vector_test1.cpp"
   LINK euclidean_vector
)

cxx_test(
        TARGET default_constructor
        FILENAME "Constructors/default_constructor.cpp"
        LINK euclidean_vector
)

cxx_test(
        TARGET size_constructor
        FILENAME "Constructors/size_constructor.cpp"
        LINK euclidean_vector
)

cxx_test(
        TARGET size_initial_constructor
        FILENAME "Constructors/size_initial_value_constructor.cpp"
        LINK euclidean_vector
)

cxx_test(
        TARGET stdvector_constructor
        FILENAME "Constructors/stdvector_constructor.cpp"
        LINK euclidean_vector
)

cxx_test(
        TARGET initialiser_list_constructor
        FILENAME "Constructors/initialiser_list_constructor.cpp"
        LINK euclidean_vector
)

cxx_test(
        TARGET move_constructor
        FILENAME "Constructors/move_constructor.cpp"
        LINK euclidean_vector
)

cxx_test(
        TARGET copy_constructor
        FILENAME "Constructors/copy_constructor.cpp"
        LINK euclidean_vector
)

cxx_test(
        TARGET copy_assignment
        FILENAME "Operations/copy_asignment.cpp"
        LINK euclidean_vector
)

cxx_test(
        TARGET move_assignment
        FILENAME "Operations/move_assignment.cpp"
        LINK euclidean_vector
)

cxx_test(
        TARGET subscripts
        FILENAME "Operations/subscript.cpp"
        LINK euclidean_vector
)

cxx_test(
        TARGET unary
        FILENAME "Operations/unary.cpp"
        LINK euclidean_vector
)

cxx_test(
        TARGET negation
        FILENAME "Operations/negation.cpp"
        LINK euclidean_vector
)