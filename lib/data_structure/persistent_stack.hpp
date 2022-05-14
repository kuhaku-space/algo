#pragma once
#include "template/template.hpp"

template <class T>
struct persistent_stack {
  private:
    struct Node {
        using pointer = Node *;
        T val;
        pointer prev;
    };

  public:
    using node_pointer = Node::pointer;

    constexpr persistent_stack() : root(nullptr) {}
    constexpr persistent_stack(node_pointer _root) : root(_root) {}

    T top() const {
        assert(this->root);
        return this->root->val;
    }

    persistent_stack push(T val) const { return persistent_stack(new Node{val, this->root}); }

    persistent_stack pop() const {
        assert(this->root);
        return persistent_stack(this->root->prev);
    }

  private:
    node_pointer root;
};
