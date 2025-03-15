#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <vector>
#include "segtree/dynamic_segment_tree.hpp"

/**
 * @brief 二次元セグメント木
 *
 * @tparam M モノイド
 */
template <class M>
struct segment_tree_2d {
  private:
    using T = typename M::value_type;

    struct _node {
        using pointer = _node *;
        pointer left, right;
        dynamic_segment_tree<M> segtree;

        _node(std::int64_t w) : left(nullptr), right(nullptr), segtree(w) {}
    };

  public:
    using node_ptr = typename _node::pointer;

    segment_tree_2d(std::int64_t h, std::int64_t w) : root(new _node(w)), _h(h), _w(w) {}

    T at(std::int64_t x, std::int64_t y) const {
        node_ptr node = root;
        std::int64_t l = 0, r = _h;
        while (r - l > 1) {
            if (!node) return M::id();
            std::int64_t m = (l + r) >> 1;
            if (x < m) r = m, node = node->left;
            else l = m, node = node->right;
        }
        return node ? node->segtree.get(y) : M::id();
    }
    T get(std::int64_t x, std::int64_t y) const { return at(x, y); }

    void set(std::int64_t x, std::int64_t y, T val) {
        assert(0 <= x && x < _h);
        assert(0 <= y && y < _w);
        node_ptr node = root;
        std::vector<node_ptr> nodes;
        std::int64_t l = 0, r = _h;
        while (r - l > 1) {
            std::int64_t m = (l + r) >> 1;
            nodes.emplace_back(node);
            if (x < m) {
                if (!node->left) node->left = new _node(_w);
                r = m, node = node->left;
            } else {
                if (!node->right) node->right = new _node(_w);
                l = m, node = node->right;
            }
        }
        node->segtree.set(y, val);

        std::reverse(std::begin(nodes), std::end(nodes));
        for (auto node : nodes) {
            node->segtree.set(y, M::op(node->left ? node->left->segtree.get(y) : M::id(),
                                       node->right ? node->right->segtree.get(y) : M::id()));
        }
    }
    void reset(std::int64_t x, std::int64_t y) { set(x, y, M::id()); }

    T all_prod() const { return root ? root->segtree.all_prod() : M::id(); }
    T prod(std::int64_t l, std::int64_t r, std::int64_t d, std::int64_t u) const {
        assert(0 <= l && l <= r && r <= _h);
        assert(0 <= d && d <= u && u <= _w);
        return prod(l, r, d, u, root, 0, _h);
    }

  private:
    node_ptr root;
    std::int64_t _h, _w;

    T prod(std::int64_t l, std::int64_t r, std::int64_t d, std::int64_t u, node_ptr node,
           std::int64_t x, std::int64_t y) const {
        if (!node || y <= l || r <= x) return M::id();
        if (l <= x && y <= r) return node->segtree.prod(d, u);

        return M::op(prod(l, r, d, u, node->left, x, (x + y) >> 1),
                     prod(l, r, d, u, node->right, (x + y) >> 1, y));
    }
};
