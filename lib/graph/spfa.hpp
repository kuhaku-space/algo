#pragma once
#include "graph/graph.hpp"
#include "template/template.hpp"

/// @brief SPFA
/// @see https://hogloid.hatenablog.com/entry/20120409/1333973448
/// @see https://ei1333.github.io/luzhiled/snippets/graph/shortest-path-faster-algorithm.html
template <class T>
std::vector<T> shortest_path_faster_algorithm(Graph<T> &g, int s, T inf = std::numeric_limits<T>::max()) {
    int n = g.size();
    std::vector<T> dists(n, inf);
    std::vector<int> pending(n, 0), times(n, 0);
    std::queue<int> que;
    que.emplace(s);
    pending[s] = true;
    ++times[s];
    dists[s] = 0;
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
