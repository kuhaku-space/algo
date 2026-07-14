#pragma once
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>
#include "flow/bipartite_matching.hpp"
#include "graph/graph.hpp"

/// @brief 2 彩色済みの一般の無向グラフを二部マッチング本体（`BipartiteMatching`）に橋渡しするアダプタ
/// @details `bipartite_coloring(g)` の結果をそのまま渡して構築し、
///          最大マッチング・最小頂点被覆・最大独立集合を元のグラフの頂点 id で取得する。
///
///          ```cpp
///          auto color = bipartite_coloring(g);
///          if (color) {
///              BipartiteGraphMatching bgm(g, *color);
///              auto mis = bgm.maximum_independent_set();
///          }
///          ```
struct BipartiteGraphMatching {
    /// @param g 無向グラフ（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
    /// @param color 各頂点の色（0/1）。正当な 2 彩色であること。
    template <graph_type G>
    BipartiteGraphMatching(const G &g, const std::vector<int> &color)
        : local(color.size(), -1), bm((int)std::count(color.begin(), color.end(), 0),
                                      (int)color.size() - (int)std::count(color.begin(), color.end(), 0)) {
        int n = color.size();
        assert(g.size() == n);
        for (int v = 0; v < n; ++v) {
            auto &ids = color[v] == 0 ? origin_left : origin_right;
            local[v] = ids.size();
            ids.emplace_back(v);
        }
        for (int v : origin_left) {
            for (auto &e : g[v]) {
                assert(color[e.to()] == 1);
                bm.add_edge(local[v], local[e.to()]);
            }
        }
    }

    /// @brief 最大マッチングのサイズ
    int matching() {
        if (match_size == -1) match_size = bm.matching();
        return match_size;
    }

    /// @brief 最大マッチングの辺集合（元の頂点 id の組）
    std::vector<std::pair<int, int>> matching_pairs() {
        matching();
        std::vector<std::pair<int, int>> res;
        for (auto [l, r] : bm.get_pairs()) res.emplace_back(origin_left[l], origin_right[r]);
        return res;
    }

    /// @brief 最小頂点被覆（元の頂点 id、昇順）
    std::vector<int> minimum_vertex_cover() {
        auto [l, r] = bm.minimum_vertex_cover();
        return to_origin(l, r);
    }

    /// @brief 最大独立集合（元の頂点 id、昇順）
    std::vector<int> maximum_independent_set() {
        auto [l, r] = bm.maximum_independent_set();
        return to_origin(l, r);
    }

  private:
    std::vector<int> origin_left, origin_right;  // 左右の局所 id → 元の頂点 id（昇順）
    std::vector<int> local;                      // 元の頂点 id → 左右内の局所 id
    BipartiteMatching bm;
    int match_size = -1;

    // 左右の局所 id 列を元の頂点 id に写して昇順にマージする
    std::vector<int> to_origin(const std::vector<int> &left, const std::vector<int> &right) const {
        std::vector<int> a(left.size()), b(right.size()), res(left.size() + right.size());
        std::ranges::transform(left, a.begin(), [&](int l) { return origin_left[l]; });
        std::ranges::transform(right, b.begin(), [&](int r) { return origin_right[r]; });
        std::ranges::merge(a, b, res.begin());
        return res;
    }
};
