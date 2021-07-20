#ifndef GDWG_GRAPH_HPP
#define GDWG_GRAPH_HPP

#include <memory>
#include <set>
#include <unordered_map>
#include <map>

namespace gdwg {
    template<typename N, typename E>
    class graph {
    public:
        graph() = default;

        graph(std::initializer_list<N>);

        template<typename InputIt>
        graph(InputIt first, InputIt last);

        graph(graph &&other) noexcept;

        graph(graph const &other);

        auto operator=(graph const &other) -> graph &;

        auto operator=(graph &&other) noexcept -> graph &;

        struct value_type {
            N from;
            N to;
            E weight;
        };

        // Your member functions go here
        auto insert_node(N const &value) -> bool;

        auto insert_edge(N const &src, N const &dst, E const &weight) -> bool;

        auto replace_node(N const& old_data, N const& new_data) -> bool;


    private:
        struct Edge {
            Edge(const N &node, const E &w = E()) {
                connected = std::make_shared<N>(node);
                weight = w;
            }

            Edge(const std::shared_ptr<N> &node, const E &w = E()) {
                connected = node;
                weight = w;
            }

            std::weak_ptr<N> connected;
            E weight;

            E get_weight() const {
                return this->weight;
            }

            N get_node() const {
                return *this->connected;
            }

            bool operator<(const Edge &rhs) const {
                if(rhs.connected.lock().get() == connected.lock().get()){
                    return false;
                }
                return weight < rhs.weight;
            }
        };

        struct compare_nodes {
            bool operator()(const std::shared_ptr<N> &l, const std::shared_ptr<N> &r) const {
                return *l.get() < *r.get();
            }
        };

        std::map<std::shared_ptr<N>, std::set<Edge>, compare_nodes> graph_;
    };

    template<typename N, typename E>
    graph<N, E>::graph(std::initializer_list<N> il1) {
        std::for_each(il1.begin(), il1.end(),
                      [&](auto node) {
                          graph_.emplace(std::make_shared<N>(node), std::set<Edge>());
                      });

    }

    template<typename N, typename E>
    template<typename InputIt>
    graph<N, E>::graph(InputIt first, InputIt last) : graph() {
        std::for_each(first, last,
                      [&](auto node) {
                          graph_.emplace(std::make_shared<N>(node), std::set<Edge>());
                      });
    }

    template<typename N, typename E>
    graph<N, E>::graph(graph &&other) noexcept {
        graph_ = std::move(other.graph_);
        other.graph_.clear();
    }

    template<typename N, typename E>
    graph<N, E>::graph(const graph &other) : graph_(other.graph_.begin(), other.graph_.end()) {
        std::for_each(other.graph_.begin(), other.graph_.end(), [&](auto node) {
            if (graph_.contains(node.first)) {
                graph_.at(node.first.get()) = other.graph_.at(node.first.get());
            }
        });
    }

    template<typename N, typename E>
    auto graph<N, E>::operator=(const graph &other) -> graph & {
        std::for_each(other.graph_.begin(), other.graph_.end(), [&](auto node) {
            graph_.emplace(node, std::set<Edge>());
            if (graph_.contains(node.first)) {
                graph_.at(node.first) = other.graph_.at(node.first);
            }
        });
        return *this;
    }

    template<typename N, typename E>
    auto graph<N, E>::operator=(graph &&other) noexcept -> graph & {
        graph_ = std::move(other.graph_);
        other.graph_.clear();
        return *this;
    }

    template<typename N, typename E>
    auto graph<N, E>::insert_node(const N &value) -> bool {
        if (graph_.find(std::make_shared<N>(value)) == graph_.end()) {
            graph_.emplace(std::make_shared<N>(value), std::set<Edge>());
            return true;
        }
        return false;
    }

    template<typename N, typename E>
    auto graph<N, E>::insert_edge(const N &src, const N &dst, const E &weight) -> bool {
        auto check_node_src = graph_.find(std::make_shared<N>(src));
        auto check_node_dst = graph_.find(std::make_shared<N>(dst));
        if (check_node_dst == graph_.end() or check_node_src == graph_.end()) {
            throw std::runtime_error(
                    "Cannot call gdwg::graph<N, E>::insert_edge when either src or dst node does not exist");
        }
        // first we will check if the edge already exists, this will be O(log(n)) due to search time for set
        auto check_edge = graph_.at(std::make_shared<N>(src)).find(Edge{dst, E()});
        if(check_edge == graph_.at(std::make_shared<N>(src)).end()){
            auto node = std::find(graph_.begin(), graph_.end(), [&](auto value){return value.first.get() == src;});
            //graph_.at(std::make_shared<N>(src)).insert(Edge{node.first, weight});
            return true;
        }
        return false;
    }

    template<typename N, typename E>
    auto graph<N, E>::replace_node(const N &old_data, const N &new_data) -> bool {
        if(graph_.find(old_data) == graph_.end()){
            throw std::runtime_error("Cannot call gdwg::graph<N, E>::replace_node on a node that doesn't exist");
        }
        if(graph_.find(new_data) != graph_.end()) {
            return false;
        }
        graph_.emplace(new_data, std::move(graph_.at(old_data)));
        graph_.erase(old_data);
        return true;
    }
} // namespace gdwg
#endif // GDWG_GRAPH_HPP

