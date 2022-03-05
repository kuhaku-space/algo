#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief 強連結成分分解
 *
 * @tparam T 辺の重みの型
 * @param g グラフ
 * @return vector<int> 各頂点が属する強連結成分の番号
 */
template <class T>
vector<int> scc(const Graph<T> &g) {
    int n = g.size();
    Graph<T> rg(n);
    vector<int> comp(n, -1), order;
    vector<bool> used(n);

    for (auto &es : g) {
        for (auto &e : es) rg.add_edge(e.to, e.from);
    }

    auto dfs = [&](auto self, int idx) {
        if (used[idx]) return;
        used[idx] = true;
        for (auto &e : g[idx]) self(self, e.to);
        order.emplace_back(idx);
    };
    auto rdfs = [&](auto self, int idx, int cnt) {
        if (~comp[idx]) return;
        comp[idx] = cnt;
        for (auto &e : rg[idx]) self(self, e.to, cnt);
    };

    for (int i = 0; i < n; i++) dfs(dfs, i);
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
Graph<T> make_DAG(const Graph<T> &g, const vector<int> &v) {
    Graph<T> res(*std::max_element(v.begin(), v.end()) + 1);
    for (auto &es : g) {
        for (auto &e : es) {
            int x = v[e.from], y = v[e.to];
            if (x != y) res.add_edge(x, y, e.dist);
        }
    }
    return res;
}

vector<int> scc(const Graph<void> &g) {
    int n = g.size();
    Graph<void> rg(n);
    vector<int> comp(n, -1), order;
    vector<bool> used(n);

    for (int i = 0; i < n; ++i) {
        for (auto &e : g[i]) rg.add_edge(e, i);
    }

    auto dfs = [&](auto self, int idx) {
        if (used[idx]) return;
        used[idx] = true;
        for (auto &e : g[idx]) self(self, e);
        order.emplace_back(idx);
    };
    auto rdfs = [&](auto self, int idx, int cnt) {
        if (~comp[idx]) return;
        comp[idx] = cnt;
        for (auto &e : rg[idx]) self(self, e, cnt);
    };

    for (int i = 0; i < n; i++) dfs(dfs, i);
    std::reverse(order.begin(), order.end());
    int ptr = 0;
    for (auto i : order) {
        if (comp[i] == -1) rdfs(rdfs, i, ptr++);
    }

    return comp;
};

Graph<void> make_DAG(const Graph<void> &g, const vector<int> &v) {
    int n = g.size();
    Graph<void> res(*std::max_element(v.begin(), v.end()) + 1);
    for (int i = 0; i < n; ++i) {
        for (auto &e : g[i]) {
            int x = v[i], y = v[e];
            if (x != y) res.add_edge(x, y);
        }
    }
    return res;
}
