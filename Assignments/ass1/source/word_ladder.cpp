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

    void generate_solution(const std::string &neighbour, const std::string &from, const std::string &to,
                           const std::unordered_map<std::string, std::vector<std::string>> &visited_front,
                           const std::unordered_map<std::string, std::vector<std::string>> &visited_back,
                           std::vector<std::vector<std::string>> &solutions, const int &depth);

    void DFS(const std::string &start, const std::string &goal, std::vector<std::string> &path, std::unordered_set<std::string> &visited,
             std::vector<std::vector<std::string>> &all_paths,
             const std::unordered_map<std::string, std::vector<std::string>> &child_parent_map, const int &goal_depth, const int &current_depth);

    void
    update_search(std::unordered_set<std::string> &to_explore,
                  const std::unordered_map<std::string, std::unordered_set<std::string>> &neighbour_map,
                  std::unordered_map<std::string, std::vector<std::string>> &visited,
                  const std::unordered_map<std::string, std::vector<std::string>> &visited_other_direction,
                  std::vector<std::vector<std::string>> &solutions,
                  const std::string &from, const std::string &to, bool &found, const bool &forward, const int &depth);

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
        auto visited_front = std::unordered_map<std::string, std::vector<std::string>>();
        auto visited_back = std::unordered_map<std::string, std::vector<std::string>>();
        front.insert(from);
        back.insert(to);
        auto solutions = std::vector<std::vector<std::string>>();
        auto found = false;
        auto depth = 0;
        while (not front.empty() and not back.empty()) {
            update_search(front, neighbour_map, visited_front, visited_back, solutions, from, to, found, true, depth);
            if (found) {
                break;
            }
            update_search(back, neighbour_map, visited_back, visited_front, solutions, from, to, found, false, depth);
            if (found) {
                break;
            }
            depth++;
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


    void
    update_search(std::unordered_set<std::string> &to_explore,
                  const std::unordered_map<std::string, std::unordered_set<std::string>> &neighbour_map,
                  std::unordered_map<std::string, std::vector<std::string>> &visited,
                  const std::unordered_map<std::string, std::vector<std::string>> &visited_other_direction,
                  std::vector<std::vector<std::string>> &solutions,
                  const std::string &from, const std::string &to, bool &found, const bool &forward, const int &depth) {
        auto new_layer = std::unordered_set<std::string>();
        for (auto word : to_explore) {
            auto neighbours = get_neighbours(word, neighbour_map);
            for (const auto &neighbour : neighbours) {
                if (visited.count(neighbour)) {
                    continue;
                }
                if (visited_other_direction.count(neighbour) ||
                    ((neighbour == from && not forward) || (neighbour == to && forward))) {
                    if (forward) {
                        visited[word].push_back(neighbour);
                    } else {
                        visited[neighbour].push_back(word);
                    }
                    generate_solution(neighbour, from, to, visited, visited_other_direction, solutions, depth);
                    found = true;
                }else {
                    // if we go forward, we update our parent so that the neighbour is a CHILD from the origin word
                    // this way visited keeps track of the parent node from shortest path its found
                    if (forward) {
                        visited[word].push_back(neighbour);
                    } else {
                        visited[neighbour].push_back(word);
                    }
                    new_layer.insert(neighbour);
                }
            }
        }
        to_explore = new_layer;
    }

    void generate_solution(const std::string &neighbour, const std::string &from, const std::string &to,
                           const std::unordered_map<std::string, std::vector<std::string>> &visited_front,
                           const std::unordered_map<std::string, std::vector<std::string>> &visited_back,
                           std::vector<std::vector<std::string>> &solutions, const int &depth) {
        // now that we have the intersecting neighbour
        // we want to perform a DFS from, origin -> intersecting neighbour and intersecting neighbour -> end word
        // and merge the two paths together to form solution
        auto forward_paths = std::vector<std::vector<std::string>>();
        auto forward_path_start = std::vector<std::string>{from};
        auto backward_paths = std::vector<std::vector<std::string>>();
        auto backward_path_start = std::vector<std::string>{neighbour};

        auto dfs_vis_front = std::unordered_set<std::string>();
        auto dfs_vis_back = std::unordered_set<std::string>();
        // we will take all combinations of forward + back paths and insert that into our solutions
        DFS(from, neighbour, forward_path_start, dfs_vis_front, forward_paths, visited_front, depth, 0);
        DFS(neighbour, to, backward_path_start, dfs_vis_back, backward_paths, visited_back, depth, 0);
        for (auto forward_path : forward_paths ){
            auto  merged_path = std::vector<std::string>();
            forward_path.pop_back();
            for(auto backward_path : backward_paths){
                merged_path.insert(merged_path.end(), forward_path.begin(), forward_path.end());
                merged_path.insert(merged_path.end(), backward_path.begin(), backward_path.end());
                solutions.push_back(merged_path);
            }
        }

    }

    void DFS(const std::string &start, const std::string &goal, std::vector<std::string> &path, std::unordered_set<std::string> &visited,
             std::vector<std::vector<std::string>> &all_paths,
             const std::unordered_map<std::string, std::vector<std::string>> &child_parent_map, const int &goal_depth, const int &current_depth) {
        if(goal_depth < current_depth){
            return;
        }
        if (start == goal) {
            all_paths.push_back(path);
            return;
        }
        if (not child_parent_map.count(start)) {
            return;
        }
        auto x = child_parent_map.at(start);
        for (const auto &child : child_parent_map.at(start)) {
            if(visited.count(child)){
                continue;
            }
            path.push_back(child);
            visited.insert(child);
            DFS(child, goal, path, visited, all_paths, child_parent_map, goal_depth, current_depth + 1);
            path.pop_back();
        }

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