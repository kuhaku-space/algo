#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief 強連結成分分解
 *
 * @tparam T 辺の重みの型
 * @param g グラフ
 * @return std::vector<int> 各頂点が属する強連結成分の番号
 */
template <class T>
std::vector<int> scc(const Graph<T> &g) {
    int n = g.size();
    Graph<void> rg(n);
    std::vector<int> comp(n, -1), order;
    std::vector<bool> used(n);

    for (auto &es : g) {
        for (auto &e : es) rg.add_edge(e.to(), e.from());
    }

    auto dfs = [&](auto self, int index) {
        if (used[index]) return;
        used[index] = true;
        for (auto &e : g[index]) self(self, e.to());
        order.emplace_back(index);
    };
    auto rdfs = [&](auto self, int index, int count) {
        if (~comp[index]) return;
        comp[index] = count;
        for (auto &e : rg[index]) self(self, e.to(), count);
    };

    for (int i = 0; i < n; ++i) dfs(dfs, i);
    std::reverse(order.begin(), order.end());
    int ptr = 0;
    for (auto i : order) {
        if (comp[i] == -1) rdfs(rdfs, i, ptr++);
    }

    return comp;
};

/**
 * @brief 有向非巡回グラフの構築
 *
 * @tparam T 辺の重みの型
 * @param g グラフ
 * @param v 各頂点が属する強連結成分の番号
 * @return Graph<T> 有向非巡回グラフ
 */
template <class T>
Graph<T> make_DAG(const Graph<T> &g, const std::vector<int> &v) {
    Graph<T> res(*std::max_element(v.begin(), v.end()) + 1);
    for (auto &es : g) {
        for (auto &e : es) {
            int x = v[e.from()], y = v[e.to()];
            if (x != y) res.add_edge(x, y, e.weight());
        }
    }
    return res;
}
