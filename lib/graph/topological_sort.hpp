#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief 閉路検出
 * 
 * @tparam T 辺の重みの型
 * @param g グラフ
 * @return true 閉路あり
 * @return false 閉路なし
 */
template <class T>
bool has_cycle(const Graph<T> &g) {
    int n = g.size();
    std::vector<bool> is_seen(n), is_finish(n);
    bool res = false;

    auto dfs = [&](auto self, int idx) {
        if (is_finish[idx]) return;
        is_seen[idx] = true;
        for (auto &e : g[idx]) {
            if (res |= is_seen[e.to]) return;
            self(self, e.to);
        }
        is_seen[idx] = false;
        is_finish[idx] = true;
    };

    for (int i = 0; i < n; ++i) {
        if (res) break;
        dfs(dfs, i);
    }
    return res;
}

template <>
bool has_cycle<void>(const Graph<void> &g) {
    int n = g.size();
    std::vector<bool> is_seen(n), is_finish(n);
    bool res = false;

    auto dfs = [&](auto self, int idx) {
        if (is_finish[idx]) return;
        is_seen[idx] = true;
        for (auto &e : g[idx]) {
            if (res |= is_seen[e]) return;
            self(self, e);
        }
        is_seen[idx] = false;
        is_finish[idx] = true;
    };

    for (int i = 0; i < n; ++i) {
        if (res) break;
        dfs(dfs, i);
    }
    return res;
}

/**
 * @brief トポロジカルソート
 * 
 * @tparam T 辺の重みの型
 * @param g グラフ
 * @return std::vector<int> 頂点の順序
 */
template <class T>
std::vector<int> topological_sort(const Graph<T> &g) {
    int n = g.size();
    std::vector<int> res;
    std::vector<bool> is_seen(n);
    auto dfs = [&](auto self, int v) {
        if (is_seen[v]) return;
        is_seen[v] = true;
        for (auto &e : g[v])
            if (!is_seen[e.to]) self(self, e.to);
        res.emplace_back(v);
    };
    for (int i = 0; i < n; ++i) dfs(dfs, i);
    std::reverse(res.begin(), res.end());
    return res;
}

template <>
std::vector<int> topological_sort<void>(const Graph<void> &g) {
    int n = g.size();
    std::vector<int> res;
    std::vector<bool> is_seen(n);
    auto dfs = [&](auto self, int v) {
        if (is_seen[v]) return;
        is_seen[v] = true;
        for (auto &e : g[v])
            if (!is_seen[e]) self(self, e);
        res.emplace_back(v);
    };
    for (int i = 0; i < n; ++i) dfs(dfs, i);
    std::reverse(res.begin(), res.end());
    return res;
}
