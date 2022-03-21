#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief 全域木
 * @details 全域木を構築する
 * 
 * @tparam T 
 * @param g グラフ
 * @param r 始点
 * @return Graph<T> 
 */
template <class T>
Graph<T> spanning_tree(const Graph<T> &g, int r = 0) {
    int n = g.size();
    Graph<void> res(n);
    std::queue<int> que;
    std::vector<bool> visited(n);
    que.emplace(r);
    visited[r] = true;
    while (!que.empty()) {
        auto x = que.front();
        que.pop();
        for (auto &e : g[x]) {
            if (!visited[e]) {
                res.add_edges(x, e);
                que.emplace(e);
                visited[e] = true;
            }
        }
    }
    return res;
}
