#include "graph/graph.hpp"
#include "template/template.hpp"

template <class T>
vector<int> tree_subtree(const Graph<T> &g, int r = 0) {
    vector<int> res(g.size());
    auto dfs = [&g, &res](auto &&self, int idx, int par) {
        res[idx] = 1;
        for (auto i : g[idx]) {
            if (i.to == par) continue;
            res[idx] += self(self, i.to, idx);
        }
        return res[idx];
    };
    dfs(dfs, 0, -1);
    return res;
}

template <>
vector<int> tree_subtree(const Graph<void> &g, int r = 0) {
    vector<int> res(g.size());
    auto dfs = [&g, &res](auto &&self, int idx, int par) {
        res[idx] = 1;
        for (auto i : g[idx]) {
            if (i == par) continue;
            res[idx] += self(self, i.to, idx);
        }
        return res[idx];
    };
    dfs(dfs, 0, -1);
    return res;
}
