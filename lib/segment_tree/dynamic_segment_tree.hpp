#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <utility>
#include <vector>
#include "segment_tree/monoid.hpp"

/**
 * @brief 動的セグメント木
 *
 * @tparam M モノイド
 */
template <class M>
struct dynamic_segment_tree {
  private:
    using T = typename M::value_type;

    struct _node {
        using pointer = _node *;
        std::int64_t index;
        pointer left, right;
        T value, product;

        constexpr _node(std::int64_t _index, T _value)
            : index(_index), left(nullptr), right(nullptr), value(_value), product(_value) {}
    };

  public:
    using node_ptr = typename _node::pointer;

    dynamic_segment_tree(std::int64_t n) : root(), _size(n) {}

    T operator[](std::int64_t k) const {
        node_ptr node = root;
        std::int64_t l = 0, r = _size;
        while (node) {
            if (k == node->index) return node->value;
            std::int64_t m = (l + r) >> 1;
            if (k < m) r = m, node = node->left;
            else l = m, node = node->right;
        }
        return M::id();
    }
    T at(std::int64_t k) const { return operator[](k); }
    T get(std::int64_t k) const { return operator[](k); }

    void set(std::int64_t k, T x) {
        assert(0 <= k && k < _size);
        if (!root) {
            root = new _node(k, x);
            return;
        }
        node_ptr node = root;
        std::vector<node_ptr> nodes;
        std::int64_t l = 0, r = _size;
        while (true) {
            nodes.emplace_back(node);
            if (k == node->index) {
                node->value = x;
                break;
            }
            std::int64_t m = (l + r) >> 1;
            if (k < m) {
                if (node->index < k) std::swap(k, node->index), std::swap(x, node->value);
                if (!node->left) {
                    node->left = new _node(k, x);
                    break;
                }
                r = m, node = node->left;
            } else {
                if (k < node->index) std::swap(k, node->index), std::swap(x, node->value);
                if (!node->right) {
                    node->right = new _node(k, x);
                    break;
                }
                l = m, node = node->right;
            }
        }

        std::reverse(std::begin(nodes), std::end(nodes));
        for (auto node : nodes) {
            node->product = M::op(M::op(node->left ? node->left->product : M::id(), node->value),
                                  node->right ? node->right->product : M::id());
        }
    }
    void reset(std::int64_t k) { set(k, M::id()); }

    T all_prod() const { return root ? root->product : M::id(); }
    T prod(std::int64_t a, std::int64_t b) const {
        assert(0 <= a && a <= _size);
        assert(0 <= b && b <= _size);
        return prod(a, b, root, 0, _size);
    }

    template <class F>
    std::int64_t max_right(F f) const {
        assert(f(M::id()));
        if (root == nullptr || f(root->value)) return _size;
        node_ptr node = root;
        T sm = M::id();
        std::int64_t l = 0, r = _size;
        while (r - l > 1) {
            std::int64_t m = (l + r) >> 1;
            if (node->left == nullptr || f(M::op(sm, node->left->value))) {
                if (node->left != nullptr) sm = M::op(sm, node->left->value);
                l = m;
                node = node->right;
            } else {
                r = m;
                node = node->left;
            }
        }
        return f(M::op(sm, node->value)) ? r : l;
    }

    template <class F>
    std::int64_t min_left(F f) const {
        assert(f(M::id()));
        if (root == nullptr || f(root->value)) return 0;
        node_ptr node = root;
        T sm = M::id();
        std::int64_t l = 0, r = _size;
        while (r - l > 1) {
            std::int64_t m = (l + r) >> 1;
            if (node->right == nullptr || f(M::op(node->right->value, sm))) {
                if (node->right != nullptr) sm = M::op(node->right->value, sm);
                r = m;
                node = node->left;
            } else {
                l = m;
                node = node->right;
            }
        }
        return f(M::op(node->value, sm)) ? l : r;
    }

  private:
    node_ptr root;
    std::int64_t _size;

    T prod(std::int64_t a, std::int64_t b, node_ptr node, std::int64_t l, std::int64_t r) const {
        if (!node || r <= a || b <= l) return M::id();
        if (a <= l && r <= b) return node->product;

        return M::op(M::op(prod(a, b, node->left, l, (l + r) >> 1),
                           a <= node->index && node->index < b ? node->value : M::id()),
                     prod(a, b, node->right, (l + r) >> 1, r));
    }
};
