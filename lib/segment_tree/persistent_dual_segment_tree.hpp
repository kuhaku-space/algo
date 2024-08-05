#pragma once
#include <vector>
#include "segment_tree/monoid.hpp"

/// @brief 永続双対セグメント木
template <class M>
struct persistent_dual_segment_tree {
  private:
    using T = typename M::value_type;

    struct _node {
        using pointer = _node *;
        T val;
        pointer left, right;

        constexpr _node(T _val) : val(_val), left(), right() {}
        constexpr _node(T _val, pointer _left, pointer _right)
            : val(_val), left(_left), right(_right) {}
    };

  public:
    using node_pointer = typename _node::pointer;

    constexpr persistent_dual_segment_tree() : _size(), root() {}
    constexpr persistent_dual_segment_tree(int n, node_pointer _root) : _size(n), root(_root) {}
    persistent_dual_segment_tree(int n, T e = M::id()) : _size(n), root(this->build(0, n, e)) {}
    template <class U>
    persistent_dual_segment_tree(const std::vector<U> &v)
        : _size(v.size()), root(this->build(0, v.size(), v)) {}

    T operator[](int i) const { return this->get(0, this->_size, i, this->root); }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }

    persistent_dual_segment_tree apply(int a, T val) const { return this->apply(a, a + 1, val); }
    persistent_dual_segment_tree apply(int a, int b, T val) const {
        assert(0 <= a && b <= this->_size);
        return persistent_dual_segment_tree(
            this->_size, this->apply(0, this->_size, a, b, val, M::id(), this->root));
    }

  private:
    int _size;
    node_pointer root;

    static node_pointer merge(node_pointer left, node_pointer right) {
        return new _node(M::op(left->val, right->val), left, right);
    }

    node_pointer build(int l, int r, T val) const {
        if (l + 1 == r) return new _node(val);
        int m = (l + r) >> 1;
        return this->merge(this->build(l, m, val), this->build(m, r, val));
    }
    template <class U>
    node_pointer build(int l, int r, const std::vector<U> &v) const {
        if (l + 1 == r) return new _node(v[l]);
        int m = (l + r) >> 1;
        return this->merge(this->build(l, m, v), this->build(m, r, v));
    }

    T get(int l, int r, int k, node_pointer node) const {
        if (l + 1 == r) return node->val;
        int m = (l + r) >> 1;
        if (k < m) return M::op(node->val, this->get(l, m, k, node->left));
        else return M::op(node->val, this->get(m, r, k, node->right));
    }

    node_pointer apply(int l, int r, int a, int b, T val, T prop, node_pointer node) const {
        if (a <= l && r <= b)
            return new _node(M::op(val, M::op(prop, node->val)), node->left, node->right);
        if (b <= l || r <= a) return new _node(M::op(prop, node->val), node->left, node->right);
        int m = (l + r) >> 1;
        return new _node(M::id(), this->apply(l, m, a, b, val, M::op(prop, node->val), node->left),
                         this->apply(m, r, a, b, val, M::op(prop, node->val), node->right));
    }
};
