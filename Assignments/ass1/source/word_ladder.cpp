#include "comp6771/word_ladder.hpp"
#include <unordered_set>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <set>


// Write your implementation here
namespace word_ladder {
    auto get_neighbours(const std::string &word,
                        const std::unordered_map<std::string, std::unordered_set<std::string>> &neighbour_map) -> std::unordered_set<std::string>;

    void reconstruct_solutions_from_graph(const std::string &from, const std::string &to,
                                          const std::unordered_map<std::string, std::vector<std::string>> &graph,
                                          std::vector<std::vector<std::string>> &solutions);

    void DFS(const std::string &start, const std::string &goal, std::vector<std::string> &path,
             const std::unordered_map<std::string, std::vector<std::string>> &graph,
             std::vector<std::vector<std::string>> &all_solutions);

    bool
    update_search(std::unordered_set<std::string> &to_explore_front, std::unordered_set<std::string> &to_explore_back,
                  std::unordered_set<std::string> &visited,
                  const std::unordered_map<std::string, std::unordered_set<std::string>> &neighbour_map,
                  std::unordered_map<std::string, std::vector<std::string>> &graph);

    auto generate_all_1nn(
            std::unordered_set<std::string> lexicon,
            size_t length) -> std::unordered_map<std::string, std::unordered_set<std::string>>;

    auto generate(std::string
                  const &from,
                  std::string const &to,
                  std::unordered_set<std::string>
                  const &lexicon) -> std::vector<std::vector<std::string>> {
        if (from.size() != to.size()) {
            return std::vector<std::vector<std::string>>();
        }

        auto const neighbour_map = word_ladder::generate_all_1nn(lexicon, from.size());
        auto front = std::unordered_set<std::string>();
        auto back = std::unordered_set<std::string>();
        // keep a list of parents too while we're at it, poggies
        auto graph = std::unordered_map<std::string, std::vector<std::string>>();
        auto visited = std::unordered_set<std::string>();
        front.insert(from);
        back.insert(to);
        auto solutions = std::vector<std::vector<std::string>>();
        auto found = false;
        while (not front.empty() and not back.empty()) {
            found = update_search(front, back, visited, neighbour_map, graph);
            if (found) {
                break;
            }
        }

        if (found) {
            reconstruct_solutions_from_graph(from, to, graph, solutions);
        }
        // remove all paths that aren't the shortest
        std::sort(solutions.begin(), solutions.end());
        for (auto i : solutions) {
            for (auto node : i) {
                std::cout << node << " ";
            }
            std::cout << std::endl;
        }
        return solutions;
    }

    bool
    update_search(std::unordered_set<std::string> &to_explore_front, std::unordered_set<std::string> &to_explore_back,
                  std::unordered_set<std::string> &visited,
                  const std::unordered_map<std::string, std::unordered_set<std::string>> &neighbour_map,
                  std::unordered_map<std::string, std::vector<std::string>> &graph) {
        auto new_layer = std::unordered_set<std::string>();
        // expand the smaller layer first, overall this will lead to a much more refined search space
        auto found = false;
        // keep track of words we are exploring in BOTH directions, we don't want to expand nodes in the other direction
        // since we will later explore them, this prevents rediscovering nodes in front that are in back, and vice versa
        for(auto word : to_explore_front){
            visited.insert(word);
        }
        for(auto word : to_explore_back){
            visited.insert(word);
        }
        if (to_explore_front.size() > to_explore_back.size()) {
            // traversing forward
            for (const auto &word : to_explore_front) {
                auto neighbours = get_neighbours(word, neighbour_map);
                for (const auto &neighbour : neighbours) {
                    // if the backward direction has this neighbour we have found an intersection
                    if (to_explore_back.count(neighbour)) {
                        found = true;
                        graph[word].push_back(neighbour);
                    }
                    // check if the word already seen before, if so we can ignore it
                    if (not found and not visited.contains(neighbour)) {
                        new_layer.insert(neighbour);
                        // we want to add the connection into our graph now with this neighbour, since we are forward
                        // we want the PARENT to be the origin word, and child to be the neighbour
                        graph[word].push_back(neighbour);
                    }
                }
            }
            // next layer to explore for the front will be the adjacent 1 hop layer
            to_explore_front = new_layer;
        } else {
            // traversing backward
            for (const auto &word : to_explore_back) {
                auto neighbours = get_neighbours(word, neighbour_map);
                for (const auto &neighbour : neighbours) {
                    // if the forward direction has this neighbour we have found an intersection
                    if (to_explore_front.count(neighbour)) {
                        found = true;
                        graph[neighbour].push_back(word);
                    }
                    // check if the word already seen before, if so we can ignore it
                    if (not found and not visited.contains(neighbour)) {
                        new_layer.insert(neighbour);
                        // we want to add the connection into our graph now with this neighbour, since we are backward
                        // we want the PARENT to be the NEIGHBOUR word, and child to be the ORIGIN
                        graph[neighbour].push_back(word);
                    }
                }
            }
            // next layer to explore for the front will be the adjacent 1 hop layer
            to_explore_back = new_layer;
        }
        return found;
    }

    void reconstruct_solutions_from_graph(const std::string &from, const std::string &to,
                                          const std::unordered_map<std::string, std::vector<std::string>> &graph,
                                          std::vector<std::vector<std::string>> &solutions) {
        auto path = std::vector<std::string>{from};
        DFS(from, to, path, graph, solutions);
    }

    void DFS(const std::string &start, const std::string &goal, std::vector<std::string> &path,
             const std::unordered_map<std::string, std::vector<std::string>> &graph,
             std::vector<std::vector<std::string>> &all_solutions) {
        if (start == goal) {
            all_solutions.push_back(path);
        } else {
            for (const auto &child : graph.at(start)) {
                path.push_back(child);
                DFS(child, goal, path, graph, all_solutions);
                path.pop_back();
            }
        }

    }

    void trim_paths_not_shortest(std::vector<std::vector<std::string>> &solutions) {
        if (solutions.size() > 0) {
            auto min_length = solutions.begin()->size();
            // find shortest length
            for (auto solution : solutions) {
                if (solution.size() < min_length) {
                    min_length = solution.size();
                }
            }
            auto new_solutions = std::vector<std::vector<std::string>>();
            // trim all solutions not of that length
            for (auto solution : solutions) {
                if (solution.size() == min_length) {
                    new_solutions.push_back(solution);
                }
            }
            std::sort(solutions.begin(), new_solutions.end());
            solutions = new_solutions;
        }
    }

    auto get_neighbours(const std::string &word,
                        const std::unordered_map<std::string, std::unordered_set<std::string>> &neighbour_map) -> std::unordered_set<std::string> {
        auto neighbours = std::unordered_set<std::string>();
        for (std::vector<std::string>::size_type i = 0; i < word.size(); i++) {
            auto last_node_copy = word;
            last_node_copy[i] = '_';
            if (neighbour_map.count(last_node_copy)) {
                neighbours.insert(neighbour_map.at(last_node_copy).begin(),
                                  neighbour_map.at(last_node_copy).end());
            }
        }
        neighbours.erase(word);
        return neighbours;
    }

    auto generate_all_1nn(
            std::unordered_set<std::string> lexicon,
            size_t length) -> std::unordered_map<std::string, std::unordered_set<std::string>> {
        std::unordered_map<std::string, std::unordered_set<std::string>> all_1nn;
        for (auto word : lexicon) {
            if (word.size() != length) {
                continue;
            }
            for (std::vector<std::string>::size_type i = 0; i < word.length(); i++) {
                auto cloned_word = word;
                cloned_word[i] = '_';
                all_1nn[cloned_word].insert(word);
            }
        }
        return all_1nn;
    }

}