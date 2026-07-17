#pragma once
#include <algorithm>
#include <utility>
#include <vector>
#include "graph/graph.hpp"
#include "internal/internal_csr.hpp"

/// @brief 強連結成分分解
/// @tparam G グラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
template <graph_type G>
std::vector<int> scc(const G &g) {
    int n = g.size();
    std::vector<int> comp(n, -1), order;
    std::vector<bool> used(n);

    internal::graph_csr rg(n);
    for (auto &e : g.all_edges()) rg.add_edge(e.to(), e.from());
    rg.build();

    // 反復 DFS（再帰だと深いグラフでスタックオーバーフローしうる）
    // stk には頂点と隣接リストの走査位置を積む。子を処理し終えた後に
    // order へ push することで、再帰版と同じ帰りがけ順を再現する。
    std::vector<std::pair<int, int>> stk;
    stk.reserve(n);
    for (int s = 0; s < n; ++s) {
        if (used[s]) continue;
        used[s] = true;
        stk.emplace_back(s, 0);
        while (!stk.empty()) {
            auto &[v, idx] = stk.back();
            if (idx < (int)g[v].size()) {
                int to = g[v][idx++].to();
                if (!used[to]) {
                    used[to] = true;
                    stk.emplace_back(to, 0);
                }
            } else {
                order.emplace_back(v);
                stk.pop_back();
            }
        }
    }
    std::reverse(order.begin(), order.end());

    // 逆グラフ上の反復 DFS で連結成分番号を振る
    std::vector<int> rstk;
    rstk.reserve(n);
    int ptr = 0;
    for (auto i : order) {
        if (~comp[i]) continue;
        comp[i] = ptr;
        rstk.emplace_back(i);
        while (!rstk.empty()) {
            int v = rstk.back();
            rstk.pop_back();
            for (int u : rg[v]) {
                if (~comp[u]) continue;
                comp[u] = ptr;
                rstk.emplace_back(u);
            }
        }
        ++ptr;
    }

    return comp;
};

std::vector<int> scc(const internal::graph_csr &g) {
    int n = g.size();
    std::vector<int> comp(n, -1), order;
    std::vector<bool> used(n);

    internal::graph_csr rg(n);
    for (int i = 0; i < n; ++i) {
        for (int u : g[i]) rg.add_edge(u, i);
    }
    rg.build();

    // 反復 DFS（再帰だと深いグラフでスタックオーバーフローしうる）
    // CSR は隣接リストの走査をイテレータで進める。子を処理し終えた後に
    // order へ push することで、再帰版と同じ帰りがけ順を再現する。
    using cit = std::vector<int>::const_iterator;
    std::vector<std::pair<int, std::pair<cit, cit>>> stk;
    stk.reserve(n);
    for (int s = 0; s < n; ++s) {
        if (used[s]) continue;
        used[s] = true;
        stk.emplace_back(s, std::make_pair(g[s].begin(), g[s].end()));
        while (!stk.empty()) {
            auto &[v, it] = stk.back();
            if (it.first != it.second) {
                int to = *it.first++;
                if (!used[to]) {
                    used[to] = true;
                    stk.emplace_back(to, std::make_pair(g[to].begin(), g[to].end()));
                }
            } else {
                order.emplace_back(v);
                stk.pop_back();
            }
        }
    }
    std::reverse(order.begin(), order.end());

    // 逆グラフ上の反復 DFS で連結成分番号を振る
    std::vector<int> rstk;
    rstk.reserve(n);
    int ptr = 0;
    for (auto i : order) {
        if (~comp[i]) continue;
        comp[i] = ptr;
        rstk.emplace_back(i);
        while (!rstk.empty()) {
            int v = rstk.back();
            rstk.pop_back();
            for (int u : rg[v]) {
                if (~comp[u]) continue;
                comp[u] = ptr;
                rstk.emplace_back(u);
            }
        }
        ++ptr;
    }

    return comp;
};

/// @brief 有向非巡回グラフの構築
/// @tparam G 重み付きグラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
template <weighted_graph_type G>
list_graph<graph_weight_t<G>> make_directed_acyclic_graph(const G &g, const std::vector<int> &v) {
    list_graph<graph_weight_t<G>> res(*std::max_element(v.begin(), v.end()) + 1);
    for (auto &e : g.all_edges()) {
        int x = v[e.from()], y = v[e.to()];
        if (x != y) res.add_edge(x, y, e.weight());
    }
    return res;
}
