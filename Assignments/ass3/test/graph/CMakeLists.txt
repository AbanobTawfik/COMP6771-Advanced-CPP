cxx_test(
        TARGET graph_test1
        FILENAME "graph_test1.cpp"
)

cxx_test(
        TARGET default_constructor
        FILENAME "Constructors/default_constructor.cpp"
)

cxx_test(
        TARGET initialiser_list_constructor
        FILENAME "Constructors/initialiser_list_constructor.cpp"
)

cxx_test(
        TARGET input_iterator_contructor
        FILENAME "Constructors/input_iterator_constructor.cpp"
)

cxx_test(
        TARGET move_contructor
        FILENAME "Constructors/move_constructor.cpp"
)

cxx_test(
        TARGET move_equals
        FILENAME "Constructors/move_equals.cpp"
)

cxx_test(
        TARGET copy_constructor
        FILENAME "Constructors/copy_constructor.cpp"
)

cxx_test(
        TARGET copy_equals
        FILENAME "Constructors/copy_equals.cpp"
)

cxx_test(
        TARGET insert_node
        FILENAME "Modifiers/insert_node.cpp"
)

cxx_test(
        TARGET insert_edge
        FILENAME "Modifiers/insert_edge.cpp"
)

cxx_test(
        TARGET replace_node
        FILENAME "Modifiers/replace_node.cpp"
)

cxx_test(
        TARGET merge_replace_node
        FILENAME "Modifiers/merge_replace_node.cpp"
)