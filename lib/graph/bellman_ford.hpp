#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief ベルマンフォード法
 *
 * @tparam T
 * @param graph グラフ
 * @param s 始点
 * @param inf
 * @return std::vector<T>
 */
template <class T>
std::vector<T> bellman_ford(const Graph<T> &graph, int s = 0, T inf = numeric_limits<T>::max()) {
    int n = graph.size();
    std::vector<T> dists(n, inf);
    dists[s] = T();
    bool updated = true;
    for (int count = 0; updated && count <= n << 1; ++count) {
        updated = false;
        for (int i = 0; i < n; ++i) {
            if (dists[i] == inf) continue;
            for (auto &e : graph[i]) {
                if (dists[i] == -inf || chmin(dists[e.to()], dists[i] + e.weight())) {
                    if (dists[e.to()] == -inf) continue;
                    updated = true;
                    if (count >= n) dists[e.to()] = -inf;
                }
            }
        }
    }
    return dists;
}
