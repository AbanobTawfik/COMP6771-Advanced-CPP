#include "comp6771/word_ladder.hpp"
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <iostream>

// Write your implementation here
namespace word_ladder_slow {
    ////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                            //
    //                                                                                            //
    //                                             HELPER METHODS                                 //
    //                                                                                            //
    //                                                                                            //
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // this method is designed to get ALL the immediate one hop neighbours of a word by modifying
    // each letter one by one in the word, and retrieving the valid words that fill in the gap, for
    // example all neighbours of word are all valid words that fill the underscore for: _ord all
    // valid words that fill the underscore for: w_rd all valid words that fill the underscore for:
    // wo_d all valid words that fill the underscore for: woo_
    auto
    get_neighbours(const std::string &word,
                   const std::unordered_map<std::string, std::unordered_set<std::string>> &neighbour_map)
    -> std::unordered_set<std::string> {
        auto neighbours = std::unordered_set<std::string>();
        for (std::vector<std::string>::size_type i = 0; i < word.size(); i++) {
            auto word_copy = word;
            word_copy[i] = '_';
            if (neighbour_map.contains(word_copy)) {
                neighbours.insert(neighbour_map.at(word_copy).begin(),
                                  neighbour_map.at(word_copy).end());
            }
        }
        neighbours.erase(word);
        return neighbours;
    }

    // a simplified modification of DFS that will simply go through all paths from start node to end
    // node and append all of the paths into the final solution list.
    void DFS(const std::string &start,
             const std::string &goal,
             std::vector<std::string> &path,
             const std::unordered_map<std::string, std::unordered_set<std::string>> &graph,
             std::vector<std::vector<std::string>> &all_solutions) {
        if (start == goal) {
            all_solutions.push_back(path);
        } else {
            if (graph.contains(start)) {
                for (const auto &child : graph.at(start)) {
                    path.push_back(child);
                    DFS(child, goal, path, graph, all_solutions);
                    path.pop_back();
                }
            }
        }
    }

    // this method is designed to retrieve ALL paths from the origin word, to the destination word
    // using an adjacency list graph. this will be done using a modified DFS that simply finds ALL
    // paths from the start to end node. this works in our case as all neighbourings done are from
    // the shortest path from start -> end, discovered during the Bi-Directional BFS
    void reconstruct_solutions_from_graph(
            const std::string &from,
            const std::string &to,
            const std::unordered_map<std::string, std::unordered_set<std::string>> &graph,
            std::vector<std::vector<std::string>> &solutions) {
        auto path = std::vector<std::string>{from};
        DFS(from, to, path, graph, solutions);
    }

    // this is the main mechanism for the Bi-Directional BFS. This method will simply pick between
    // the layer with the smallest amount of nodes (either front or back layer) and will create a new
    // layer that contains all the 1 hop neighbours from the current layer, whilst updating the
    // adjacency list graph in order to keep track of the parents/children. the current layer will
    // then become the new layer

    // it is worth noting that we also add ALL nodes from the forward and backward set into visited
    // as this prevents exploring paths that are not shortest path. This is because, the nodes in
    // either set are ALWAYS the shortest path nodes from the from and to words, as the search is
    // bidirectional, we want the shortest path to all intersecting words from both directions, so
    // for example if the word "hello" is in the forward set, and backwards one of the neighbours is
    // "hello", we don't want to expand the word "hello" in the backward set, as it would lead to an
    // overall longer path.

    // if we are working on the forward path, we make the children of the current node the neighbour
    // words if we are working on the backward path, we make the children of the neighbour the
    // current node this is so that during path reconstruction, we don't get the path from
    // intersecting node -> end word backwards

    // when an intersection word is found (when one of the neighbours we discover is in the other
    // directions set) then we have found the shortest path possible from start -> end and we can
    // begin reconstructing ALL solutions using DFS. This can be seen as the following front
    // neighbour = "word", back set = ["word", "hord", "bord"] etc. indicating we have the shortest
    // path from front -> word, and the shortest path from back -> word already meaning our overall
    // shortest path will intersect at "word" rather than ending the search after immediately finding
    // this word, we will expand all neighbours at this level to find ALL intersecting words, giving
    // us ALL solutions possible.

    // due to all paths having the same cost (all neighbours are 1 distance apart), and all
    // information of start/end node being available to us, bidirectional search massively increases
    // performance of this search time complexity from O(b^d) to O(b^(d/2)) where b is our branch
    // factor (average number of neighbours from each node at each depth) and d is the depth of the
    // search. Halving the search space more than halves the speed of execution as the complexity
    // grows exponentially
    bool
    expand_layer(std::unordered_set<std::string> &to_explore_front,
                 const std::string &goal,
                 std::unordered_set<std::string> &visited,
                 const std::unordered_map<std::string, std::unordered_set<std::string>> &neighbour_map,
                 std::unordered_map<std::string, std::unordered_set<std::string>> &graph) {
        auto new_layer = std::unordered_set<std::string>();
        // expand the smaller layer first, overall this will lead to a much more refined search space
        auto found = false;
        // keep track of words we are exploring in BOTH directions, we don't want to expand nodes in
        // the other direction since we will later explore them, this prevents rediscovering nodes in
        // front that are in back, and vice versa
        for (const auto &word : to_explore_front) {
            visited.insert(word);
        }

        for (const auto &word : to_explore_front) {
            auto neighbours = get_neighbours(word, neighbour_map);
            for (const auto &neighbour : neighbours) {
                // if the backward direction has this neighbour we have found an intersection
                if (word == goal) {
                    found = true;
                    if (not graph.contains(word)) {
                        graph.emplace(word, std::unordered_set<std::string>{neighbour});
                    } else {
                        graph.at(word).insert(neighbour);
                    }
                }
                // check if the word already seen before, if so we can ignore it
                if (not found and not visited.contains(neighbour)) {
                    new_layer.insert(neighbour);
                    // we want to add the connection into our graph now with this neighbour, since we are
                    // forward we want the PARENT to be the origin word, and child to be the neighbour
                    if (not graph.contains(word)) {
                        graph.emplace(word, std::unordered_set<std::string>{neighbour});
                    } else {
                        graph.at(word).insert(neighbour);
                    }
                }
            }
        }
        // next layer to explore for the front will be the adjacent 1 hop layer
        to_explore_front = new_layer;
        return found;
    }

    // This method is designed for pure optimisation in creating a get neighbours method
    // traditionally to get neighbours we would modify each letter in the word from a-z and check if
    // the modified word exists in the lexicon. However this is computationally expensive due to the
    // 26 for loop iterations called each time, and searching the lexicon each time for all those
    // potential words. this method will create a new mapping that contains a word with a filler spot
    // ("_" in our case) and will precompute all the potential words to that filler spot. This is
    // done by going through each word in the lexicon and for each letter in those words replacing 1
    // by 1 with the filler spot, and pushing to the list of neighbour words the original unmodified
    // word for example if our lexicon had cat, bat, hat, hot, ham

    // when we get to cat -> _at would have cat inserted to its list, c_t would have cat inserted to
    // its list and ca_ would have cat inserted to its list. now when we get to bat -> _at would
    // insert bat also into its list since _at leads to bat aswell and so on and so on this means
    // when we for instance have the word hat as our current word we are expanding, and we want all
    // neighbours we would take the word hat, modify each letter with the filler space, and get all
    // words linked to that modified word for example _at -> returns cat and bat as neighbours in
    // O(1) h_t -> returns hot in O(1) ha_ -> returns ham in O(1)
    auto generate_all_1nn(const std::unordered_set<std::string> &lexicon, const size_t &length)
    -> std::unordered_map<std::string, std::unordered_set<std::string>> {
        std::unordered_map<std::string, std::unordered_set<std::string>> all_1nn;
        for (const auto &word : lexicon) {
            if (word.size() != length) {
                continue;
            }
            for (std::vector<std::string>::size_type i = 0; i < word.length(); i++) {
                auto cloned_word = word;
                cloned_word[i] = '_';
                if (not all_1nn.contains(cloned_word)) {
                    all_1nn.emplace(cloned_word, std::unordered_set<std::string>{word});
                } else {
                    all_1nn.at(cloned_word).insert(word);
                }
            }
        }
        return all_1nn;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                            //
    //                                                                                            //
    //                                             CODE BEINGS HERE                               //
    //                                                                                            //
    //                                                                                            //
    ////////////////////////////////////////////////////////////////////////////////////////////////
    auto generate_accurate(std::string const &from,
                           std::string const &to,
                           std::unordered_set<std::string> const &lexicon)
    -> std::vector<std::vector<std::string>> {
        if (from.size() != to.size() || not lexicon.contains(from) || not lexicon.contains(to)
            || from == to) {
            return std::vector<std::vector<std::string>>();
        }

        auto const neighbour_map = generate_all_1nn(lexicon, from.size());
        auto front = std::unordered_set<std::string>();
        auto back = std::unordered_set<std::string>();
        auto graph = std::unordered_map<std::string, std::unordered_set<std::string>>();
        auto visited = std::unordered_set<std::string>();
        front.insert(from);
        back.insert(to);
        auto solutions = std::vector<std::vector<std::string>>();
        auto found = false;
        while (not front.empty() and not back.empty()) {
            found = word_ladder_slow::expand_layer(front, to, visited, neighbour_map, graph);
            if (found) {
                break;
            }
        }

        if (found) {
            reconstruct_solutions_from_graph(from, to, graph, solutions);
        }
        std::sort(solutions.begin(), solutions.end());
        return solutions;
    }

} // namespace word_ladder_slow
