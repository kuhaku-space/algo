#pragma once
#include <algorithm>
#include <vector>
#include "graph/graph.hpp"

/// @brief LowLink
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @complexity 構築は $O(V+E)$、取得は $O(1)$
template <graph_type G>
struct low_link {
    /// @brief 無向グラフgの関節点と橋を列挙する
    /// @complexity $O(V+E)$
    low_link(const G &_g) : low_link(_g, _g.size()) {}

    /// @brief 関節点（頂点番号）の一覧を取得する
    /// @complexity $O(1)$
    const std::vector<int> &get_articulation_points() const { return articulation_points; }
    /// @brief 橋の一覧を辺 ID で取得する（頂点は g.get_edge(id) で引ける）
    /// @complexity $O(1)$
    const std::vector<int> &get_bridges() const { return bridges; }

  private:
    const G &g;
    std::vector<int> ord, low;
    std::vector<bool> used;
    std::vector<int> articulation_points;  // 関節点（頂点番号）
    std::vector<int> bridges;              // 橋（辺 ID）

    low_link(const G &_g, int n) : g(_g), ord(n), low(n), used(n) { build(); }

    void build() {
        int number = 0;
        // parent_edge_id: index に入ってきた辺の ID（根は -1）。
        // 親へ戻る辺は「同じ ID の辺」で除外する。多重辺は ID が異なるため
        // back edge として正しく扱われ、橋・関節点の誤判定を防ぐ。
        //
        // 反復 DFS（再帰だと深いグラフでスタックオーバーフローしうる）。
        // 各フレームは頂点・親辺 ID・隣接走査位置・子の本数・関節点フラグを持つ。
        // 子から戻った直後の処理（low の更新・橋/関節点判定）は、どの辺で
        // 降りたかを覚えておき復帰時に行う。
        struct frame {
            int v, parent_edge_id, idx, count;
            bool is_articulation;
        };
        std::vector<frame> stk;
        stk.reserve(g.size());
        for (int s = 0; s < g.size(); ++s) {
            if (used[s]) continue;
            used[s] = true;
            ord[s] = low[s] = number++;
            stk.push_back({s, -1, 0, 0, false});
            while (!stk.empty()) {
                frame &f = stk.back();
                int v = f.v;
                if (f.idx < (int)g[v].size()) {
                    auto e = g[v][f.idx++];
                    if (e.id() == f.parent_edge_id) continue;  // 親へ来た辺そのものは無視
                    int to = e.to();
                    if (!used[to]) {
                        ++f.count;
                        used[to] = true;
                        ord[to] = low[to] = number++;
                        // 復帰時に f.idx-1 の辺で子を処理するため、子フレームを積む
                        stk.push_back({to, e.id(), 0, 0, false});
                    } else {
                        low[v] = std::min(low[v], ord[to]);
                    }
                } else {
                    // v の探索完了。親フレームへ戻って子処理を反映する。
                    bool is_art = f.is_articulation;
                    is_art |= f.parent_edge_id == -1 && f.count > 1;
                    if (is_art) articulation_points.emplace_back(v);
                    int low_v = low[v], pe = f.parent_edge_id;
                    stk.pop_back();
                    if (!stk.empty()) {
                        frame &pf = stk.back();
                        int p = pf.v;
                        low[p] = std::min(low[p], low_v);
                        pf.is_articulation |= pf.parent_edge_id != -1 && low_v >= ord[p];
                        if (ord[p] < low_v) bridges.emplace_back(pe);
                    }
                }
            }
        }
    }
};
