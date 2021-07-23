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

        auto insert_edge(N const &from, N const &to, E const &weight) -> bool;

        auto replace_node(N const &old_data, N const &new_data) -> bool;

        auto merge_replace_node(N const &old_data, N const &new_data) -> void;

    private:
        struct Node;
        struct Edge;
        struct set_comparator;
        struct Raw_Edge;

        struct Edge {
            Edge() = default;

            Edge(std::weak_ptr<Node> from, std::weak_ptr<Node> to, E weight) : from{from}, to{to},
                                                                               weight{weight} {}

            ~Edge() {
                from.reset();
                to.reset();
            }

            std::weak_ptr<Node> from;
            std::weak_ptr<Node> to;
            E weight;
        };

        struct Node {
            Node() = default;

            Node(N value) : value{value} {
                incoming = std::set<std::weak_ptr<Edge>, set_comparator>();
                outgoing = std::set<std::weak_ptr<Edge>, set_comparator>();
            }

            Node(N value, std::set<std::weak_ptr<Edge>> incoming, std::set<std::weak_ptr<Edge>> outgoing) : value{
                    value}, incoming{incoming}, outgoing{outgoing} {};

            std::set<std::weak_ptr<Edge>, set_comparator> incoming;
            std::set<std::weak_ptr<Edge>, set_comparator> outgoing;
            N value;
        };

        struct set_comparator {
            bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const {
                return lhs.get()->value < rhs.get()->value;
            }

            bool operator()(const std::weak_ptr<Node> &lhs, const std::weak_ptr<Node> &rhs) const {
                return lhs.lock().get()->value < rhs.lock().get()->value;
            }

            bool operator()(const Node &lhs, const Node &rhs) const {
                return lhs->value < rhs->value;
            }

            // in order to do this in O(log(N) time we need edges to be sorted properly
            // sort first by from, to, weight in that order
            bool operator()(const std::shared_ptr<Edge> &lhs, const std::shared_ptr<Edge> &rhs) const {
                // first compare by from
                if (lhs.get()->from.lock().get()->value != rhs.get()->from.lock().get()->value) {
                    return lhs.get()->from.lock().get()->value < rhs.get()->from.lock().get()->value;
                }
                // if above check failed, means from nodes are identical so now check to nodes
                if (lhs.get()->to.lock().get()->value != rhs.get()->to.lock().get()->value) {
                    return lhs.get()->to.lock().get()->value < rhs.get()->to.lock().get()->value;
                }
                // now we have same from and to nodes (same edge location), compare by weight now
                return lhs.get()->weight < rhs.get()->weight;
            }

            bool operator()(const std::weak_ptr<Edge> &lhs, const std::weak_ptr<Edge> &rhs) const {
                if (lhs.lock().get()->from.lock().get()->value != rhs.lock().get()->from.lock().get()->value) {
                    return lhs.lock().get()->from.lock().get()->value < rhs.lock().get()->from.lock().get()->value;
                }
                if (lhs.lock().get()->to.lock().get()->value != rhs.lock().get()->to.lock().get()->value) {
                    return lhs.lock().get()->to.lock().get()->value < rhs.lock().get()->to.lock().get()->value;
                }
                return lhs.lock().get()->weight < rhs.lock().get()->weight;
            }

            bool operator()(const Edge &lhs, const Edge &rhs) const {
                if (not lhs.from == rhs.from) {
                    return lhs.from < rhs.from;
                }
                if (not lhs.to == rhs.to) {
                    return lhs.to < rhs.to;
                }
                return lhs.weight < rhs.weight;
            }
        };

        // set keeps order so O(logn) lookups due to binary search built into find (RB trees)
        // nodes contain a list of all their incoming and outgoing connections, and the set of edges
        // can be used for book keeping
        // due to nodes containing a set of weak_ptrs for both incoming/outgoing connections, when a edge
        // is removed from the all_Edges set, all nodes assosicated will have corresponding connections removed too
        // only book keeping is required for managing the connections on nodes
        std::set<std::shared_ptr<Node>, set_comparator> all_nodes_;
        std::set<std::shared_ptr<Edge>, set_comparator> all_edges_;
    };

    template<typename N, typename E>
    graph<N, E>::graph(std::initializer_list<N> il1) {
        std::for_each(il1.begin(), il1.end(),
                      [&](auto value) {
                          all_nodes_.insert(std::make_shared<Node>(Node{value}));
                      });

    }

    template<typename N, typename E>
    template<typename InputIt>
    graph<N, E>::graph(InputIt first, InputIt last) : graph() {
        std::for_each(first, last,
                      [&](auto value) {
                          all_nodes_.insert(std::make_shared<Node>(Node{value}));
                      });
    }

    template<typename N, typename E>
    graph<N, E>::graph(graph &&other) noexcept {
        all_nodes_ = std::move(other.all_nodes_);
        all_edges_ = std::move(other.all_edges_);
        if (other != *this) {
            other.all_nodes_.clear();
            other.all_edges_.clear();
        }
    }

    template<typename N, typename E>
    graph<N, E>::graph(const graph &other) {
        std::copy(other.all_nodes_.begin(), other.all_nodes_.end(), all_nodes_.begin(), all_nodes_.end());
        std::copy(other.all_edges_.begin(), other.all_edges_.end(), all_edges_.begin(), all_edges_.end());
    }

    template<typename N, typename E>
    auto graph<N, E>::operator=(const graph &other) -> graph & {
        std::copy(other.all_nodes_.begin(), other.all_nodes_.end(), all_nodes_.begin(), all_nodes_.end());
        std::copy(other.all_edges_.begin(), other.all_edges_.end(), all_edges_.begin(), all_edges_.end());
        return *this;
    }

    template<typename N, typename E>
    auto graph<N, E>::operator=(graph &&other) noexcept -> graph & {
        all_nodes_ = std::move(other.all_nodes_);
        all_edges_ = std::move(other.all_edges_);
        if (other != *this) {
            other.all_nodes_.clear();
            other.all_edges_.clear();
        }
        return *this;
    }

    template<typename N, typename E>
    auto graph<N, E>::insert_node(const N &value) -> bool {
        auto to_insert = std::make_shared<Node>(value);
        if (all_nodes_.find(to_insert) == all_nodes_.end()) {
            all_nodes_.insert(to_insert);
            return true;
        }
        return false;
    }

    template<typename N, typename E>
    auto graph<N, E>::insert_edge(const N &from, const N &to, const E &weight) -> bool {

        auto check_node_from = all_nodes_.find(std::make_shared<Node>(from));
        auto check_node_to = all_nodes_.find(std::make_shared<Node>(to));
        if (check_node_to == all_nodes_.end() or check_node_from == all_nodes_.end()) {
            throw std::runtime_error(
                    "Cannot call gdwg::graph<N, E>::insert_edge when either from or to node does not exist");
        }
        // first we will check if the edge already exists, this will be O(log(n)) due to search time for set

        auto edge_to_insert = std::make_shared<Edge>(*check_node_from, *check_node_to, weight);
        if (all_edges_.find(edge_to_insert) == all_edges_.end()) {
            all_edges_.insert(edge_to_insert);
            // now to update the nodes incoming and outgoing connections for both from and to, O(log(n)) for each
            check_node_from->get()->outgoing.insert(edge_to_insert);
            check_node_to->get()->incoming.insert(edge_to_insert);
            return true;
        }
        return false;
    }

    template<typename N, typename E>
    auto graph<N, E>::replace_node(const N &old_data, const N &new_data) -> bool {
        auto old_node = all_nodes_.find(std::make_shared<Node>(old_data));
        if (old_node == all_nodes_.end()) {
            throw std::runtime_error("Cannot call gdwg::graph<N, E>::replace_node on a node that doesn't exist");
        }
        if (all_nodes_.find(std::make_shared<Node>(new_data)) != all_nodes_.end()) {
            return false;
        }
        // creating the new node
        auto new_node = std::make_shared<Node>(new_data);
        auto updated_in_edges = std::set<std::weak_ptr<Edge>, set_comparator>();
        auto updated_out_edges = std::set<std::weak_ptr<Edge>, set_comparator>();
        for (auto in_edge : old_node->get()->incoming) {
            auto edge_to_insert = std::make_shared<Edge>(
                    Edge{in_edge.lock().get()->from, new_node, in_edge.lock().get()->weight});
            all_edges_.erase(in_edge.lock());
            updated_in_edges.insert(edge_to_insert);
        }
        for (auto out_edge : old_node->get()->outgoing) {
            auto edge_to_insert = std::make_shared<Edge>(Edge{new_node, out_edge.lock().get()->from,
                                                              out_edge.lock().get()->weight});
            all_edges_.erase(out_edge.lock());
            updated_out_edges.insert(edge_to_insert);
        }
        new_node.get()->incoming = updated_in_edges;
        new_node.get()->outgoing = updated_out_edges;
        all_nodes_.insert(new_node);
        all_nodes_.erase(old_node);
        auto z = all_nodes_.find(std::make_shared<Node>(new_data))->get();
        return true;
    }

    template<typename N, typename E>
    auto graph<N, E>::merge_replace_node(const N &old_data, const N &new_data) -> void {
        // we can call replace_node for this since sets naturally do not contain duplicates!
        auto old_node = all_nodes_.find(std::make_shared<Node>(old_data));
        auto new_node = all_nodes_.find(std::make_shared<Node>(new_data));
        if (old_node == all_nodes_.end() || new_node == all_nodes_.end()) {
            throw std::runtime_error(
                    "Cannot call gdwg::graph<N, E>::merge_replace_node on old or new data if they don't exist in the graph");
        }
        // due to the nature of our sets, duplicates are ignored anyways, since sets are compared by elements itself
        // so we just need to update all edge connections recursively
//        auto check_duplicates_incoming = std::set<Raw_Edge, raw_edge_comparator>();
//        for (auto in_edge : new_node->get()->incoming) {
//            check_duplicates_incoming.insert(Raw_Edge{in_edge.lock().get()->from.lock().get()->value,
//                                                      in_edge.lock().get()->to.lock().get()->value,
//                                                      in_edge.lock().get()->weight});
//        }
//        auto check_duplicates_outgoing = std::set<Raw_Edge, raw_edge_comparator>();
//        for (auto out_edge : new_node->get()->incoming) {
//            check_duplicates_incoming.insert(Raw_Edge{out_edge.lock().get()->from.lock().get()->value,
//                                                      out_edge.lock().get()->to.lock().get()->value,
//                                                      out_edge.lock().get()->weight});
//        }
//
//        for (auto in_edge : old_node->get()->incoming) {
//            if (check_duplicates_incoming.find(
//                    Raw_Edge{in_edge.lock().get()->from.lock().get()->value, new_data, in_edge.lock().get()->weight}) !=
//                check_duplicates_incoming.end()) {
//                continue;
//            }
//            check_duplicates_incoming.insert(
//                    Raw_Edge{in_edge.lock().get()->from.lock().get()->value, new_data, in_edge.lock().get()->weight});
//            auto edge_to_insert = std::make_shared<Edge>(
//                    Edge{in_edge.lock().get()->from, new_node, in_edge.lock().get()->weight});
//            new_node->
//            all_edges_.erase(in_edge.lock());
//            updated_in_edges.insert(edge_to_insert);
//        }
//        for (auto out_edge : old_node->get()->outgoing) {
//            auto edge_to_insert = std::make_shared<Edge>(Edge{new_node, out_edge.lock().get()->from,
//                                                              out_edge.lock().get()->weight});
//            all_edges_.erase(out_edge.lock());
//            updated_out_edges.insert(edge_to_insert);
//        }
//        new_node.get()->incoming = updated_in_edges;
//        new_node.get()->outgoing = updated_out_edges;
//        all_nodes_.insert(new_node);
        auto z = all_nodes_.find(std::make_shared<Node>(new_data))->get();
    }


} // namespace gdwg
#endif // GDWG_GRAPH_HPP

