#include "comp6771/word_ladder.hpp"
#include <queue>
#include <chrono>
#include <iostream>

// Write your implementation here
namespace word_ladder {
    auto get_neighbours(std::vector<std::string> path,
                        std::unordered_map<std::string, std::unordered_set<std::string>> neighbour_map) -> std::unordered_set<std::string>;

    void
    update_search(int depth, std::unordered_set<std::string> neighbours,
                  std::unordered_map<std::string, std::string> &visited,
                  std::unordered_map<std::string, std::string> visited_other_direction,
                  std::queue<std::vector<std::string>> &all_paths, std::vector<std::string> path,
                  std::vector<std::vector<std::string>> &solutions, std::string keyword,
                  bool &found, bool forward);

    auto generate(std::string
                  const &from,
                  std::string const &to,
                  std::unordered_set<std::string>
                  const &lexicon)
    -> std::vector<std::vector<std::string>> {
        if (from.size() != to.size()) {
            return std::vector<std::vector<std::string>>();
        }
        auto const neighbour_map = word_ladder::generate_all_1nn(lexicon, from.size());
        auto front = std::queue<std::vector<std::string>>();
        // keep a list of parents too while we're at it, poggies
        auto visited_front = std::unordered_map<std::string, std::string>();
        auto back = std::queue<std::vector<std::string>>();
        auto visited_back = std::unordered_map<std::string, std::string>();
        front.push({to});
        back.push({from});
        auto solutions = std::vector<std::vector<std::string>>();
        auto found = false;
        while (not front.empty() and not back.empty()) {
            auto start = std::chrono::high_resolution_clock::now();
            auto front_curr = front.front();
            auto back_curr = back.front();
            front.pop();
            back.pop();
            int depth_front = front_curr.size();
            int depth_back = back_curr.size();
            // check all the neighbours of front_curr
            auto front_neighbours = std::unordered_set<std::string>();
            auto last_node = front_curr.back();
            for (int i = 0; i < last_node.size(); i++) {
                auto last_node_copy = last_node;
                last_node_copy[i] = '_';
                if (neighbour_map.count(last_node_copy)) {
                    front_neighbours.insert(neighbour_map.at(last_node_copy).begin(),
                                            neighbour_map.at(last_node_copy).end());
                }
            }
            front_neighbours.erase(front_curr.back());

            auto back_neighbours = std::unordered_set<std::string>();
            last_node = back_curr.back();
            for (int i = 0; i < last_node.size(); i++) {
                auto last_node_copy = last_node;
                last_node_copy[i] = '_';
                back_neighbours.insert(neighbour_map.at(last_node_copy).begin(),
                                       neighbour_map.at(last_node_copy).end());
            }
            back_neighbours.erase(front_curr.back());
            auto end = std::chrono::high_resolution_clock::now();
            update_search(depth_front, front_neighbours, visited_front, visited_back, front, front_curr,
                          solutions, from, found, true);
            update_search(depth_back, back_neighbours, visited_back, visited_front, back, back_curr, solutions,
                          to, found, false);
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            std::cout << duration.count() << std::endl;
        }
        return solutions;
    }

//    auto get_neighbours(std::vector<std::string> path,
//                        std::unordered_map<std::string, std::unordered_set<std::string>> neighbour_map) -> std::unordered_set<std::string> {
//        auto neighbours = std::unordered_set<std::string>();
//
//        auto last_node = path.back();
//        for (int i = 0; i < last_node.size(); i++) {
//            auto last_node_copy = last_node;
//            last_node_copy[i] = '_';
////            neighbours.insert(neighbour_map.at(last_node_copy.begin(), neighbour_map.at(last_node_copy).end());
//        }
//        neighbours.erase(path.back());
//        return neighbours;
//    }

    void
    update_search(int depth, std::unordered_set<std::string> neighbours,
                  std::unordered_map<std::string, std::string> &visited,
                  std::unordered_map<std::string, std::string> visited_other_direction,
                  std::queue<std::vector<std::string>> &all_paths, std::vector<std::string> path,
                  std::vector<std::vector<std::string>> &solutions, std::string keyword,
                  bool &found, bool forward) {
        for (auto neighbour : neighbours) {
            if (visited.count(neighbour)) {
                continue;
            }
            if (neighbour == keyword) {
//                auto path_copy = path;
//                path_copy.push_back(neighbour);
//                solutions.push_back(path_copy);
                found = true;
            }
            if (visited_other_direction.count(neighbour)) {
                found = true;
            }
            auto path_copy = path;
            if (!found) {
                // if we go forward, we update our parent so that the neighbour is a CHILD from the origin word
                // this way visited keeps track of the parent node from shortest path its found
                if (forward) {
                    visited[neighbour] = path_copy.back();
                } else {
                    visited[path_copy.back()] = neighbour;
                }
                path_copy.push_back(neighbour);
                all_paths.push(path_copy);
            }
        }
    }

    auto generate_all_1nn(
            std::unordered_set<std::string> lexicon,
            int length) -> std::unordered_map<std::string, std::unordered_set<std::string>> {
        std::unordered_map<std::string, std::unordered_set<std::string>> all_1nn;
        for (auto word : lexicon) {
            if (word.size() != length) {
                continue;
            }
            for (int i = 0; i < word.length(); i++) {
                auto cloned_word = word;
                cloned_word[i] = '_';
                all_1nn[cloned_word].insert(word);
                if (cloned_word == "_heeing" || cloned_word == "t_eeing" || cloned_word == "th_eing" ||
                    cloned_word == "the_ing"
                    || cloned_word == "thee_ng" || cloned_word == "theei_g" || cloned_word == "theein_") {
                    auto x = all_1nn.at(cloned_word);
                    auto z = 1;
                }
            }
        }
        return all_1nn;
    }

}