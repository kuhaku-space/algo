#pragma once
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>
#include "graph/graph.hpp"

/// @brief 単一始点最短路（実重み付きグラフはダイクストラ法）
/// @tparam G 実重み付きグラフ型（`list_graph<T>` / `csr_graph<T>`、T は非 void）
/// @note 重みなしグラフ（`*_graph<void>`）は下の BFS 版が選ばれる。
template <properly_weighted_graph_type G, class T = graph_weight_t<G>>
std::vector<T> shortest_path(const G &g, int s = 0, T inf = std::numeric_limits<T>::max()) {
    // pair は first（距離）優先で比較されるので greater<> で最小ヒープになる。
    using node = std::pair<T, int>;
    std::vector<T> dists(g.size(), inf);
    std::priority_queue<node, std::vector<node>, std::greater<>> p_que;
    dists[s] = T();
    p_que.emplace(T(), s);
    while (!p_que.empty()) {
        auto [d, v] = p_que.top();
        p_que.pop();
        if (dists[v] < d) continue;
        for (auto &e : g[v]) {
            if (d + e.weight() < dists[e.to()]) {
                dists[e.to()] = d + e.weight();
                p_que.emplace(dists[e.to()], e.to());
            }
        }
    }
    return dists;
}

/// @brief 単一始点最短路（負辺ありはベルマンフォード法）
/// @note 負閉路から到達できる頂点の距離は `ninf`（既定で `lowest()`）になる。
/// @tparam G 重み付きグラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
template <weighted_graph_type G, class T = graph_weight_t<G>>
std::vector<T> shortest_path_negative(const G &g, int s = 0, T inf = std::numeric_limits<T>::max(),
                                      T ninf = std::numeric_limits<T>::lowest()) {
    int n = g.size();
    std::vector<T> dists(n, inf);
    dists[s] = T();
    // 前半 n-1 回で最短距離を確定、後半 n-1 回で負閉路の影響を ninf として伝播する。
    bool updated = true;
    for (int count = 0; updated && count < 2 * n - 1; ++count) {
        updated = false;
        for (int i = 0; i < n; ++i) {
            if (dists[i] == inf) continue;
            for (auto &e : g[i]) {
                if (dists[i] == ninf || dists[i] + e.weight() < dists[e.to()]) {
                    if (dists[e.to()] == ninf) continue;
                    updated = true;
                    // n 回目以降の更新は負閉路に由来するので ninf にする。
                    if (count >= n - 1) dists[e.to()] = ninf;
                    else dists[e.to()] = dists[i] + e.weight();
                }
            }
        }
    }
    return dists;
}

/// @brief 単一始点最短路（負辺ありは SPFA）
/// @note 負閉路を検出した場合は空の `vector` を返す。
/// @see https://hogloid.hatenablog.com/entry/20120409/1333973448
/// @see https://ei1333.github.io/luzhiled/snippets/graph/shortest-path-faster-algorithm.html
/// @tparam G 重み付きグラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
template <weighted_graph_type G, class T = graph_weight_t<G>>
std::vector<T> shortest_path_spfa(const G &g, int s = 0, T inf = std::numeric_limits<T>::max()) {
    int n = g.size();
    std::vector<T> dists(n, inf);
    std::vector<bool> pending(n, false);
    std::vector<int> times(n, 0);
    std::queue<int> que;
    dists[s] = T();
    pending[s] = true;
    ++times[s];
    que.emplace(s);
    while (!que.empty()) {
        int p = que.front();
        que.pop();
        pending[p] = false;
        for (auto &e : g[p]) {
            if (!(dists[p] + e.weight() < dists[e.to()])) continue;
            dists[e.to()] = dists[p] + e.weight();
            if (!pending[e.to()]) {
                if (++times[e.to()] >= n) return std::vector<T>();
                pending[e.to()] = true;
                que.emplace(e.to());
            }
        }
    }
    return dists;
}

/// @brief 単一始点最短路（重みなしグラフは BFS で O(V+E)）
/// @tparam G 重みなしグラフ型（`list_graph<void>` / `csr_graph<void>` のいずれでも可）
/// @note 重みが 1 固定なので priority_queue 不要。`unweighted_graph_type` と
///       `properly_weighted_graph_type` は排他なので、重みなしグラフではこちらが選ばれる。
template <unweighted_graph_type G>
std::vector<int> shortest_path(const G &g, int s = 0, int inf = std::numeric_limits<int>::max()) {
    std::vector<int> dists(g.size(), inf);
    std::queue<int> que;
    dists[s] = 0;
    que.emplace(s);
    while (!que.empty()) {
        auto v = que.front();
        que.pop();
        for (auto &e : g[v]) {
            if (dists[v] + 1 < dists[e.to()]) {
                dists[e.to()] = dists[v] + 1;
                que.emplace(e.to());
            }
        }
    }
    return dists;
}
