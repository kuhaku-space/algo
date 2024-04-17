#include <queue>
#include <vector>
#include "graph/graph.hpp"

/**
 * @brief 全域木
 * @details 全域木を構築する
 *
 * @tparam T 辺の重みの型
 * @param g グラフ
 * @param r 始点
 * @return Graph<T>
 */
template <class T>
Graph<T> spanning_tree(const Graph<T> &g, int r = 0) {
    int n = g.size();
    Graph<T> res(n);
    std::queue<int> que;
    std::vector<bool> visited(n);
    que.emplace(r);
    visited[r] = true;
    while (!que.empty()) {
        int x = que.front();
        que.pop();
        for (auto &e : g[x]) {
            if (!visited[e.to()]) {
                res.add_edges(e);
                que.emplace(e.to());
                visited[e.to()] = true;
            }
        }
    }
    return res;
}
