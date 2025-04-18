#pragma once
#include <cassert>
#include <vector>
#include "segtree/monoid.hpp"

/// @brief 永続セグメント木
template <class M>
struct persistent_segment_tree {
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
    using node_ptr = typename _node::pointer;

    constexpr persistent_segment_tree() : _size(), _root() {}
    constexpr persistent_segment_tree(int n, node_ptr _root) : _size(n), _root(_root) {}
    persistent_segment_tree(int n, T e = M::id()) : _size(n), _root(build(0, n, e)) {}
    template <class U>
    persistent_segment_tree(const std::vector<U> &v)
        : _size(v.size()), _root(build(0, v.size(), v)) {}

    T operator[](int i) const { return prod(i, i + 1); }
    T at(int k) const { return operator[](k); }
    T get(int k) const { return operator[](k); }

    persistent_segment_tree set(int k, T val) {
        assert(0 <= k && k < _size);
        return persistent_segment_tree(_size, set(0, _size, k, val, _root));
    }
    persistent_segment_tree reset(int k) { return set(k, M::id()); }

    T all_prod() const { return _root->val; }
    T prod(int a, int b) const {
        assert(0 <= a && b <= _size);
        return prod(0, _size, a, b, _root);
    }

  private:
    int _size;
    node_ptr _root;

    static node_ptr merge(node_ptr left, node_ptr right) {
        return new _node(M::op(left->val, right->val), left, right);
    }

    node_ptr build(int l, int r, T val) const {
        if (l + 1 == r) return new _node(val);
        int m = (l + r) >> 1;
        return merge(build(l, m, val), build(m, r, val));
    }
    template <class U>
    node_ptr build(int l, int r, const std::vector<U> &v) const {
        if (l + 1 == r) return new _node(v[l]);
        int m = (l + r) >> 1;
        return merge(build(l, m, v), build(m, r, v));
    }

    node_ptr set(int l, int r, int k, T val, node_ptr node) const {
        if (l + 1 == r) return new _node(val);
        int m = (l + r) >> 1;
        if (k < m) return merge(set(l, m, k, val, node->left), node->right);
        else return merge(node->left, set(m, r, k, val, node->right));
    }

    T prod(int l, int r, int a, int b, node_ptr node) const {
        if (a <= l && r <= b) return node->val;
        if (b <= l || r <= a) return M::id();
        int m = (l + r) >> 1;
        return M::op(prod(l, m, a, b, node->left), prod(m, r, a, b, node->right));
    }
};
