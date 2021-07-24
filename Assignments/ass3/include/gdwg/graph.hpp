#ifndef GDWG_GRAPH_HPP
#define GDWG_GRAPH_HPP

#include <memory>
#include <set>
#include <unordered_map>
#include <map>
#include <iterator>
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

        auto erase_node(N const &value) -> bool;

        auto erase_edge(N const &src, N const &dst, E const &weight) -> bool;

        auto erase_edge(iterator i) -> iterator;

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
                if (lhs.from.lock().get()->value != rhs.from.lock().get()->value) {
                    return lhs.from.lock().get()->value < rhs.from.lock().get()->value;
                }
                if (lhs.to.lock().get()->value != rhs.to.lock().get()->value) {
                    return lhs.to.lock().get()->value < rhs.to.lock().get()->value;
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
        auto debug() -> void {
            std::cout << "NODES: " << all_nodes_.size() << std::endl;
            for (auto node : all_nodes_) {
                std::cout << node->value << std::endl;
                std::cout << "incoming" << std::endl;
                for (auto edge : node->incoming) {
                    std::cout << edge.lock().get()->from.lock().get()->value << " -> "
                              << edge.lock().get()->to.lock().get()->value << ",   weight: "
                              << edge.lock().get()->weight << std::endl;
                }
                std::cout << std::endl;
                std::cout << "outgoing" << std::endl;
                for (auto edge : node->outgoing) {
                    std::cout << edge.lock().get()->from.lock().get()->value << " -> "
                              << edge.lock().get()->to.lock().get()->value << ",   weight: "
                              << edge.lock().get()->weight << std::endl;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            std::cout << "EDGES" << std::endl;
            for (auto edge : all_edges_) {
                std::cout << edge.get()->from.lock().get()->value << " -> " << edge.get()->to.lock().get()->value
                          << ",   weight: " << edge.get()->weight << std::endl;
            }
        }

        auto linear_sort_set(
                std::set<std::shared_ptr<Edge>, set_comparator> to_sort) -> std::set<std::shared_ptr<Edge>, set_comparator> {
            auto sorted_set = std::set<std::shared_ptr<Edge>, set_comparator>();
            for (auto edge : to_sort) {
                sorted_set.insert(edge);
            }
            return sorted_set;
        }

        auto linear_sort_set(
                std::set<std::weak_ptr<Edge>, set_comparator> to_sort) -> std::set<std::weak_ptr<Edge>, set_comparator> {
            auto sorted_set = std::set<std::weak_ptr<Edge>, set_comparator>();
            for (auto edge : to_sort) {
                sorted_set.insert(edge);
            }
            return sorted_set;
        }

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
        debug();
        old_node->get()->value = new_data;
        std::cout << "__________________________________________________" << std::endl;
        std::cout << "__________________________________________________" << std::endl;
        std::cout << "__________________________________________________" << std::endl;
        debug();
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
        // to do this properly we will go through each inc/out connection and update the pointers appropriately to new node
        // incoming = inc -> old
        // check if a duplicate edge exists first
        auto existing_connections = std::set<Edge, set_comparator>();
        for (auto edge : new_node->get()->incoming) {
            existing_connections.insert(
                    Edge{edge.lock().get()->from, edge.lock().get()->to, edge.lock().get()->weight});
        }
        for (auto edge : new_node->get()->outgoing) {
            existing_connections.insert(
                    Edge{edge.lock().get()->from, edge.lock().get()->to, edge.lock().get()->weight});
        }

        for (auto edge : old_node->get()->incoming) {
            auto insertion_edge = Edge{edge.lock().get()->from.lock(), *new_node, edge.lock().get()->weight};
            if (existing_connections.find(insertion_edge) != existing_connections.end()) {
                continue;
            }
            edge.lock().get()->to = *new_node;
            new_node->get()->incoming.insert(edge);
            existing_connections.insert(insertion_edge);
        }
        for (auto edge : old_node->get()->outgoing) {
            auto insertion_edge = Edge{*new_node, edge.lock().get()->to.lock(), edge.lock().get()->weight};
            if (existing_connections.find(insertion_edge) != existing_connections.end()) {
                continue;
            }
            edge.lock().get()->from = *new_node;
            new_node->get()->outgoing.insert(edge);
            existing_connections.insert(insertion_edge);
        }
        // final cleanup is to remove any edges with old_node in the new node (the final remnants)
        auto edge_to_remove_incoming = std::set<std::weak_ptr<Edge>, set_comparator>();
        for (auto edge : new_node->get()->incoming) {
            if (edge.lock().get()->from.lock().get()->value == old_data) {
                edge_to_remove_incoming.insert(edge);
            }
        }
        for (auto edge : edge_to_remove_incoming) {
            new_node->get()->incoming.erase(edge);
            all_edges_.erase(edge.lock());
        }

        auto edge_to_remove_outgoing = std::set<std::weak_ptr<Edge>, set_comparator>();
        for (auto edge : new_node->get()->outgoing) {
            if (edge.lock().get()->to.lock().get()->value == old_data) {
                edge_to_remove_outgoing.insert(edge);
            }
        }
        for (auto edge : edge_to_remove_outgoing) {
            new_node->get()->outgoing.erase(edge);
            all_edges_.erase(edge.lock());
        }
        // since i changed the nodes without updating the set again, i will re-sort my set
        all_nodes_.erase(old_node);
        all_edges_ = linear_sort_set(all_edges_);
        for (auto node : all_nodes_) {
            node.get()->incoming = linear_sort_set(node.get()->incoming);
            node.get()->outgoing = linear_sort_set(node.get()->outgoing);
        }
    }

    template<typename N, typename E>
    auto graph<N, E>::erase_node(const N &value) -> bool {
        auto node_to_delete = all_nodes_.find(std::make_shared<Node>(value));
        if (node_to_delete == all_nodes_.end()) {
            return false;
        } else {
            // delete the edges in all the incoming/outgoing for that node
            for (auto edge : node_to_delete->get()->incoming) {
                // delete this edge from the from node's outgoing
                edge.lock().get()->from.lock().get()->outgoing.erase(edge);
                all_edges_.erase(edge.lock());
            }
            for (auto edge : node_to_delete->get()->outgoing) {
                // delete this edge from the from node's outgoing
                edge.lock().get()->to.lock().get()->incoming.erase(edge);
                all_edges_.erase(edge.lock());
            }
            all_nodes_.erase(node_to_delete);
            return true;
        }
    }

    template<typename N, typename E>
    auto graph<N, E>::erase_edge(const N &src, const N &dst, const E &weight) -> bool {
        auto from = all_nodes_.find(std::make_shared<Node>(src));
        auto to = all_nodes_.find(std::make_shared<Node>(dst));
        if (from == all_nodes_.end() || to == all_nodes_.end()) {
            throw std::runtime_error(
                    "Cannot call gdwg::graph<N, E>::erase_edge on src or dst if they don't exist in the graph");
        }
        // we want to get the outgoing -> incoming edge for src and dst delete them there, then delete the edge
        // each find + removal = o(log(N)) due to set implementation
        auto edge_to_remove = all_edges_.find(
                std::make_shared<Edge>(Edge{*from, *to, weight}));
        if (edge_to_remove == all_edges_.end()) {
            return false;
        }
//        auto z = edge_to_remove->get();
        // now that we have the edge to remove, we want to remove it from the OUTGOING of the src, and INCOMING of dst
        // and then simply remove it from all_edges
        // total O(e) + O(log(n))
        from->get()->outgoing.erase(*edge_to_remove);
        to->get()->incoming.erase(*edge_to_remove);
        all_edges_.erase(*edge_to_remove);
        return true;
    }


} // namespace gdwg
#endif // GDWG_GRAPH_HPP

