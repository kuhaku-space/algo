#pragma once
#include <vector>

template <class T>
struct persistent_queue {
  private:
    struct _node {
        using pointer = _node *;
        T val;
        std::vector<pointer> prev;

        _node(T _val) : val(_val), prev() {}
    };

  public:
    using node_pointer = typename _node::pointer;

    constexpr persistent_queue() : _size(), root() {}
    constexpr persistent_queue(int n, node_pointer _root) : _size(n), root(_root) {}

    constexpr int size() const { return _size; }

    T top() const {
        node_pointer node = root;
        int k = 0;
        while ((_size - 1) >> k) {
            if ((_size - 1) >> k & 1) { node = node->prev[k]; }
            ++k;
        }
        return node->val;
    }
    T front() const { return top(); }

    persistent_queue push(T val) const {
        node_pointer new_node = new _node(val);
        node_pointer node = root;
        new_node->prev.emplace_back(node);
        int k = 0;
        while (node) {
            if (node->prev.size() > k) node = node->prev[k++];
            else node = nullptr;
            new_node->prev.emplace_back(node);
        }
        return persistent_queue(_size + 1, new_node);
    }
    persistent_queue emplace(T val) const { return push(val); }

    persistent_queue pop() const { return persistent_queue(_size - 1, root); }

  private:
    int _size;
    node_pointer root;
};
