#pragma once
#include <cassert>
#include <vector>
#include "segtree/monoid.hpp"

/// @brief 永続遅延評価セグメント木
template <class S, class F>
struct persistent_lazy_segment_tree {
  private:
    using T = typename S::value_type;
    using U = typename F::value_type;

    struct _node {
        using pointer = _node *;
        T val;
        U lazy;
        pointer left, right;

        constexpr _node(T _val) : val(_val), lazy(F::id()), left(), right() {}
        constexpr _node(T _val, U _lazy, pointer _left, pointer _right)
            : val(_val), lazy(_lazy), left(_left), right(_right) {}
    };

  public:
    using node_ptr = typename _node::pointer;

    constexpr persistent_lazy_segment_tree() : _size(), _root() {}
    constexpr persistent_lazy_segment_tree(int n, node_ptr _root) : _size(n), _root(_root) {}
    persistent_lazy_segment_tree(int n, T e = S::id()) : _size(n), _root(build(0, n, e)) {}
    template <class U>
    persistent_lazy_segment_tree(const std::vector<U> &v)
        : _size(v.size()), _root(build(0, v.size(), v)) {}

    T operator[](int i) { return prod(i, i + 1); }
    T at(int k) { return operator[](k); }
    T get(int k) { return operator[](k); }

    persistent_lazy_segment_tree set(int k, T val) const {
        assert(0 <= k && k < _size);
        return persistent_lazy_segment_tree(_size, set(0, _size, k, val, _root));
    }
    persistent_lazy_segment_tree reset(int k) const { return set(k, S::id()); }

    persistent_lazy_segment_tree apply(int k, U f) const { return apply(k, k + 1, f); }
    persistent_lazy_segment_tree apply(int a, int b, U f) const {
        return persistent_lazy_segment_tree(_size, apply(0, _size, a, b, f, _root));
    }

    persistent_lazy_segment_tree copy(int a, int b, persistent_lazy_segment_tree cp) const {
        return persistent_lazy_segment_tree(_size, copy(0, _size, a, b, cp._root, _root));
    }

    T all_prod() const { return _root->val; }
    T prod(int a, int b) {
        assert(0 <= a && b <= _size);
        auto [val, node] = prod(0, _size, a, b, _root);
        _root = node;
        return val;
    }

  private:
    int _size;
    node_ptr _root;

    static node_ptr merge(node_ptr left, node_ptr right) {
        if (left == nullptr) return right;
        if (right == nullptr) return left;
        return new _node(S::op(left->val, right->val), F::id(), left, right);
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
        node = push(node);
        int m = (l + r) >> 1;
        if (k < m) return merge(set(l, m, k, val, node->left), node->right);
        else return merge(node->left, set(m, r, k, val, node->right));
    }

    node_ptr apply(int l, int r, int a, int b, U f, node_ptr node) const {
        if (a <= l && r <= b) return all_apply(node, f);
        if (b <= l || r <= a) return node;
        node = push(node);
        int m = (l + r) >> 1;
        return merge(apply(l, m, a, b, f, node->left), apply(m, r, a, b, f, node->right));
    }

    node_ptr copy(int l, int r, int a, int b, node_ptr node_cp, node_ptr node) const {
        if (a <= l && r <= b) return node_cp;
        if (b <= l || r <= a) return node;
        node = push(node);
        node_cp = push(node_cp);
        int m = (l + r) >> 1;
        return merge(copy(l, m, a, b, node_cp->left, node->left),
                     copy(m, r, a, b, node_cp->right, node->right));
    }

    std::pair<T, node_ptr> prod(int l, int r, int a, int b, node_ptr node) const {
        if (a <= l && r <= b) return {node->val, node};
        if (b <= l || r <= a) return {S::id(), node};
        node = push(node);
        int m = (l + r) >> 1;
        auto [vl, pl] = prod(l, m, a, b, node->left);
        auto [vr, pr] = prod(m, r, a, b, node->right);
        return {S::op(vl, vr), new _node(node->val, node->lazy, pl, pr)};
    }

    node_ptr all_apply(node_ptr node, U f) const {
        if (node == nullptr) return nullptr;
        return new _node(F::f(f, node->val), F::op(f, node->lazy), node->left, node->right);
    }

    node_ptr push(node_ptr node) const {
        if (node == nullptr) return nullptr;
        return new _node(node->val, F::id(), all_apply(node->left, node->lazy),
                         all_apply(node->right, node->lazy));
    }
};
