#ifndef GDWG_GRAPH_HPP
#define GDWG_GRAPH_HPP

#include <memory>
#include <set>
#include <unordered_map>
#include <map>
#include <iterator>
#include <numeric>
#include <iostream>
#include <vector>

namespace gdwg {
    template<typename N, typename E>
    class graph {

    public:
        struct value_type {
            N from;
            N to;
            E weight;

            bool operator==(const value_type &v) const {
                return from == v.from && to == v.to && weight == v.weight;
            }
        };

    private:
        struct Node;
        struct Edge;
        struct set_comparator;

        struct Edge {
            Edge() = default;

            Edge(std::weak_ptr<Node> from, std::weak_ptr<Node> to, E weight) : from{from}, to{to},
                                                                               weight{weight} {}

            Edge(std::shared_ptr<Node> from, std::shared_ptr<Node> to, E weight) : from{from}, to{to},
                                                                               weight{weight} {}
            ~Edge() {
                from.reset();
            }

            std::weak_ptr<Node> from;
            std::weak_ptr<Node> to;
            E weight;
        };

        // Nodes store the incoming and outgoing edges RELATED TO THAT NODE
        // so nodes can look like , 1 , incoming 2 -> 1, 3 -> 1, 1 -> 1 and outgoing 1 -> 1, 1 -> 4
        // this is extremely useful for reaching time complexities required when we store informaiton as weak pointers
        // this is because shared pointers dont increase memory load as much as creating a new node, however
        // give us the benefit of time complexity
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

        // comparator can be used for set of edges/nodes in shared/weak pointer form
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

        // this method is used to recreate the edges set for all edges
        // this method just goes through each edge in all_edges and only adds in edges that have alive connections
        // to the shared pointers.
        auto linear_sort_set(
                const std::set<std::shared_ptr<Edge>, set_comparator> to_sort) const -> std::set<std::shared_ptr<Edge>, set_comparator> {
            auto sorted_set = std::set<std::shared_ptr<Edge>, set_comparator>();
            for (auto edge : to_sort) {
                if (edge.get()->from.expired() || edge.get()->to.expired()) {
                    continue;
                }
                sorted_set.insert(edge);
            }
            return sorted_set;
        }

        // this method is identical to above except it goes through the outgoing/incoming connections of the
        // nodes
        auto linear_sort_set(
                const std::set<std::weak_ptr<Edge>, set_comparator> to_sort) const -> std::set<std::weak_ptr<Edge>, set_comparator> {
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

        // because my all_edges structure encapsulates the idea of the iterator (all edges sorted)
        // the iterator is just a wrapper for my all_edges
        class graph_iterator {
        public:
            using value_type = graph<N, E>::value_type;
            using reference = value_type;
            using pointer = void;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::bidirectional_iterator_tag;

            // Iterator constructor
            graph_iterator() = default;

            // Iterator source
            auto operator*() -> reference {
                return this->edge_;
            };

            // Iterator traversal
            auto operator++() -> graph_iterator & {
                auto next_address = this->edge_address_;
                std::advance(next_address, 1);
                auto next_edge = iterator(next_address, iterator_end_);
                edge_ = next_edge.edge_;
                edge_address_ = next_edge.edge_address_;
                return *this;
            };

            auto operator++(int) -> graph_iterator {
                auto next_address = this->edge_address_;
                std::advance(next_address, 1);
                return iterator(next_address, iterator_end_);
            }

            auto operator--() -> graph_iterator & {
                auto next_address = this->edge_address_;
                std::advance(next_address, -1);
                auto next_edge = iterator(next_address, iterator_end_);
                edge_ = next_edge.edge_;
                edge_address_ = next_edge.edge_address_;
                return *this;
            }

            auto operator--(int) -> graph_iterator {
                auto next_address = this->edge_address_;
                std::advance(next_address, -1);
                return iterator(next_address, iterator_end_);
            }

            // Iterator comparison
            auto operator==(graph_iterator const &other) const -> bool {
                return other.edge_address_ == this->edge_address_;
            }

        private:
            // iterator construction happens behind the scenes, so i take 2 values to avoid segmentation faults
            // i take the end iterator of all edges always in order to see if i am going to assign the iterator
            // to the end (this way i dont try to dereference the end of the all_edges_ iterator)
            explicit graph_iterator(typename std::set<std::shared_ptr<Edge>, set_comparator>::iterator edge,
                                    typename std::set<std::shared_ptr<Edge>, set_comparator>::iterator iterator_end) {
                iterator_end_ = iterator_end;
                if (edge == iterator_end) {
                    edge_address_ = iterator_end;
                }else {
                    edge_ = value_type{edge->get()->from.lock().get()->value, edge->get()->to.lock().get()->value,
                                       edge->get()->weight};
                    edge_address_ = edge;
                }
            };

            // iterator variables
            typename std::set<std::shared_ptr<Edge>, set_comparator>::iterator iterator_end_;
            value_type edge_;
            typename std::set<std::shared_ptr<Edge>, set_comparator>::iterator edge_address_;

            friend class graph;
        };

    public:
        using iterator = graph_iterator;
        using const_iterator = graph_iterator;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        graph() = default;

        graph(std::initializer_list<N>);

        template<typename InputIt>
        graph(InputIt first, InputIt last);

        graph(graph &&other) noexcept;

        graph(graph const &other);

        graph(graph &other);

        auto operator=(graph const &other) -> graph &;

        auto operator=(graph &other) -> graph &;

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

        [[nodiscard]] auto is_node(N const &value) const -> bool;

        [[nodiscard]] auto empty() const -> bool;

        [[nodiscard]] auto is_connected(N const &src, N const &dst) const -> bool;

        [[nodiscard]] auto nodes() const -> std::vector<N>;

        [[nodiscard]] auto weights(N const &src, N const &dst) const -> std::vector<E>;

        [[nodiscard]] auto find(N const &src, N const &dst, E const &weight) const -> iterator;

        [[nodiscard]] auto connections(N const &src) const -> std::vector<N>;

        [[nodiscard]] auto begin() const -> iterator;

        [[nodiscard]] auto end() const -> iterator;

        [[nodiscard]] auto operator==(graph const &other) const -> bool;

        [[nodiscard]] auto operator==(graph const &other) -> bool;

        template<typename node, typename edge>
        friend auto operator<<(std::ostream &os, graph<node, edge> const &g) -> std::ostream &;

    private:
        // set keeps order so O(logn) lookups due RB trees
        // nodes contain a list of all their incoming and outgoing connections, and the set of edges
        // can be used for book keeping
        // due to nodes containing a set of weak_ptrs for both incoming/outgoing connections, when a edge
        // is removed from the all_Edges set, all nodes assosicated will have corresponding connections expired too
        // only book keeping is required for managing the incoming/outgoing connections on nodes
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
        std::for_each(other.all_nodes_.begin(), other.all_nodes_.end(), [&](auto node) { all_nodes_.insert(node); });
        std::for_each(other.all_edges_.begin(), other.all_edges_.end(), [&](auto edge) { all_edges_.insert(edge); });
    }

    template<typename N, typename E>
    graph<N, E>::graph(graph &other) {
        std::for_each(other.all_nodes_.begin(), other.all_nodes_.end(), [&](auto node) { all_nodes_.insert(node); });
        std::for_each(other.all_edges_.begin(), other.all_edges_.end(), [&](auto edge) { all_edges_.insert(edge); });
    }

    template<typename N, typename E>
    auto graph<N, E>::operator=(const graph &other) -> graph & {
        std::for_each(other.all_nodes_.begin(), other.all_nodes_.end(), [&](auto node) { all_nodes_.insert(node); });
        std::for_each(other.all_edges_.begin(), other.all_edges_.end(), [&](auto edge) { all_edges_.insert(edge); });
        return *this;
    }

    template<typename N, typename E>
    auto graph<N, E>::operator=(graph &other) -> graph & {
        std::for_each(other.all_nodes_.begin(), other.all_nodes_.end(), [&](auto node) { all_nodes_.insert(node); });
        std::for_each(other.all_edges_.begin(), other.all_edges_.end(), [&](auto edge) { all_edges_.insert(edge); });
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
        // in order to correctly update the memory address for all the incoming/outgoing nodes we need to insert a new
        // node, with the new value, and insert into it the old updated connections,
        auto new_node = std::make_shared<Node>(new_data);
        old_node->get()->incoming = linear_sort_set(old_node->get()->incoming);
        for (auto edge : old_node->get()->incoming) {
            auto insertion_edge = Edge{edge.lock().get()->from.lock(), new_node, edge.lock().get()->weight};

            edge.lock().get()->to = new_node;
            new_node.get()->incoming.insert(edge);
        }
        old_node->get()->outgoing = linear_sort_set(old_node->get()->outgoing);
        for (auto edge : old_node->get()->outgoing) {
            auto insertion_edge = Edge{new_node, edge.lock().get()->to.lock(), edge.lock().get()->weight};
            edge.lock().get()->from = new_node;
            new_node.get()->outgoing.insert(edge);
        }
        all_nodes_.insert(new_node);
        all_nodes_.erase(old_node);
        all_edges_ = linear_sort_set(all_edges_);
        return true;
    }

    template<typename N, typename E>
    auto graph<N, E>::merge_replace_node(const N &old_data, const N &new_data) -> void {
        // we can call replace_node for this since sets naturally do not contain duplicates!
        if (old_data == new_data) {
            return;
        }
        auto old_node = all_nodes_.find(std::make_shared<Node>(old_data));
        auto new_node = all_nodes_.find(std::make_shared<Node>(new_data));
        if (old_node == all_nodes_.end() || new_node == all_nodes_.end()) {
            throw std::runtime_error(
                    "Cannot call gdwg::graph<N, E>::merge_replace_node on old or new data if they don't exist in the graph");
        }
        all_edges_ = linear_sort_set(all_edges_);
        // remake edges + new node outgoing set in order to maintain order and delete junk memory etc.
        auto new_edges = std::set<std::shared_ptr<Edge>, set_comparator>();
        new_node->get()->outgoing.clear();
        // go through each edge,
        // 1. if the source node of that edge is equal to the old data, we want to re-create a new edge with
        //    the new node as the new source, and updating the connection for the destination nodes incoming connection
        //    finally insert it into the all edges
        // 2. if the destination node of that edge is equal to the old data we want to re-create a new edge with
        //    the new node as the destination, and updating the connection for the source node incoming connection
        //    finally insert it into the all edges
        // 3. edge unrelated? -> add it in as it is no need to modify anything
        // to handle double old node -> old node edges, i will simply check if that case has occurred and insert
        // a self edge in that case.
        for (auto edge : all_edges_) {
            auto replaced = false;
            if (edge.get()->from.lock().get()->value == old_data) {
                auto replaced_destination = edge.get()->to.lock();
                if (replaced_destination.get()->value == old_data) {
                    replaced_destination = *new_node;
                    replaced = true;
                }
                // we want to create new edge from the current node, replacing the from value
                auto new_edge = std::make_shared<Edge>(Edge{*new_node, replaced_destination, edge.get()->weight});
                // now we want to fix connections on both nodes
                new_node->get()->outgoing.insert(new_edge);
                auto to_node = all_nodes_.find(std::make_shared<Node>(edge.get()->to.lock().get()->value));
                to_node->get()->incoming.insert(new_edge);
                if (replaced) {
                    to_node->get()->outgoing.insert(new_edge);
                }
                new_edges.insert(new_edge);
                continue;
            }
            if (edge.get()->to.lock().get()->value == old_data) {
                auto replaced_destination = edge.get()->from.lock();
                if (replaced_destination.get()->value == old_data) {
                    replaced_destination = *new_node;
                    replaced = true;
                }
                // we want to create new edge from the current node, replacing the from value
                auto new_edge = std::make_shared<Edge>(Edge{replaced_destination, *new_node, edge.get()->weight});
                // now we want to fix connections on both nodes
                new_node->get()->incoming.insert(new_edge);
                auto to_node = all_nodes_.find(std::make_shared<Node>(edge.get()->from.lock().get()->value));
                to_node->get()->outgoing.insert(new_edge);
                if (replaced) {
                    to_node->get()->incoming.insert(new_edge);
                }
                new_edges.insert(new_edge);
                continue;
            }
            auto new_edge = std::make_shared<Edge>(
                    Edge{edge.get()->from.lock(), edge.get()->to.lock(), edge.get()->weight});

            edge.get()->from.lock().get()->outgoing = linear_sort_set(edge.get()->from.lock().get()->outgoing);
            edge.get()->to.lock().get()->incoming = linear_sort_set(edge.get()->to.lock().get()->incoming);

            edge.get()->from.lock().get()->outgoing.insert(new_edge);
            edge.get()->to.lock().get()->incoming.insert(new_edge);
            new_edges.insert(new_edge);
        }
        all_nodes_.erase(old_node);
        all_edges_ = new_edges;
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
        auto ret = all_edges_.size() == 1 ? iterator(all_edges_.end(), all_edges_.end()) : i++;
        all_edges_.erase(*i.edge_address_);
        return ret;
    }

    template<typename N, typename E>
    auto graph<N, E>::erase_edge(graph::iterator i, graph::iterator s) -> graph::iterator {
        while (i != s) {
            auto next_validated = i++;
            if(i != s){
                all_edges_.erase(*i.edge_address_);
            }
            i = next_validated;
        }

        return s;
    }

    template<typename N, typename E>
    auto graph<N, E>::clear() noexcept -> void {
        // erasing all nodes in turn erases all edges
        all_nodes_.clear();
        all_edges_.clear();
    }

    template<typename N, typename E>
    auto graph<N, E>::is_node(const N &value) const -> bool {
        return all_nodes_.find(std::make_shared<Node>(value)) != all_nodes_.end();
    }

    template<typename N, typename E>
    auto graph<N, E>::empty() const -> bool {
        return all_nodes_.size() == 0;
    }

    template<typename N, typename E>
    auto graph<N, E>::is_connected(const N &src, const N &dst) const -> bool {
        // we can just check the outgoing edges of src to see if dst is in there at all and we can also use this too
        auto from_node = all_nodes_.find(std::make_shared<Node>(src));
        auto to_node = all_nodes_.find(std::make_shared<Node>(dst));
        if (from_node == all_nodes_.end() || to_node == all_nodes_.end()) {
            throw std::runtime_error(
                    "Cannot call gdwg::graph<N, E>::is_connected if src or dst node don't exist in the graph");
        }
        from_node->get()->outgoing = linear_sort_set(from_node->get()->outgoing);
        from_node->get()->incoming = linear_sort_set(from_node->get()->incoming);
        to_node->get()->outgoing = linear_sort_set(to_node->get()->outgoing);
        to_node->get()->incoming = linear_sort_set(to_node->get()->incoming);
        for (auto edge : from_node->get()->outgoing) {
            if (edge.expired()) {
                continue;
            }
            if (edge.lock().get()->to.lock().get()->value == dst) {
                return true;
            }
        }
        return false;
    }

    template<typename N, typename E>
    auto graph<N, E>::nodes() const -> std::vector<N> {
        auto return_vector = std::vector<N>();
        for (auto node : all_nodes_) {
            return_vector.push_back(node.get()->value);
        }
        return return_vector;
    }

    template<typename N, typename E>
    auto graph<N, E>::weights(const N &src, const N &dst) const -> std::vector<E> {
        auto return_vector = std::vector<E>();
        auto from_node = all_nodes_.find(std::make_shared<Node>(src));
        auto to_node = all_nodes_.find(std::make_shared<Node>(dst));
        if (from_node == all_nodes_.end() || to_node == all_nodes_.end()) {
            throw std::runtime_error(
                    "Cannot call gdwg::graph<N, E>::weights if src or dst node don't exist in the graph");
        }
        // O(e) = size of edges stored in the outgoing (slightly less than e)
        for (auto edge : from_node->get()->outgoing) {
            if (edge.expired()) {
                continue;
            }
            if (edge.lock().get()->to.expired()) {
                continue;
            }
            if (edge.lock().get()->to.lock().get()->value == dst) {
                return_vector.push_back(edge.lock().get()->weight);
            }
        }
        return return_vector;
    }

    template<typename N, typename E>
    auto graph<N, E>::find(const N &src, const N &dst, const E &weight) const -> graph::iterator {
        // only o(log(e))
        return iterator(all_edges_.find(std::make_shared<Edge>(Edge{std::make_shared<Node>(src), std::make_shared<Node>(dst), weight})), all_edges_.end());
    }

    template<typename N, typename E>
    auto graph<N, E>::connections(const N &src) const -> std::vector<N> {
        auto node_set = std::set<N>();
        auto from_node = all_nodes_.find(std::make_shared<Node>(src));
        if (from_node == all_nodes_.end()) {
            throw std::runtime_error(
                    "Cannot call gdwg::graph<N, E>::connections if src doesn't exist in the graph");
        }
        for (auto edge : from_node->get()->outgoing) {
            if (edge.expired()) {
                continue;
            }
            if (edge.lock().get()->to.expired() || edge.lock().get()->from.expired()) {
                continue;
            }
            node_set.insert(edge.lock().get()->to.lock().get()->value);
        }
        return std::vector<N>(node_set.begin(), node_set.end());
    }

    template<typename N, typename E>
    auto graph<N, E>::begin() const -> graph::iterator {
        if (all_edges_.empty()) {
            return iterator(all_edges_.end(), all_edges_.end());
        }
        // here we can just perform our checks to skip over dead nodes (since it's a const method we cant remove them here)
        auto ret = all_edges_.begin();
        while(ret != all_edges_.end() && (ret->get()->from.expired() || ret->get()->to.expired())){
            ret++;
        }
        return iterator(ret, all_edges_.end());
    }

    template<typename N, typename E>
    auto graph<N, E>::end() const -> graph::iterator {
        return iterator(all_edges_.end(), all_edges_.end());
    }

    template<typename N, typename E>
    auto graph<N, E>::operator==(const graph &other) const -> bool {
        auto other_cmp = linear_sort_set(other.all_edges_);
        auto cmp = linear_sort_set(all_edges_);
        // first check all nodes equal
        auto nodes_equal = std::equal(other.all_nodes_.begin(), other.all_nodes_.end(), all_nodes_.begin(),
                                      all_nodes_.end(),
                                      [&](auto node1, auto node2) {
                                          return node1.get()->value == node2.get()->value;
                                      });
        auto edges_equal = std::equal(cmp.begin(), cmp.end(), other_cmp.begin(),
                                      other_cmp.end(),
                                      [&](auto edge1, auto edge2) {
                                          return edge1.get()->from.lock().get()->value ==
                                                 edge2.get()->from.lock().get()->value &&
                                                 edge1.get()->to.lock().get()->value ==
                                                 edge2.get()->to.lock().get()->value &&
                                                 edge1.get()->weight == edge2.get()->weight;
                                      });
        return nodes_equal && edges_equal;
    }

    template<typename N, typename E>
    auto graph<N, E>::operator==(const graph &other) -> bool {
        auto other_cmp = linear_sort_set(other.all_edges_);
        auto cmp = linear_sort_set(all_edges_);
        // first check all nodes equal
        auto nodes_equal = std::equal(other.all_nodes_.begin(), other.all_nodes_.end(), all_nodes_.begin(),
                                      all_nodes_.end(),
                                      [&](auto node1, auto node2) {
                                          return node1.get()->value == node2.get()->value;
                                      });
        auto edges_equal = std::equal(cmp.begin(), cmp.end(), other_cmp.begin(),
                                      other_cmp.end(),
                                      [&](auto edge1, auto edge2) {
                                          return edge1.get()->from.lock().get()->value ==
                                                 edge2.get()->from.lock().get()->value &&
                                                 edge1.get()->to.lock().get()->value ==
                                                 edge2.get()->to.lock().get()->value &&
                                                 edge1.get()->weight == edge2.get()->weight;
                                      });
        return nodes_equal && edges_equal;
    }

    template<typename N, typename E>
    auto operator<<(std::ostream &os, const graph<N, E> &g) -> std::ostream & {
        for (auto node : g.all_nodes_) {
            os << node.get()->value << " (" << "\n";
            // add all the edges appropriately now
            for (auto edge : node.get()->outgoing) {
                if (edge.expired() || edge.lock().get()->to.expired() || edge.lock().get()->from.expired()) {
                    continue;
                }
                if (g.all_edges_.find(edge.lock()) == g.all_edges_.end()) {
                    continue;
                }
                os << "  " << edge.lock().get()->to.lock().get()->value << " | " << edge.lock().get()->weight << "\n";
            }

            os << ")" << "\n";

        }
        return os;
    }

} // namespace gdwg
#endif // GDWG_GRAPH_HPP
