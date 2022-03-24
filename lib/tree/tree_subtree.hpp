#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief 部分木の大きさを求める
 * 
 * @tparam T 辺の重みの型
 * @param g グラフ
 * @param r 根
 * @return std::vector<int> 
 */
template <class T>
std::vector<int> tree_subtree(const Graph<T> &g, int r = 0) {
    std::vector<int> res(g.size());
    auto dfs = [&g, &res](auto &&self, int index, int parent) {
        res[index] = 1;
        for (auto &e : g[index]) {
            if (e.to() == parent) continue;
            res[index] += self(self, e.to(), index);
        }
        return res[index];
    };
    dfs(dfs, r, -1);
    return res;
}
