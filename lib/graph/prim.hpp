#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief プリム法
 * @details 最小全域木を求める
 *
 * @tparam T
 * @param g グラフ
 * @param r 
 * @return std::vector<typename Graph<T>::edge_type>
 */
template <class T>
std::vector<typename Graph<T>::edge_type> prim(const Graph<T> &g, int r = 0) {
    using _edge = typename Graph<T>::edge_type;
    std::vector<_edge> res;
    std::vector<bool> visited(g.size());
    visited[r] = true;
    std::priority_queue<_edge, std::vector<_edge>, greater<>> p_que;
    for (auto &e : g[r]) { p_que.emplace(e); }
    while (!p_que.empty()) {
        auto e = p_que.top();
        p_que.pop();
        if (visited[e.to]) continue;
        visited[e.to] = true;
        res.emplace_back(e);
        for (auto &f : g[e.to]) {
            if (!visited[f.to]) p_que.emplace(f);
        }
    }
    return res;
}
