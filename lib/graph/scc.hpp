#pragma once
#include <algorithm>
#include <vector>
#include "graph/graph.hpp"
#include "internal/internal_csr.hpp"

/// @brief 強連結成分分解
template <class T>
std::vector<int> scc(const Graph<T> &g) {
    int n = g.size();
    std::vector<int> comp(n, -1), order;
    std::vector<bool> used(n);

    internal::graph_csr rg(n);
    for (auto &es : g) {
        for (auto &e : es) rg.add_edge(e.to(), e.from());
    }
    rg.build();

    auto dfs = [&](auto self, int index) {
        if (used[index]) return;
        used[index] = true;
        for (auto &e : g[index]) self(self, e.to());
        order.emplace_back(index);
    };
    auto rdfs = [&](auto self, int index, int count) {
        if (~comp[index]) return;
        comp[index] = count;
        for (int u : rg[index]) self(self, u, count);
    };

    for (int i = 0; i < n; ++i) dfs(dfs, i);
    std::reverse(order.begin(), order.end());
    int ptr = 0;
    for (auto i : order) {
        if (comp[i] == -1) rdfs(rdfs, i, ptr++);
    }

    return comp;
};

std::vector<int> scc(const internal::graph_csr &g) {
    int n = g.size();
    std::vector<int> comp(n, -1), order;
    std::vector<bool> used(n);

    internal::graph_csr rg(n);
    for (int i = 0; i < n; ++i) {
        for (int u : g[i]) rg.add_edge(u, i);
    }
    rg.build();

    auto dfs = [&](auto self, int index) {
        if (used[index]) return;
        used[index] = true;
        for (int u : g[index]) self(self, u);
        order.emplace_back(index);
    };
    auto rdfs = [&](auto self, int index, int count) {
        if (~comp[index]) return;
        comp[index] = count;
        for (int u : rg[index]) self(self, u, count);
    };

    for (int i = 0; i < n; ++i) dfs(dfs, i);
    std::reverse(order.begin(), order.end());
    int ptr = 0;
    for (auto i : order) {
        if (comp[i] == -1) rdfs(rdfs, i, ptr++);
    }

    return comp;
};

/// @brief 有向非巡回グラフの構築
template <class T>
Graph<T> make_directed_acyclic_graph(const Graph<T> &g, const std::vector<int> &v) {
    Graph<T> res(*std::max_element(v.begin(), v.end()) + 1);
    for (auto &es : g) {
        for (auto &e : es) {
            int x = v[e.from()], y = v[e.to()];
            if (x != y) res.add_edge(x, y, e.weight());
        }
    }
    return res;
}

template <>
Graph<void> make_directed_acyclic_graph(const Graph<void> &g, const std::vector<int> &v) {
    Graph<void> res(*std::max_element(v.begin(), v.end()) + 1);
    for (auto &es : g) {
        for (auto &e : es) {
            int x = v[e.from()], y = v[e.to()];
            if (x != y) res.add_edge(x, y);
        }
    }
    return res;
}

internal::graph_csr make_directed_acyclic_graph(internal::graph_csr &g, const std::vector<int> &v) {
    int n = *std::max_element(v.begin(), v.end()) + 1;
    internal::graph_csr res(n);
    for (int i = 0; i < n; ++i) {
        for (int u : g[i]) {
            int x = v[i], y = v[u];
            if (x != y) res.add_edge(x, y);
        }
    }
    return res;
}
