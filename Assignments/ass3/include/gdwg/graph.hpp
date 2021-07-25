#ifndef GDWG_GRAPH_HPP
#define GDWG_GRAPH_HPP

#include <memory>
#include <set>
#include <unordered_map>
#include <map>
#include <iterator>
#include <numeric>

namespace gdwg {
    template<typename N, typename E>
    class graph {

    private:
        struct Node;
        struct Edge;
        struct set_comparator;

        struct Edge {
            Edge() = default;

            Edge(std::weak_ptr<Node> from, std::weak_ptr<Node> to, E weight) : from{from}, to{to},
                                                                               weight{weight} {}

            ~Edge() {
                from.reset();
            }

            std::weak_ptr<Node> from;
            std::weak_ptr<Node> to;
            E weight;
        };

//        struct Edge_Iterator_Type{
//
//        };

        struct Node {
            Node() = default;

            explicit Node(N value) : value{value} {
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
            auto operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const -> bool {
                return lhs.get()->value < rhs.get()->value;
            }

            auto operator()(const std::weak_ptr<Node> &lhs, const std::weak_ptr<Node> &rhs) const -> bool {
                return lhs.lock().get()->value < rhs.lock().get()->value;
            }

            auto operator()(const Node &lhs, const Node &rhs) const -> bool {
                return lhs->value < rhs->value;
            }

            // in order to do this in O(log(N) time we need edges to be sorted properly
            // sort first by from, to, weight in that order
            auto operator()(const std::shared_ptr<Edge> &lhs, const std::shared_ptr<Edge> &rhs) const -> bool {
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

            auto operator()(const std::weak_ptr<Edge> &lhs, const std::weak_ptr<Edge> &rhs) const -> bool {
                if (lhs.lock().get()->from.lock().get()->value != rhs.lock().get()->from.lock().get()->value) {
                    return lhs.lock().get()->from.lock().get()->value < rhs.lock().get()->from.lock().get()->value;
                }
                if (lhs.lock().get()->to.lock().get()->value != rhs.lock().get()->to.lock().get()->value) {
                    return lhs.lock().get()->to.lock().get()->value < rhs.lock().get()->to.lock().get()->value;
                }
                return lhs.lock().get()->weight < rhs.lock().get()->weight;
            }

            auto operator()(const Edge &lhs, const Edge &rhs) const -> bool {
                if (lhs.from.lock().get()->value != rhs.from.lock().get()->value) {
                    return lhs.from.lock().get()->value < rhs.from.lock().get()->value;
                }
                if (lhs.to.lock().get()->value != rhs.to.lock().get()->value) {
                    return lhs.to.lock().get()->value < rhs.to.lock().get()->value;
                }
                return lhs.weight < rhs.weight;
            }
        };

        auto linear_sort_set(
                std::set<std::shared_ptr<Edge>, set_comparator> to_sort) -> std::set<std::shared_ptr<Edge>, set_comparator> {
            auto sorted_set = std::set<std::shared_ptr<Edge>, set_comparator>();
            for (auto edge : to_sort) {
                if (edge.get()->from.expired() || edge.get()->to.expired()) {
                    continue;
                }
                sorted_set.insert(edge);
            }
            return sorted_set;
        }

        auto linear_sort_set(
                std::set<std::weak_ptr<Edge>, set_comparator> to_sort) -> std::set<std::weak_ptr<Edge>, set_comparator> {
            auto sorted_set = std::set<std::weak_ptr<Edge>, set_comparator>();
            for (auto edge : to_sort) {
                if (edge.expired()) {
                    continue;
                }
                if (edge.lock().get()->from.expired() || edge.lock().get()->to.expired()) {
                    continue;
                }
                sorted_set.insert(edge);
            }
            return sorted_set;
        }

        class graph_iterator {
        public:
            using value_type = struct value_type {
                N from;
                N to;
                E weight;
            };;
            using reference = value_type;
            using pointer = void;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;

            // Iterator constructor
            graph_iterator() = default;

            // Iterator source
            auto operator*() -> reference;

            // Iterator traversal
            auto operator++() -> graph_iterator &;

            auto operator++(int) -> graph_iterator;

            auto operator--() -> graph_iterator &;

            auto operator--(int) -> graph_iterator;

            // Iterator comparison
            auto operator==(graph_iterator const &other) -> bool;

        private:
            explicit graph_iterator(Edge* edge);
            Edge* edge_;
            friend class graph;
        };

    public:
        using iterator = graph_iterator;
        using const_iterator = graph_iterator;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
        struct value_type {
            N from;
            N to;
            E weight;
        };

        graph() = default;

        graph(std::initializer_list<N>);

        template<typename InputIt>
        graph(InputIt first, InputIt last);

        graph(graph &&other) noexcept;

        graph(graph const &other);

        auto operator=(graph const &other) -> graph &;

        auto operator=(graph &&other) noexcept -> graph &;

        // Your member functions go here
        auto insert_node(N const &value) -> bool;

        auto insert_edge(N const &from, N const &to, E const &weight) -> bool;

        auto replace_node(N const &old_data, N const &new_data) -> bool;

        auto merge_replace_node(N const &old_data, N const &new_data) -> void;

        auto erase_node(N const &value) -> bool;

        auto erase_edge(N const &src, N const &dst, E const &weight) -> bool;

        auto erase_edge(iterator i) -> iterator;

        auto erase_edge(iterator i, iterator s) -> iterator;

        auto clear() noexcept -> void;

        [[nodiscard]] auto is_node(N const &value) -> bool;

        [[nodiscard]] auto empty() -> bool;

        [[nodiscard]] auto is_connected(N const &src, N const &dst) -> bool;

        [[nodiscard]] auto nodes() -> std::vector<N>;

        [[nodiscard]] auto weights(N const &src, N const &dst) -> std::vector<E>;

        [[nodiscard]] auto find(N const &src, N const &dst, E const &weight) -> iterator;

        [[nodiscard]] auto connections(N const &src) -> std::vector<N>;

        [[nodiscard]] auto begin() const -> iterator;

        [[nodiscard]] auto end() const -> iterator;

        [[nodiscard]] auto operator==(graph const &other) -> bool;

        template<typename node, typename edge>
        friend auto operator<<(std::ostream &os, graph<node, edge> const &g) -> std::ostream &;

//        friend auto operator<<(std::ostream &os, graph const &g) -> std::ostream &;

    private:
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
        old_node->get()->value = new_data;
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
        all_nodes_.erase(old_node);
    }

    template<typename N, typename E>
    auto graph<N, E>::erase_node(const N &value) -> bool {
        auto node_to_delete = all_nodes_.find(std::make_shared<Node>(value));
        if (node_to_delete == all_nodes_.end()) {
            return false;
        } else {
            all_nodes_.erase(node_to_delete);
            all_edges_ = linear_sort_set(all_edges_);
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
        auto edge_to_remove = all_edges_.find(
                std::make_shared<Edge>(Edge{*from, *to, weight}));
        if (edge_to_remove == all_edges_.end()) {
            return false;
        }
        all_edges_.erase(*edge_to_remove);
        return true;
    }

    template<typename N, typename E>
    auto graph<N, E>::erase_edge(graph::iterator i) -> graph::iterator {
        auto ret = i++;
        all_edges_.erase(*i);
        return ret;
    }

    template<typename N, typename E>
    auto graph<N, E>::erase_edge(graph::iterator i, graph::iterator s) -> graph::iterator {
        auto ret = s;
        while (i != s) {
            all_edges_.remove(*i);
            i++;
        }

        return end() ? i == end() : ret;
    }

    template<typename N, typename E>
    auto graph<N, E>::clear() noexcept -> void {
        // erasing all nodes in turn erases all edges
        all_nodes_.clear();
        all_edges_.clear();
    }

    template<typename N, typename E>
    auto graph<N, E>::is_node(const N &value) -> bool {
        return all_nodes_.find(std::make_shared<Node>(value)) != all_nodes_.end();
    }

    template<typename N, typename E>
    auto graph<N, E>::empty() -> bool {
        return all_nodes_.size() == 0;
    }

    template<typename N, typename E>
    auto graph<N, E>::is_connected(const N &src, const N &dst) -> bool {
        // we can just check the outgoing edges of src to see if dst is in there at all and we can also use this too
        auto from_node = all_nodes_.find(std::make_shared<Node>(src));
        auto to_node = all_nodes_.find(std::make_shared<Node>(dst));
        if (from_node == all_nodes_.end() || to_node == all_nodes_.end()) {
            throw std::runtime_error(
                    "Cannot call gdwg::graph<N, E>::is_connected if src or dst node don't exist in the graph");
        }
        from_node->get()->outgoing = linear_sort_set(from_node->get()->outgoing);
        to_node->get()->incoming = linear_sort_set(from_node->get()->incoming);
        for (auto edge : from_node->get()->outgoing) {
            if (edge.lock().get()->to.lock().get()->value == dst) {
                return true;
            }
        }
        return false;
    }

    template<typename N, typename E>
    auto graph<N, E>::nodes() -> std::vector<N> {
        auto return_vector = std::vector<N>();
        for (auto node : all_nodes_) {
            return_vector.push_back(node.get()->value);
        }
        return return_vector;
    }

    template<typename N, typename E>
    auto graph<N, E>::weights(const N &src, const N &dst) -> std::vector<E> {
        auto return_vector = std::vector<E>();
        auto from_node = all_nodes_.find(std::make_shared<Node>(src));
        auto to_node = all_nodes_.find(std::make_shared<Node>(dst));
        if (from_node == all_nodes_.end() || to_node == all_nodes_.end()) {
            throw std::runtime_error(
                    "Cannot call gdwg::graph<N, E>::weights if src or dst node don't exist in the graph");
        }
        // O(e) = size of edges stored in the outgoing (slightly less than e)
        for (auto edge : from_node->get()->outgoing) {
            if (edge.lock().get()->to.lock().get()->value == dst) {
                return_vector.push_back(edge.lock().get()->weight);
            }
        }
        return return_vector;
    }

    template<typename N, typename E>
    auto graph<N, E>::find(const N &src, const N &dst, const E &weight) -> graph::iterator {
        // only o(log(e))
        return all_edges_.find(Edge{std::make_shared<Node>(src), std::make_shared<Node>(dst), weight});
    }

    template<typename N, typename E>
    auto graph<N, E>::connections(const N &src) -> std::vector<N> {
        auto node_set = std::set<N>();
        auto from_node = all_nodes_.find(std::make_shared<Node>(src));
        if (from_node == all_nodes_.end()) {
            throw std::runtime_error(
                    "Cannot call gdwg::graph<N, E>::weights if src or dst node don't exist in the graph");
        }
        from_node->get()->outgoing = linear_sort_set(from_node->get()->outgoing);
        for (auto edge : from_node->get()->outgoing) {
            node_set.insert(edge.lock().get()->to.lock().get()->value);
        }
        return std::vector<N>(node_set.begin(), node_set.end());
    }

    template<typename N, typename E>
    auto graph<N, E>::begin() const -> graph::iterator {
        return all_edges_.begin();
    }

    template<typename N, typename E>
    auto graph<N, E>::end() const -> graph::iterator {
        return all_edges_.end();
    }

    template<typename N, typename E>
    auto graph<N, E>::operator==(const graph &other) -> bool {
        // quick cleanups of junk edges
        auto other_cmp = linear_sort_set(other.all_edges_);
        auto cmp = linear_sort_set(all_edges_);
        return std::equal(other.all_nodes_.begin(), other.all_nodes_.end(), all_nodes_.begin(), all_nodes_.end()) &&
               std::equal(cmp.begin(), cmp.end(), other_cmp.begin(), other_cmp.end());
    }

    template<typename N, typename E>
    auto operator<<(std::ostream &os, const graph<N, E> &g) -> std::ostream & {
        os << "(";
        for (auto node : g.all_nodes_) {
            os << node.get()->value << "(" << std::endl;
            // add all the edges appropriately now
            for (auto edge : node.get()->outgoing) {
                if (edge.expired() || edge.lock().get()->to.expired() || edge.lock().get()->from.expired()) {
                    continue;
                }
                os << edge.lock().get()->to.lock().get()->value << " | " << edge.lock().get()->weight << std::endl;
            }

            os << ")" << std::endl;

        }
        os << ")";
        return os;
    }


} // namespace gdwg
#endif // GDWG_GRAPH_HPP

