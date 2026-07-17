#pragma once
#include <cassert>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>
#include "segtree/monoid.hpp"

/// @brief 永続セグメント木
/// @tparam S データのモノイド
/// @tparam F 作用素モノイド（op が作用素の合成、f が値への作用）。`void` なら遅延伝播なし
///           （`apply`/`copy` は提供せず、`prod`/`get` は push を伴わない const な読み取りになる）。
/// @note `void` は内部で `std::monostate` に正規化し、本体を 1 つに保つ。遅延伝播ありの場合、
///       `prod` は経路上の push 結果を `_root` にキャッシュするため非 const になる。
template <class S, class F = void>
requires monoid<S> && (std::is_void_v<F> || (monoid<F> && acts_on<F, typename S::value_type>))
struct PersistentSegmentTree {
  private:
    using T = typename S::value_type;
    static constexpr bool use_lazy = !std::is_void_v<F>;
    struct void_monoid {
        using value_type = std::monostate;
    };
    using U = typename std::conditional_t<use_lazy, F, void_monoid>::value_type;

    struct Node {
        using pointer = Node *;
        T val;
        [[no_unique_address]] std::conditional_t<use_lazy, U, std::monostate> lazy;
        pointer left, right;

        constexpr Node(T _val) : val(_val), left(), right() {
            if constexpr (use_lazy) lazy = F::id();
        }
        constexpr Node(T _val, pointer _left, pointer _right) : val(_val), left(_left), right(_right) {
            if constexpr (use_lazy) lazy = F::id();
        }
        constexpr Node(T _val, U _lazy, pointer _left, pointer _right)
        requires use_lazy
            : val(_val), lazy(_lazy), left(_left), right(_right) {}
    };

  public:
    using node_ptr = typename Node::pointer;

    constexpr PersistentSegmentTree() : _size(), _root() {}
    constexpr PersistentSegmentTree(int n, node_ptr _root) : _size(n), _root(_root) {}
    PersistentSegmentTree(int n, T e = S::id()) : _size(n), _root(build(0, n, e)) {}
    template <class V>
    PersistentSegmentTree(const std::vector<V> &v) : _size(v.size()), _root(build(0, v.size(), v)) {}

    T operator[](int i) const
    requires(!use_lazy)
    {
        return prod(i, i + 1);
    }
    T operator[](int i)
    requires use_lazy
    {
        return prod(i, i + 1);
    }
    T at(int k) const
    requires(!use_lazy)
    {
        return operator[](k);
    }
    T at(int k)
    requires use_lazy
    {
        return operator[](k);
    }
    T get(int k) const
    requires(!use_lazy)
    {
        return operator[](k);
    }
    T get(int k)
    requires use_lazy
    {
        return operator[](k);
    }

    PersistentSegmentTree set(int k, T val) const {
        assert(0 <= k && k < _size);
        return PersistentSegmentTree(_size, set(0, _size, k, val, _root));
    }
    PersistentSegmentTree reset(int k) const { return set(k, S::id()); }

    /// @brief v[k] に f を作用させた版を返す
    PersistentSegmentTree apply(int k, U f) const
    requires use_lazy
    {
        return apply(k, k + 1, f);
    }
    /// @brief v[a ... b-1] に f を作用させた版を返す
    PersistentSegmentTree apply(int a, int b, U f) const
    requires use_lazy
    {
        return PersistentSegmentTree(_size, apply(0, _size, a, b, f, _root));
    }

    /// @brief v[a ... b-1] を cp の同区間で置き換えた版を返す
    PersistentSegmentTree copy(int a, int b, PersistentSegmentTree cp) const
    requires use_lazy
    {
        return PersistentSegmentTree(_size, copy(0, _size, a, b, cp._root, _root));
    }

    T all_prod() const { return _root->val; }
    T prod(int a, int b) const
    requires(!use_lazy)
    {
        assert(0 <= a && b <= _size);
        return prod_readonly(0, _size, a, b, _root);
    }
    T prod(int a, int b)
    requires use_lazy
    {
        assert(0 <= a && b <= _size);
        auto [val, node] = prod_and_push(0, _size, a, b, _root);
        _root = node;
        return val;
    }

  private:
    int _size;
    node_ptr _root;

    static node_ptr merge(node_ptr left, node_ptr right) {
        if (left == nullptr) return right;
        if (right == nullptr) return left;
        return new Node(S::op(left->val, right->val), left, right);
    }

    node_ptr build(int l, int r, T val) const {
        if (l + 1 == r) return new Node(val);
        int m = (l + r) >> 1;
        return merge(build(l, m, val), build(m, r, val));
    }
    template <class V>
    node_ptr build(int l, int r, const std::vector<V> &v) const {
        if (l + 1 == r) return new Node(v[l]);
        int m = (l + r) >> 1;
        return merge(build(l, m, v), build(m, r, v));
    }

    node_ptr set(int l, int r, int k, T val, node_ptr node) const {
        if (l + 1 == r) return new Node(val);
        if constexpr (use_lazy) node = push(node);
        int m = (l + r) >> 1;
        if (k < m) return merge(set(l, m, k, val, node->left), node->right);
        else return merge(node->left, set(m, r, k, val, node->right));
    }

    node_ptr apply(int l, int r, int a, int b, U f, node_ptr node) const
    requires use_lazy
    {
        if (a <= l && r <= b) return all_apply(node, f);
        if (b <= l || r <= a) return node;
        node = push(node);
        int m = (l + r) >> 1;
        return merge(apply(l, m, a, b, f, node->left), apply(m, r, a, b, f, node->right));
    }

    node_ptr copy(int l, int r, int a, int b, node_ptr node_cp, node_ptr node) const
    requires use_lazy
    {
        if (a <= l && r <= b) return node_cp;
        if (b <= l || r <= a) return node;
        node = push(node);
        node_cp = push(node_cp);
        int m = (l + r) >> 1;
        return merge(copy(l, m, a, b, node_cp->left, node->left), copy(m, r, a, b, node_cp->right, node->right));
    }

    T prod_readonly(int l, int r, int a, int b, node_ptr node) const {
        if (a <= l && r <= b) return node->val;
        if (b <= l || r <= a) return S::id();
        int m = (l + r) >> 1;
        return S::op(prod_readonly(l, m, a, b, node->left), prod_readonly(m, r, a, b, node->right));
    }

    std::pair<T, node_ptr> prod_and_push(int l, int r, int a, int b, node_ptr node) const
    requires use_lazy
    {
        if (a <= l && r <= b) return {node->val, node};
        if (b <= l || r <= a) return {S::id(), node};
        node = push(node);
        int m = (l + r) >> 1;
        auto [vl, pl] = prod_and_push(l, m, a, b, node->left);
        auto [vr, pr] = prod_and_push(m, r, a, b, node->right);
        return {S::op(vl, vr), new Node(node->val, node->lazy, pl, pr)};
    }

    node_ptr all_apply(node_ptr node, U f) const
    requires use_lazy
    {
        if (node == nullptr) return nullptr;
        return new Node(F::f(f, node->val), F::op(f, node->lazy), node->left, node->right);
    }

    node_ptr push(node_ptr node) const
    requires use_lazy
    {
        if (node == nullptr) return nullptr;
        return new Node(node->val, F::id(), all_apply(node->left, node->lazy), all_apply(node->right, node->lazy));
    }
};
