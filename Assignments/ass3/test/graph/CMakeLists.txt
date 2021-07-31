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

cxx_test(
        TARGET erase_node
        FILENAME "Modifiers/erase_node.cpp"
)

cxx_test(
        TARGET erase_edges
        FILENAME "Modifiers/erase_edge.cpp"
)

cxx_test(
        TARGET erase_edge_iterator
        FILENAME "Modifiers/erase_edge_iterator.cpp"
)

cxx_test(
        TARGET clear_graph
        FILENAME "Modifiers/clear.cpp"
)

cxx_test(
        TARGET equals
        FILENAME "Utility Functions/equals.cpp"
)

cxx_test(
        TARGET os
        FILENAME "Utility Functions/print.cpp"
)

cxx_test(
        TARGET iterator_begin
        FILENAME "Iterator/begin_end.cpp"
)

cxx_test(
        TARGET iterator_derference
        FILENAME "Iterator/dereference.cpp"
)

cxx_test(
        TARGET iterator_increment
        FILENAME "Iterator/increment.cpp"
)

cxx_test(
        TARGET iterator_decrement
        FILENAME "Iterator/decrement.cpp"
)

cxx_test(
        TARGET connections
        FILENAME "Accessors/connections.cpp"
)

cxx_test(
        TARGET empty
        FILENAME "Accessors/empty.cpp"
)

cxx_test(
        TARGET find
        FILENAME "Accessors/find.cpp"
)

cxx_test(
        TARGET is_connected
        FILENAME "Accessors/is_connected.cpp"
)

cxx_test(
        TARGET is_node
        FILENAME "Accessors/is_node.cpp"
)

cxx_test(
        TARGET nodes
        FILENAME "Accessors/nodes.cpp"
)

cxx_test(
        TARGET weights
        FILENAME "Accessors/weights.cpp"
)

cxx_test(
        TARGET equals_iterator
        FILENAME "Iterator/equals.cpp"
)