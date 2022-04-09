#include "graph/graph.hpp"
#include "template/template.hpp"

template <class T>
std::vector<int> tree_dfs(const Graph<T> &g, int r = 0) {
    std::vector<int> res;
    auto dfs = [&g, &res](auto self, int index, int parent) {
        res.emplace_back(index);
        for (auto &e : g[index]) {
            if (e.to() == parent) continue;
            self(self, e.to(), index);
        }
    };
    dfs(dfs, r, -1);
    return res;
}
