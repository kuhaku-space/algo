#include "graph/graph.hpp"
#include "template/template.hpp"

template <class T>
std::vector<int> tree_bfs(const Graph<T> &g, int r = 0) {
    int pos = 0;
    std::vector<int> res;
    std::vector<bool> visited(g.size());
    res.emplace_back(r);
    visited[r] = true;
    while (pos < res.size()) {
        auto index = res[pos++];
        for (auto &e : g[index]) {
            if (visited[e.to()]) continue;
            res.emplace_back(e.to());
            visited[e.to()] = true;
        }
    }
    return res;
}
