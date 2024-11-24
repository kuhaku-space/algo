#include <stack>
#include <vector>
#include "graph/graph.hpp"

template <class T>
std::vector<int> tree_bfs(const Graph<T> &g, int r = 0) {
    int pos = 0;
    std::vector<int> res;
    std::vector<bool> visited(g.size());
    res.emplace_back(r);
    visited[r] = true;
    while (pos < (int)res.size()) {
        auto index = res[pos++];
        for (auto &e : g[index]) {
            if (visited[e.to()]) continue;
            res.emplace_back(e.to());
            visited[e.to()] = true;
        }
    }
    return res;
}

std::vector<int> tree_bfs(const std::vector<int> &parents) {
    int n = parents.size();
    Graph<void> g(n);
    int r = 0;
    for (int i = 0; i < n; ++i) {
        if (parents[i] == -1 || parents[i] == i) {
            r = i;
            continue;
        }
        g.add_edges(i, parents[i]);
    }
    return tree_bfs(g, r);
}

template <class T>
std::vector<int> tree_dfs(const Graph<T> &g, int r = 0) {
    std::vector<int> res;
    auto dfs = [&g, &res](auto self, int index, int parent) -> void {
        res.emplace_back(index);
        for (auto &e : g[index]) {
            if (e.to() == parent) continue;
            self(self, e.to(), index);
        }
    };
    dfs(dfs, r, -1);
    return res;
}

/// @brief 木の距離を求める
template <class T, class U = T>
std::vector<U> tree_dist(const Graph<T> &g, int r = 0) {
    std::vector<U> res(g.size(), -1);
    std::stack<int> st;
    res[r] = 0;
    st.emplace(r);
    while (!st.empty()) {
        auto index = st.top();
        st.pop();
        for (auto &e : g[index]) {
            if (res[e.to()] != -1) continue;
            res[e.to()] = res[index] + e.weight();
            st.emplace(e.to());
        }
    }
    return res;
}

/// @brief 木の頂点の親を求める
template <class T>
std::vector<int> tree_parent(const Graph<T> &g, int r = 0) {
    std::vector<int> res(g.size(), -1);
    std::stack<int> st;
    res[r] = r;
    st.emplace(r);
    while (!st.empty()) {
        auto index = st.top();
        st.pop();
        for (auto &e : g[index]) {
            if (res[e.to()] != -1) continue;
            res[e.to()] = index;
            st.emplace(e.to());
        }
    }
    res[r] = -1;
    return res;
}

/// @brief 部分木の大きさを求める
template <class T>
std::vector<int> tree_subtree(const Graph<T> &g, int r = 0) {
    std::vector<int> res(g.size());
    auto dfs = [&g, &res](auto self, int index) -> int {
        res[index] = 1;
        for (auto &e : g[index]) {
            if (res[e.to()] != 0) continue;
            res[index] += self(self, e.to());
        }
        return res[index];
    };
    dfs(dfs, r);
    return res;
}
