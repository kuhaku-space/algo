#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <vector>
#include "segtree/dynamic_segment_tree.hpp"

/// @brief 二次元セグメント木
/// @complexity 点更新・矩形積は $O(\log h\log w)$
template <monoid M>
struct SegmentTree2D {
  private:
    using T = typename M::value_type;

    struct Node {
        using pointer = Node *;
        pointer left, right;
        DynamicSegmentTree<M> segtree;

        Node(std::int64_t w) : left(nullptr), right(nullptr), segtree(w) {}
    };

  public:
    /// @brief 内部ノードへのpointer型
    /// @complexity 型エイリアスで実行時計算量はない
    using node_ptr = typename Node::pointer;

    /// @brief h行w列の空の木を構築する
    /// @complexity $O(1)$
    SegmentTree2D(std::int64_t _h, std::int64_t _w) : root(new Node(_w)), h(_h), w(_w) {}

    /// @brief 座標(x,y)の値を返す
    /// @complexity $O(\log h\log w)$
    T at(std::int64_t x, std::int64_t y) const {
        node_ptr node = root;
        std::int64_t l = 0, r = h;
        while (r - l > 1) {
            if (!node) return M::id();
            std::int64_t m = (l + r) >> 1;
            if (x < m) r = m, node = node->left;
            else l = m, node = node->right;
        }
        return node ? node->segtree.get(y) : M::id();
    }

    /// @brief 座標(x,y)の値を返す
    /// @complexity $O(\log h\log w)$
    T get(std::int64_t x, std::int64_t y) const { return at(x, y); }

    /// @brief 座標(x,y)をvalへ変更する
    /// @complexity $O(\log h\log w)$
    void set(std::int64_t x, std::int64_t y, T val) {
        assert(0 <= x && x < h);
        assert(0 <= y && y < w);
        node_ptr node = root;
        std::vector<node_ptr> nodes;
        std::int64_t l = 0, r = h;
        while (r - l > 1) {
            std::int64_t m = (l + r) >> 1;
            nodes.emplace_back(node);
            if (x < m) {
                if (!node->left) node->left = new Node(w);
                r = m, node = node->left;
            } else {
                if (!node->right) node->right = new Node(w);
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

    /// @brief 座標(x,y)を単位元へ戻す
    /// @complexity $O(\log h\log w)$
    void reset(std::int64_t x, std::int64_t y) { set(x, y, M::id()); }

    /// @brief 全要素の積を返す
    /// @complexity $O(1)$
    T all_prod() const { return root ? root->segtree.all_prod() : M::id(); }

    /// @brief 行[xl,xr)・列[yl,yr)の矩形積を返す
    /// @complexity $O(\log h\log w)$
    T prod(std::int64_t xl, std::int64_t xr, std::int64_t yl, std::int64_t yr) const {
        assert(0 <= xl && xl <= xr && xr <= h);
        assert(0 <= yl && yl <= yr && yr <= w);
        return prod(xl, xr, yl, yr, root, 0, h);
    }

  private:
    node_ptr root;
    std::int64_t h, w;

    T prod(std::int64_t xl, std::int64_t xr, std::int64_t yl, std::int64_t yr, node_ptr node, std::int64_t l,
           std::int64_t r) const {
        if (!node || r <= xl || xr <= l) return M::id();
        if (xl <= l && r <= xr) return node->segtree.prod(yl, yr);
        std::int64_t m = (l + r) >> 1;
        return M::op(prod(xl, xr, yl, yr, node->left, l, m), prod(xl, xr, yl, yr, node->right, m, r));
    }
};
