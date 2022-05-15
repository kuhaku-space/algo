#pragma once
#include "template/template.hpp"

template <class T>
struct persistent_queue {
  private:
    struct Node {
        using pointer = Node *;
        T val;
        std::vector<pointer> prev;

        Node(T _val) : val(_val), prev() {}
    };

  public:
    using node_pointer = typename Node::pointer;

    constexpr persistent_queue() : _size(), root() {}
    constexpr persistent_queue(int n, node_pointer _root) : _size(n), root(_root) {}

    constexpr int size() const { return this->_size; }

    T top() const {
        node_pointer node = this->root;
        int k = 0;
        while ((this->_size - 1) >> k) {
            if ((this->_size - 1) >> k & 1) { node = node->prev[k]; }
            ++k;
        }
        return node->val;
    }
    T front() const { return this->top(); }

    persistent_queue push(T val) const {
        node_pointer new_node = new Node(val);
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
    persistent_queue emplace(T val) const { return this->push(val); }

    persistent_queue pop() const { return persistent_queue(this->_size - 1, root); }

  private:
    int _size;
    node_pointer root;
};
