#include "comp6771/word_ladder.hpp"
#include <queue>
#include <chrono>
#include <iostream>

// Write your implementation here
namespace word_ladder {
    auto get_neighbours(std::vector<std::string> path,
                        std::unordered_map<std::string, std::unordered_set<std::string>> neighbour_map) -> std::unordered_set<std::string>;

    int
    update_search(int depth, std::unordered_set<std::string> neighbours, std::unordered_map<std::string, int> &visited,
                  std::unordered_map<std::string, int> visited_other_direction,
                  std::queue<std::vector<std::string>> &all_paths, std::vector<std::string> path,
                  std::vector<std::vector<std::string>> &solutions, std::string keyword,
                  std::queue<std::vector<std::string>> &all_paths2);

    auto generate(std::string
                  const &from,
                  std::string const &to,
                  std::unordered_set<std::string>
                  const &lexicon)
    -> std::vector<std::vector<std::string>> {
        if (from.size() != to.size()) {
            return std::vector<std::vector<std::string>>();
        }
        auto start = std::chrono::high_resolution_clock::now();
        auto const neighbour_map = word_ladder::generate_all_1nn(lexicon, from.size());
        auto front = std::queue<std::vector<std::string>>();
        auto visited_front = std::unordered_map<std::string, int>();
        auto back = std::queue<std::vector<std::string>>();
        auto visited_back = std::unordered_map<std::string, int>();
        front.push({to});
        //visited_front[from] = 0;
        back.push({from});
        //visited_front[to] = 0;
        auto solutions = std::vector<std::vector<std::string>>();
        int shortest_distance;
        while (not front.empty() and not back.empty()) {
            auto front_curr = front.front();
            auto back_curr = back.front();
            front.pop();
            back.pop();
            int depth_front = front_curr.size();
            int depth_back = back_curr.size();
            // check all the neighbours of front_curr
            auto front_neighbours = get_neighbours(front_curr, neighbour_map);
            auto back_neighbours = get_neighbours(back_curr, neighbour_map);
            auto x = update_search(depth_front, front_neighbours, visited_front, visited_back, front, front_curr,
                                   solutions, from, back);
            auto y = update_search(depth_back, back_neighbours, visited_back, visited_front, back, back_curr, solutions,
                                   to, front);
            if (x != -1 or y != -1) {
                std::cout << x << " - " << y;
            }
        }
        return solutions;
    }

    auto get_neighbours(std::vector<std::string> path,
                        std::unordered_map<std::string, std::unordered_set<std::string>> neighbour_map) -> std::unordered_set<std::string> {
        auto neighbours = std::unordered_set<std::string>();

        auto last_node = path.back();
        for (int i = 0; i < last_node.size(); i++) {
            auto last_node_copy = last_node;
            last_node_copy[i] = '_';
            neighbours.insert(neighbour_map[last_node_copy].begin(), neighbour_map[last_node_copy].end());
        }
        neighbours.erase(path.back());
        return neighbours;
    }

    int
    update_search(int depth, std::unordered_set<std::string> neighbours, std::unordered_map<std::string, int> &visited,
                  std::unordered_map<std::string, int> visited_other_direction,
                  std::queue<std::vector<std::string>> &all_paths, std::vector<std::string> path,
                  std::vector<std::vector<std::string>> &solutions, std::string keyword,
                  std::queue<std::vector<std::string>> &all_paths2) {
        for (auto neighbour : neighbours) {
            if (visited.count(neighbour)) {
                continue;
            }
            if (neighbour == keyword) {
                auto path_copy = path;
                path_copy.push_back(neighbour);
                solutions.push_back(path_copy);
                return depth + 1;
            }
            if (visited_other_direction.count(neighbour)) {
                return visited_other_direction[neighbour] + depth;
            }
            auto path_copy = path;
            visited[neighbour] = depth;
            path_copy.push_back(neighbour);
            all_paths.push(path_copy);
        }
        return -1;
    }


}