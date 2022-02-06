#include "template/template.hpp"
#include "graph/graph.hpp"

/**
 * @brief ベルマンフォード法
 * 
 * @tparam T 
 * @param graph グラフ
 * @param s 始点
 * @param inf 
 * @return vector<T> 
 */
template <class T>
vector<T> bellman_ford(const Graph<T> &graph, int s = 0,
                       T inf = numeric_limits<T>::max()) {
    int n = graph.size();
    vector<T> dists(n, inf);
    dists[s] = T();
    bool is_updated = true;
    for (int count = 0; is_updated && count <= n << 1; ++count) {
        is_updated = false;
        for (int i = 0; i < n; ++i) {
            if (dists[i] == inf) continue;
            for (auto &j : graph[i]) {
                if (dists[i] == -inf || chmin(dists[j.to], dists[i] + j.dist)) {
                    if (dists[j.to] == -inf) continue;
                    is_updated = true;
                    if (count >= n) dists[j.to] = -inf;
                }
            }
        }
    }
    return dists;
}
