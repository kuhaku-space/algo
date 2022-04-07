#include "graph/graph.hpp"
#include "template/template.hpp"

std::vector<int> shortest_path(const Graph<void> &g, int s = 0,
                               int inf = std::numeric_limits<int>::max()) {
    std::vector<int> dists(g.size(), inf);
    std::queue<int> que;
    dists[s] = 0;
    que.emplace(s);
    while (!que.empty()) {
        auto index = que.front();
        que.pop();
        for (auto &e : g[index]) {
            if (chmin(dists[e.to()], dists[index] + 1)) que.emplace(e.to());
        }
    }
    return dists;
}
