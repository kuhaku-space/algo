#pragma once
#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>
#include "segtree/segment_tree.hpp"

/// @brief 領域木
/// @see https://hitonanode.github.io/cplib-cpp/segmenttree/rangetree.hpp.html
template <class M, class T = int>
struct RangeTree {
  private:
    using point_type = std::pair<T, T>;
    using value_type = typename M::value_type;

  public:
    /// @brief 空の領域木を構築する
    /// @complexity $O(1)$
    RangeTree() = default;

    /// @brief build前に使用する座標を登録する
    /// @complexity 償却 $O(1)$
    void add(T x, T y) noexcept { pts.emplace_back(x, y); }

    /// @brief 登録した座標から領域木を構築する
    /// @complexity 登録点数を $n$ として時間・空間ともに $O(n\log n)$
    void build() {
        std::sort(pts.begin(), pts.end());
        pts.erase(std::unique(pts.begin(), pts.end()), pts.end());
        size = pts.size();

        range2yxs.resize(size * 2);
        for (int i = 0; i < size; i++) range2yxs[size + i] = {{pts[i].second, pts[i].first}};
        for (int i = size - 1; i > 0; i--) {
            auto &lch = range2yxs[i * 2];
            auto &rch = range2yxs[i * 2 + 1];
            std::merge(lch.begin(), lch.end(), rch.begin(), rch.end(), std::back_inserter(range2yxs[i]));
            range2yxs[i].erase(std::unique(range2yxs[i].begin(), range2yxs[i].end()), range2yxs[i].end());
        }
        for (const auto &v : range2yxs) segtrees.emplace_back(v.size());
    }

    /// @brief 登録点の値を設定する
    /// @complexity $O(\log^2 n)$
    void set(T x, T y, value_type val) {
        int i = std::distance(pts.begin(), std::lower_bound(pts.begin(), pts.end(), point_type{x, y}));
        assert(i < size && pts[i] == std::make_pair(x, y));
        for (i += size; i; i >>= 1) set(i, {x, y}, val);
    }

    /// @brief 半開矩形 $[x_l,x_r)\times[y_l,y_r)$ のモノイド積を返す
    /// @complexity $O(\log^2 n)$
    value_type prod(T xl, T yl, T xr, T yr) const {
        auto comp = [](const point_type &l, const point_type &r) { return l.first < r.first; };
        int l = size + std::distance(pts.begin(), std::lower_bound(pts.begin(), pts.end(), point_type{xl, yr}, comp));
        int r = size + std::distance(pts.begin(), std::lower_bound(pts.begin(), pts.end(), point_type{xr, yr}, comp));
        value_type res = M::id();
        while (l < r) {
            if (l & 1) res = M::op(res, prod(l++, yl, yr));
            if (r & 1) res = M::op(res, prod(--r, yl, yr));
            l >>= 1, r >>= 1;
        }
        return res;
    }
    /// @brief 登録点の値を返し、未登録なら単位元を返す
    /// @complexity $O(\log n)$
    value_type get(T x, T y) const {
        int i = std::distance(pts.begin(), std::lower_bound(pts.begin(), pts.end(), point_type{x, y}));
        return i < size && pts[i] == std::make_pair(x, y) ? segtrees[size + i].get(0) : M::id();
    }

  private:
    int size;
    std::vector<point_type> pts;
    std::vector<std::vector<point_type>> range2yxs;
    std::vector<SegmentTree<M>> segtrees;

    void set(int v, point_type p, value_type val) {
        auto i = std::distance(range2yxs[v].begin(), std::lower_bound(range2yxs[v].begin(), range2yxs[v].end(),
                                                                      point_type{p.second, p.first}));
        segtrees[v].set(i, val);
    }

    value_type prod(int v, T yl, T yr) const {
        auto comp = [&](const point_type &l, const point_type &r) { return l.first < r.first; };
        auto il = std::distance(range2yxs[v].begin(),
                                std::lower_bound(range2yxs[v].begin(), range2yxs[v].end(), point_type{yl, yl}, comp));
        auto ir = std::distance(range2yxs[v].begin(),
                                std::lower_bound(range2yxs[v].begin(), range2yxs[v].end(), point_type{yr, yr}, comp));
        return segtrees[v].prod(il, ir);
    }
};
