#pragma once
#include <cassert>
#include <vector>
#include "segtree/monoid.hpp"

/// @brief 永続双対セグメント木
/// @complexity 構築は $O(n)$、点取得・区間作用は $O(\log n)$
template <monoid M>
struct PersistentDualSegmentTree {
  private:
    using T = typename M::value_type;

    struct Node {
        using pointer = Node *;
        T val;
        pointer left, right;

        constexpr Node(T _val) : val(_val), left(), right() {}
        constexpr Node(T _val, pointer _left, pointer _right) : val(_val), left(_left), right(_right) {}
    };

    using node_ptr = typename Node::pointer;

  public:
    /// @brief 空の木を構築する
    /// @complexity $O(1)$
    constexpr PersistentDualSegmentTree() : n(), root() {}

    /// @brief n要素をeで初期化する
    /// @complexity $O(n)$
    PersistentDualSegmentTree(int _n, T e = M::id()) : n(_n), root(build(0, _n, e)) {}

    /// @brief 列vから構築する
    /// @complexity $O(n)$
    template <class U>
    PersistentDualSegmentTree(const std::vector<U> &v) : n(v.size()), root(build(0, v.size(), v)) {}

    /// @brief i番目の値を返す
    /// @complexity $O(\log n)$
    T operator[](int i) const { return get(0, n, i, root); }

    /// @brief k番目の値を返す
    /// @complexity $O(\log n)$
    T at(int k) const { return operator[](k); }

    /// @brief k番目の値を返す
    /// @complexity $O(\log n)$
    T get(int k) const { return operator[](k); }

    /// @brief a番目にvalを作用した新しいversionを返す
    /// @complexity $O(\log n)$
    PersistentDualSegmentTree apply(int a, T val) const { return apply(a, a + 1, val); }

    /// @brief 半開区間[a,b)にvalを作用した新しいversionを返す
    /// @complexity $O(\log n)$
    PersistentDualSegmentTree apply(int a, int b, T val) const {
        assert(0 <= a && b <= n);
        return with_root(apply(0, n, a, b, val, M::id(), root));
    }

  private:
    int n;
    node_ptr root;

    PersistentDualSegmentTree with_root(node_ptr _root) const {
        PersistentDualSegmentTree res = *this;
        res.root = _root;
        return res;
    }

    static node_ptr merge(node_ptr left, node_ptr right) { return new Node(M::op(left->val, right->val), left, right); }

    node_ptr build(int l, int r, T val) const {
        if (l + 1 == r) return new Node(val);
        int m = (l + r) >> 1;
        return merge(build(l, m, val), build(m, r, val));
    }
    template <class U>
    node_ptr build(int l, int r, const std::vector<U> &v) const {
        if (l + 1 == r) return new Node(v[l]);
        int m = (l + r) >> 1;
        return merge(build(l, m, v), build(m, r, v));
    }

    T get(int l, int r, int k, node_ptr node) const {
        if (l + 1 == r) return node->val;
        int m = (l + r) >> 1;
        if (k < m) return M::op(node->val, get(l, m, k, node->left));
        else return M::op(node->val, get(m, r, k, node->right));
    }

    node_ptr apply(int l, int r, int a, int b, T val, T prop, node_ptr node) const {
        if (a <= l && r <= b) return new Node(M::op(val, M::op(prop, node->val)), node->left, node->right);
        if (b <= l || r <= a) return new Node(M::op(prop, node->val), node->left, node->right);
        int m = (l + r) >> 1;
        return new Node(M::id(), apply(l, m, a, b, val, M::op(prop, node->val), node->left),
                        apply(m, r, a, b, val, M::op(prop, node->val), node->right));
    }
};
