#pragma once
#include <cassert>

/// @brief 永続スタック
template <class T>
struct persistent_stack {
  private:
    struct _node {
        using pointer = _node *;
        T val;
        pointer prev;
    };

  public:
    using node_ptr = _node::pointer;

    constexpr persistent_stack() : root(nullptr) {}
    constexpr persistent_stack(node_ptr _root) : root(_root) {}

    T top() const {
        assert(root);
        return root->val;
    }

    persistent_stack push(T val) const { return persistent_stack(new _node{val, root}); }

    persistent_stack pop() const {
        assert(root);
        return persistent_stack(root->prev);
    }

  private:
    node_ptr root;
};
