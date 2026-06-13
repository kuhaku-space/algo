#pragma once
#include <algorithm>
#include <utility>
#include <vector>
#include "graph/graph.hpp"

/// @brief 支配木（Lengauer-Tarjan 法）
/// @details 始点 root から到達可能な各頂点 v について、その直接支配点
///          (immediate dominator) idom[v] を計算する。root から v への
///          すべての経路が必ず通る頂点のうち、v に最も近いものが idom[v]。
///          idom[root] = root とする。root から到達不能な頂点は idom = -1。
///          辺の重みは無視する。計算量はほぼ O((V + E) α(V))。
template <class T>
struct dominator_tree {
    /// @param g 有向グラフ
    /// @param root 支配関係の始点
    dominator_tree(const Graph<T> &g, int root = 0) : _size(g.size()), _root(root), _idom(_size, -1) {
        std::vector<std::vector<int>> radj(_size);
        for (auto &e : g.all_edges()) radj[e.to()].emplace_back(e.from());
        build(g, radj);
    }

    /// @brief 直接支配点を取得する（root は自分自身、到達不能な頂点は -1）
    int idom(int v) const { return _idom[v]; }
    /// @brief 直接支配点の配列を取得する
    const std::vector<int> &idom() const { return _idom; }

  private:
    int _size, _root;
    std::vector<int> _idom;

    void build(const Graph<T> &g, const std::vector<std::vector<int>> &radj) {
        std::vector<int> ord(_size, -1);       // 頂点 → DFS 番号
        std::vector<int> rev;                  // DFS 番号 → 頂点
        std::vector<int> par(_size, -1);       // DFS 木の親（DFS 番号）
        std::vector<int> semi(_size, -1);      // 半支配点（DFS 番号）
        std::vector<int> idom_ord(_size, -1);  // idom（DFS 番号）
        std::vector<int> uf(_size, -1);        // union-find の親
        std::vector<int> mn(_size);            // パス上で semi 最小の頂点
        std::vector<std::vector<int>> bucket(_size);

        // root からの DFS で番号付け（明示スタックで非再帰化）
        // stack には (頂点, 親の DFS 番号) を積む。
        std::vector<std::pair<int, int>> stk;
        stk.emplace_back(_root, -1);
        while (!stk.empty()) {
            auto [v, p] = stk.back();
            stk.pop_back();
            if (ord[v] != -1) continue;
            int t = rev.size();
            ord[v] = t;
            par[t] = p;
            rev.emplace_back(v);
            uf[t] = mn[t] = semi[t] = t;
            // 元の再帰と同じ訪問順にするため逆順に積む
            for (auto it = g[v].rbegin(); it != g[v].rend(); ++it) {
                int w = it->to();
                if (ord[w] == -1) stk.emplace_back(w, t);
            }
        }

        int m = rev.size();

        // semi[v] 最小の頂点を返す経路圧縮付き find（明示スタックで非再帰化）
        std::vector<int> path;
        auto eval = [&](int v) -> int {
            path.clear();
            while (uf[v] != v) {
                path.emplace_back(v);
                v = uf[v];
            }
            // 根 v に向かって巻き戻しながら mn を更新し、経路圧縮する
            for (auto it = path.rbegin(); it != path.rend(); ++it) {
                int u = *it;
                if (semi[mn[uf[u]]] < semi[mn[u]]) mn[u] = mn[uf[u]];
                uf[u] = v;
            }
            return v;
        };

        // DFS 番号の大きい順に半支配点を確定させる
        for (int t = m - 1; t >= 1; --t) {
            int v = rev[t];
            for (int u : radj[v]) {
                if (ord[u] == -1) continue;  // 到達不能な前駆は無視
                int s = ord[u];
                eval(s);
                semi[t] = std::min(semi[t], semi[mn[s]]);
            }
            bucket[semi[t]].emplace_back(t);

            // 親へ向けて bucket を処理
            int p = par[t];
            for (int s : bucket[p]) {
                eval(s);
                idom_ord[s] = (semi[mn[s]] < p) ? mn[s] : p;
            }
            bucket[p].clear();

            // t を DFS 木の親に連結
            uf[t] = p;
        }

        // idom を DFS 番号順に確定
        for (int t = 1; t < m; ++t) {
            if (idom_ord[t] != semi[t]) idom_ord[t] = idom_ord[idom_ord[t]];
        }

        _idom[_root] = _root;
        for (int t = 1; t < m; ++t) _idom[rev[t]] = rev[idom_ord[t]];
    }
};
