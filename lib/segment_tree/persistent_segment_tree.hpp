#include <vector>
#include "segment_tree/monoid.hpp"

/**
 * @brief 永続セグメント木
 *
 * @tparam Monoid モノイド
 */
template <class Monoid>
struct persistent_segment_tree {
  private:
    using T = typename Monoid::value_type;

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

    constexpr persistent_segment_tree() : _size(), _root() {}
    constexpr persistent_segment_tree(int n, node_pointer _root) : _size(n), _root(_root) {}
    persistent_segment_tree(int n, T e = Monoid::id()) : _size(n), _root(build(0, n, e)) {}
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
    persistent_segment_tree reset(int k) { return set(k, Monoid::id()); }

    T all_prod() const { return _root->val; }
    T prod(int a, int b) const {
        assert(0 <= a && b <= _size);
        return prod(0, _size, a, b, _root);
    }

  private:
    int _size;
    node_pointer _root;

    static node_pointer merge(node_pointer left, node_pointer right) {
        return new _node(Monoid::op(left->val, right->val), left, right);
    }

    node_pointer build(int l, int r, T val) const {
        if (l + 1 == r) return new _node(val);
        int m = (l + r) >> 1;
        return merge(build(l, m, val), build(m, r, val));
    }
    template <class U>
    node_pointer build(int l, int r, const std::vector<U> &v) const {
        if (l + 1 == r) return new _node(v[l]);
        int m = (l + r) >> 1;
        return merge(build(l, m, v), build(m, r, v));
    }

    node_pointer set(int l, int r, int k, T val, node_pointer node) const {
        if (l + 1 == r) return new _node(val);
        int m = (l + r) >> 1;
        if (k < m) return merge(set(l, m, k, val, node->left), node->right);
        else return merge(node->left, set(m, r, k, val, node->right));
    }

    T prod(int l, int r, int a, int b, node_pointer node) const {
        if (a <= l && r <= b) return node->val;
        if (b <= l || r <= a) return Monoid::id();
        int m = (l + r) >> 1;
        return Monoid::op(prod(l, m, a, b, node->left), prod(m, r, a, b, node->right));
    }
};
