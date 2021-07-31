# <center> Test Rationale </center>
In my testing I had created one file for each function/constructor required for the assignment. Inside each file there
is atleast one test case to check the behaviour of the function works EXACTLY AS SPECIFIED, with potentially more
depending on all the types of behaviour the function can have with different inputs. In order to prevent a massive block
of comment throughout 20+ files, it was easier to create all the rationale for each test here. The table of content below
provides a quick and easy way to navigate to the rationale behind the test for that function. To find the test function, simply navigate through the graph
directory and search in the sub folders, as each file has been organised accordingly.

1. [Constructors](#Constructors)
    1. [Default Constructor](#dc1)
    1. [Initialiser List Constructor Tests](#il1)
    1. [Input Iterator Constructor Tests](#it1)
    1. [Move Constructor Tests](#mv1)
    1. [Copy Constructor Tests](#cp1)
2. [Modifiers](#modifiers)
   1. [Insert Node](#in2)
   2. [Insert Edge](#ie2)
   3. [Replace Node](#rn2)
   4. [Merge Replace Node](#mrn2)
   5. [Erase Node](#en2)
   6. [Erase Edge](#eev2)
   9. [Clear](#cls)
3. [Accessors](#accessors)
   1. [Is Node](#in3)
   2. [Empty](#emp)
   3. [Is Connected](#ic3)
   4. [Nodes](#n3)
   5. [Weights](#w3)
   6. [Find](#f3)
   7. [Connections](#c3)
4. [Utility Functions](#utility_functions)
   1. [Equals](#eq4)
   2. [Print](#p4)
5. [Iterator](#iterator)
   1. [Begin and End](#be5)
   2. [Increment](#ic5)
   3. [Decrement](#dc5)
   4. [Dereference](#dr5)
   4. [Equals](#eq5)
   

<h2 id="Constructors"> 1. Constructor Tests </h2>
all constructors used were tested to ensure they had worked correctly

<h3 id="dc1">Default Constructor Tests</h3>
```cpp
gdwg::graph<N, E>()
```

A default constructor is only required to create an empty graph, so the only thing 
required to check is that the graph created is empty.

<h3 id = "il1">Initialiser List Constructor Tests</h3>
```cpp
gdwg::graph<N, E>{N1, N2, N3 ..., Ni}
```

This constructor is required to make a graph that contains all the node from the 
beginning to the end of the iterator supplied. In order to test this, simply we 
just have to check that the nodes in the graph is equivalent to the SORTED nodes from
the beginning to the end of the iterator.

<h3 id = "it1">Input Iterator Constructor Tests</h3>
```cpp
gdwg::graph<N, E>(iterator_begin, iterator_end)
```

This constructor takes the beginning and end of an iterator and constructs a graph 
that contains nodes equivalent to the nodes from iterating from beginning to end. 
we simply just want to check in this case that the nodes of the graph are
equivalent to the SORTED values of the iterator from begin to end

<h3 id = "mv1">Move Constructor Tests</h3>
```cpp
gdwg::graph<N, E>(std::move(gdwg::graph<N, E>()))
```

The move constructor has 2 different kinds, one for constructor using graph() other 
using equals assignment. To test the move constructors work, we first store the nodes 
(graph state since there are no edges) from the original graph. Next we want to check 
the original graph that was moved is empty, and simply compare the constructed graph's
node (aka graph state since there are no edges) with the saved nodes

<h3 id = "cp1">Copy Constructor Tests</h3>
```cpp
gdwg::graph<N, E>(gdwg::graph<N, E>())
```

The copy constructor functions identical to the move constructor above, 
however the only difference is that it creates a copy of the graph leaving 
the original graph un-effected. So in order to test this we only want to check that the
original graph and constructed graph are identical using == operator.


<h2 id="modifiers"> 2. Modifiers </h2>

<h3 id="in2">Insert Node</h3>
```cpp
auto inserted = graph.insert_node(N value);
```

To test insert node was very simple, two cases were written, 
one case is where we simply insert a node into an empty graph, 
and check if the nodes function returns a vector with just that node inside it.
The other case is to check that the insert node function returns false if 
it is a duplicate node. This is very important to see both cases have the correct behaviour.

<h3 id="ie2">Insert Edge</h3>
```cpp
auto inserted = graph.insert_edge(N value, N value, E Weight);
```

To test insert edge a similair approach was taken to Insert Node, however there was one 
extra case to handle. I had to also test cases where either combination of a missing 
source or destination node was passed into the function. In this case I made the test 
check the correct error message is thrown.

<h3 id="rn2">Replace Node</h3>
```cpp
auto replaced = graph.replace_node(N value, N value);
```

To test replace node there were 3 types of cases to handle
1. default working case where node is replaced
2. default working case where node is not replaced
3. error case

For the first case, we check the replacement occurs extensively, this is important to ensure
that connections are correctly reflecting this change. A graph of two nodes containing only
one edge had both nodes replaced, and we check that the edge has it's node as the two updated
nodes. 

For the second case, we try to call replace with an already existing node in the graph, this
will cause a return false as we don't replace with something that already exists

For the final case we simply try to replace a node that doesn't exist in the graph and
check the appropriate error is thrown.

<h3 id="mrn2">Merge Replace Node</h3>
```cpp
graph.merge_replace_node(N value, N value);
```

Merge replace was the most complicated function to both write and test due to the complexity
and potential side-effects of working with the amount of nesting. Three seperate cases had
to be handled.
1. default working case 
2. edge case, merge replacing same node
3. error case

In the first case, when merge replacing a node, it is important that order is maintained for
the set after a merge replace, and duplicates are removed. to test this i set up the following
graph

```text
A ((A, 1), (A, 5), (B, 1), (C, 2), (D, 3))
B ((B, 9))
C ((A, 9))
```
In this case when we call merge replace A -> B, we want to make sure that the old connections
of B remain there, and that the new connections that go into B are also ordered. This also means
making sure there are no duplicate edges created. Another Important edge that was used in this
test case was A -> A (5), this case we need to make sure that we create a new edge for
B -> B (5).

In the second case we check that merge replace A -> A will not change the graph in any way.
This is important as this essentially is a do nothing statement, so we need to make sure
there are no side effects

The final error cases were if a combination of src and dst node are not in the graph 
this had to result in throwing the appropriate error message.


<h3 id="en2">Erase Node</h3>
```cpp
auto erased = graph.erase_node(N value);
```
Testing erase nodes was simple, we simply check that both the node and all connections 
assosciated to that node are correctly removed and the state of the graph reflects that.
Alongside this i also had checked that erasing a node that doesn't exist in the graph will
return false.

<h3 id="eev2">Erase Edge</h3>
```cpp
auto erased = graph.erase_edge(N value, N value, E weight);
auto erased = graph.erase_edge(graph.begin());
auro erased = graph.erase_edge(graph.begin(), graph.end());
```
Testing erase edge had many different types of cases to handle due to the different ways
you could call erase_edge. In each case the return and inputs are of different types, however
behaviour checking is identical. In each of these test cases it was important to check that
the erase_edge function behaves identical in terms of change of state. In the specific
case of iterators, we make sure that if you use the second option, you do not use graph.end()
since you cannot delete an end iterator (assumed precondition). for the first case we just
make sure the correct true/false behaviour occurs, and in the iterator case we make sure
that it returns either graph.end() or the correct iterator position.

<h3 id="cls">Clear</h3>
```cpp
graph.clear();
```
This was a simple test, the only thing this test would do is check graph.empty() is true
after calling clear, however it is still important to test the behaviour works correctly.
See below for empty().

<h2 id="accessors"> 3. Accessors </h2>
<h3 id="in3">Is Node</h3>

```cpp
auto is_node = graph.is_node(N value);
```
This test case was simply done by checking the return value of is_node on a case where it 
exists in the graph or doesn't exist in the graph, and making sure the return value is true
or false otherwise appropriately. 

<h3 id="emp">Empty</h3>
```cpp
auto is_empty = graph.empty();
```
This test is extremely important to make sure that it is right since it is used in other 
tests. Simply this test will check that the default graph constructed returns true when
empty is called, and a graph that has had all its nodes removed also satisfies empty. 

<h3 id="ic3">Is Connected</h3>
```cpp
auto is_connected = graph.is_connected(N value, N value);
```
This test simply has 2 cases, one is the default behaviour, returning true for nodes that have 
atleast 1 existing connection, and false for nodes that have no existing connection, and
the other case is if either of the nodes do not exist in the graph, it should throw an error.

<h3 id="n3">Nodes</h3>
```cpp
auto all_nodes = graph.nodes(N value);
```
This test was another extremely important case to handle as it is used throughout all my tests.
Simply this test will check that the graph would return all the nodes in the graph, in sorted 
order. This was simply done by checking manually and hard coding the values in the test. To further
make sure behaviour worked correctly, i had also erased a node and made sure that the next call
to nodes had reflected this change. 

<h3 id="w3">Weights</h3>
```cpp
auto all_weights = graph.weights(N value, N value);
```
This test was also another extremely important case to handle as it used throughout all my tests.
This test was similair to nodes, however we also had to check error cases for this. For this we simply
checked that weights for nodes that do not exist in the graph threw the appropriate runtime error. 
Another important feature to test of this function was the weights returned are in sorted order,
This was checked through hard coded values

<h3 id="f3">Find</h3>
```cpp
auto found_node = graph.find(N value, N value, E weight);
```
For this test we had to check 2 different kinds of behaviour. This test was also done using some
iterator functions. Firstly for nodes that existed in the graph, we checked that if a connection
existed between the src and dst had the weight supplied, it would return the iterator pointing
to that edge. This was checked by de-referencing the iterator and checking whats stored inside. 
The other error case to handle was to check that if either node did not exist, appropriate runtime
errors were thrown.

<h3 id="c3">Connections</h3>
```cpp
auto connections = graph.connections(N value);
```
This test was used widely in more complicated functions, so checking the behaviour of this was
very important. 2 types of behaviour was tested. In the case where a node that existed in the graph
I had checked that the connections i inserted were first correct using hard coded values. To take
the test further and make sure it can handle changes and mutation, i had also removed a connection and
made sure the connections had reflected the change. In the case of the node provided not existing
in the graph, we would check that the function would throw the appropriate runtime error. 

<h2 id="utility_functions"> 4. Utility Functions </h2>
<h3 id="eq4">Equals</h3>

```cpp
auto equals = (graph1 == graph2)
```
This test case was very simple however very important to make sure it worked correctly as it was
used throughout my other tests. Simply i created 4 graphs, 1 default graph, 1 graph constructed with
the default graph, 1 graph with a value and edge in it, 1 graph constructed with that graph. for the
graph with the edge, i had checked the 2 graphs had satisfied == to true, and then compared the connections
of the hard coded edge. 

This test case also checked == returned false if the graphs were not equal, this was done by
comparing graph 1 with graph 3.
<h3 id="p4">Print</h3>
```cpp
std::cout << graph << std::endl;
```
This test was mostly taken from the specification on how the output was meant to be outputted to the 
stream. It is still important to make sure the format of the print matches identically.

<h2 id="iterator"> 5. Iterator </h2>
<h3 id="be5">Begin and End</h3>

```cpp
auto it_begin = graph.begin();
auto it_end = graph.end();
```
In these test cases it was extremely simple to make sure they had worked correctly, specifically
for begin. It is very difficult to test end since you cannot de-reference it and compare it to a
hard coded value, however I use the property of the iterator to perform this check. 

In the case of an empty graph the iterator should be empty, so i simply compare that begin and
end are equivalent for the graph iterator. 

To test begin properly with a graph that has iterable values, i had simply created a graph with 1 hard
coded edge, and checked that de-referencing the begin had matched the value. 

<h3 id="ic5">Increment</h3>
```cpp
auto iterator = graph.begin();
auto new_it = iterator++;
++iterator;
```
To test the increment had worked correctly on the iterator, i did both post increment and pre increment
in the same file (to save space). Simply i had hard coded a few edges that i purposefully put in 
random order (not sorted). I had then created an iterator to the beginning of the graph, and called
increment. Then i had checked that the iterator de-referenced had returned the SECOND SMALLEST edge. 
In this case i had
```cpp
graph.insert_edge(1,2,3);
graph.insert_edge(1,2,7);
graph.insert_edge(1,2,4);
graph.insert_edge(1,2,6);
```
so despite being inserted in non sorted order (4 < 6 < 7), i had checked that the dereferenced iterator
had (1,2,4) not (1,2,7).

<h3 id="dc5">Decrement</h3>
```cpp
graph.insert_edge(1,2,3);
graph.insert_edge(1,2,7);
graph.insert_edge(1,2,4);
graph.insert_edge(1,2,6);
auto iterator = graph.begin();
auto new_it = iterator--;
--iterator;
```
This test was almost identical to increment however i had used the property of increment to test this.
I had used the property that calling ++ then -- would return you to the same spot. in order to do this
correctly i had created an iterator at graph.begin() and a copy of that iterator as well for reference.
I then call ++ on the original iterator, then -- on the same iterator. then to be extensive i check 
that both == satisfied for the copy of the original iterator along with the original itself, and that
the value de-referenced is the same as graph.begin() -> (1,2,3)

<h3 id="dr5">Dereference</h3>
```cpp
// assuming graph.begin() != graph.end() !!!!!!
auto iterator_dereferenced = *graph.begin();
```
This test had simply checked that de-reference returns the correct values for the iterator that
is being pointed to. This was simply done by hard coding a graph with one edge, and checking that
the de-reference of the beginning of the graph was the one edge i had hard coded in. 

<h3 id="eq5">Equals</h3>
```cpp
// assuming graph.begin() != graph.end() !!!!!!
auto iterator_dereferenced = *graph.begin();
```
This test had simply checked that de-reference returns the correct values for the iterator that
is being pointed to. This was simply done by hard coding a graph with one edge, and checking that
the de-reference of the beginning of the graph was the one edge i had hard coded in. 