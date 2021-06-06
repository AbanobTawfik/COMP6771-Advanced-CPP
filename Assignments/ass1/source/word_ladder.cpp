#include "comp6771/word_ladder.hpp"
#include <queue>
#include <chrono>
#include <iostream>

// Write your implementation here
namespace word_ladder {
    auto get_neighbours(const std::string &word,
                        const std::unordered_map<std::string, std::unordered_set<std::string>> &neighbour_map) -> std::unordered_set<std::string>;

    void generate_solution(const std::string &neighbour, const std::string &from, const std::string &to,
                           const std::unordered_map<std::string, std::string> &visited_front,
                           const std::unordered_map<std::string, std::string> &visited_back,
                           std::vector<std::vector<std::string>> &solutions, const bool &forward);

    void
    update_search(const std::string &parent,
                  const std::unordered_set<std::string> &neighbours,
                  std::queue<std::string> &to_explore,
                  std::unordered_map<std::string, std::string> &visited,
                  const std::unordered_map<std::string, std::string> &visited_other_direction,
                  std::vector<std::vector<std::string>> &solutions,
                  const std::string &from, const std::string &to, bool &found, const bool &forward);

    void show_listings(const std::unordered_map<std::string, std::string> &visited_front){
        auto printout = std::unordered_map<std::string, std::vector<std::string>>();
        for(auto node : visited_front){
            printout[node.second].push_back(node.first);
        }
        for(auto x : printout){
            std::cout << x.first << " -> ";
            std::cout << "[";
            for(auto node : x.second) {
                std::cout << node << ", ";
            }
            std::cout << "]" << std::endl;
        }
    }

    auto generate(std::string
                  const &from,
                  std::string const &to,
                  std::unordered_set<std::string>
                  const &lexicon) -> std::vector<std::vector<std::string>> {
        if (from.size() != to.size()) {
            return std::vector<std::vector<std::string>>();
        }

        auto const neighbour_map = word_ladder::generate_all_1nn(lexicon, from.size());
        auto front = std::queue<std::string>();
        auto back = std::queue<std::string>();
        // keep a list of parents too while we're at it, poggies
        auto visited_front = std::unordered_map<std::string, std::string>();
        auto visited_back = std::unordered_map<std::string, std::string>();
        front.push(from);
        back.push(to);
        auto solutions = std::vector<std::vector<std::string>>();
        auto found = false;

        while (not front.empty() and not back.empty()) {
            auto start = std::chrono::high_resolution_clock::now();
            auto front_word = front.front();
            front.pop();
            auto front_neighbours = get_neighbours(front_word, neighbour_map);
            update_search(front_word, front_neighbours, front, visited_front, visited_back, solutions, from, to, found,
                          true);

            auto end = std::chrono::high_resolution_clock::now();
            auto back_word = back.front();
            back.pop();
            auto back_neighbours = get_neighbours(back_word, neighbour_map);
            update_search(back_word, back_neighbours, back, visited_back, visited_front, solutions, from, to, found,
                          false);
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//            std::cout << duration.count() << std::endl;
        }
        std::sort(solutions.begin(), solutions.end());
        for(auto i : solutions){
            for(auto node : i){
                std::cout << node << " ";
            }
            std::cout <<  std::endl;
        }
        return solutions;
    }

    auto get_neighbours(const std::string &word,
                        const std::unordered_map<std::string, std::unordered_set<std::string>> &neighbour_map) -> std::unordered_set<std::string> {
        auto neighbours = std::unordered_set<std::string>();
        for (int i = 0; i < word.size(); i++) {
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
    update_search(const std::string &parent,
                  const std::unordered_set<std::string> &neighbours,
                  std::queue<std::string> &to_explore,
                  std::unordered_map<std::string, std::string> &visited,
                  const std::unordered_map<std::string, std::string> &visited_other_direction,
                  std::vector<std::vector<std::string>> &solutions,
                  const std::string &from, const std::string &to, bool &found, const bool &forward) {
        for (const auto &neighbour : neighbours) {
            if (visited.count(neighbour)) {
                continue;
            }
            if (visited_other_direction.count(neighbour) ||
                ((neighbour == from && not forward) || (neighbour == to && forward))) {
                visited[neighbour] = parent;
                if (forward) {
                    generate_solution(neighbour, from, to, visited, visited_other_direction, solutions, forward);
                } else {
                    generate_solution(neighbour, from, to, visited_other_direction, visited, solutions, forward);
                }
                found = true;
            }
            if (!found) {
                // if we go forward, we update our parent so that the neighbour is a CHILD from the origin word
                // this way visited keeps track of the parent node from shortest path its found
                visited[neighbour] = parent;
                to_explore.push(neighbour);
            }
        }
    }
    
    void generate_solution(const std::string &neighbour, const std::string &from, const std::string &to,
                           const std::unordered_map<std::string, std::string> &visited_front,
                           const std::unordered_map<std::string, std::string> &visited_back,
                           std::vector<std::vector<std::string>> &solutions, const bool &forward) {
        // now that we have the intersecting neighbour

        show_listings(visited_front);
        std::cout << "---------------------------------------------------------" << std::endl;
        show_listings(visited_back);

        // we want to go from the front -> neighbour, merge that path with the back -> neighbour
        std::string word = neighbour;
        auto forward_path = std::vector<std::string>();
        auto backward_path = std::vector<std::string>();
        // backtrack from neighbour -> beginning word for the forward path
        // note we storing in reverse order, so we need to reverse this list
        while(word != from){
            forward_path.push_back(word);
            // get parent of this node and add it to the list
            word = visited_front.at(word);
        }
        std::reverse(forward_path.begin(), forward_path.end());
        // remove duplicate neighbour from the path
        forward_path.erase(std::remove(forward_path.begin(), forward_path.end(), neighbour), forward_path.end());

        word = neighbour;
        while(word != to){

            backward_path.push_back(word);
            word = visited_back.at(word);
        }

        forward_path.insert(forward_path.end(), backward_path.begin(), backward_path.end());
        forward_path.insert(forward_path.begin(), from);
        forward_path.insert(forward_path.end(), to);

        solutions.push_back(forward_path);

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
            }
        }
        return all_1nn;
    }

}