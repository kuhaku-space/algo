#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief 単一始点最短経路
 *
 * @tparam T 辺の重みの型
 * @param g グラフ
 * @param s 始点
 * @param inf
 * @return std::vector<T>
 *
 * @see https://ei1333.github.io/luzhiled/snippets/graph/shortest-path-faster-algorithm.html
 */
template <class T>
std::vector<T> shortest_path_faster_algorithm(Graph<T> &g, int s,
                                              T inf = std::numeric_limits<T>::max()) {
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
            if (!chmin(dists[e.to()], dists[p] + e.weight())) continue;
            if (!pending[e.to()]) {
                if (++times[e.to()] >= n) return std::vector<T>();
                pending[e.to()] = true;
                que.emplace(e.to());
            }
        }
    }
    return dists;
}
