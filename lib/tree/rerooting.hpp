#pragma once
#include <vector>
#include "graph/graph.hpp"

/// @brief 全方位木dp
/// @see https://algo-logic.info/tree-dp/
template <class M, class T, class U>
struct ReRooting {
  private:
    using Value = typename M::value_type;

  public:
    ReRooting(const Graph<T> &g, const std::vector<U> &v)
        : graph(g), data(v), dp(g.size()), values(g.size()) {
        build();
    }

    const auto &operator[](int i) const { return values[i]; }
    auto &operator[](int i) { return values[i]; }
    const auto begin() const { return values.begin(); }
    auto begin() { return values.begin(); }
    const auto end() const { return values.end(); }
    auto end() { return values.end(); }

  private:
    Graph<T> graph;
    const std::vector<U> &data;
    std::vector<std::vector<Value>> dp;
    std::vector<Value> values;

    void build() {
        dfs(0);
        bfs(0);
    }

    Value dfs(int v, int p = -1) {
        Value res = M::id();
        int deg = graph[v].size();
        dp[v] = std::vector<Value>(deg, M::id());
        for (int i = 0; i < deg; ++i) {
            auto e = graph[v][i];
            if (e.to() == p) continue;
            dp[v][i] = M::f(dfs(e.to(), v), e.weight());
            res = M::op(res, dp[v][i]);
        }
        return M::g(res, data[v]);
    }
    void bfs(int v, int p = -1, Value dp_p = M::id()) {
        int deg = graph[v].size();
        std::vector<Value> dp_r(deg + 1, M::id());
        for (int i = deg - 1; i >= 0; --i) {
            auto e = graph[v][i];
            if (e.to() == p) dp[v][i] = M::f(dp_p, e.weight());
            dp_r[i] = M::op(dp[v][i], dp_r[i + 1]);
        }
        Value dp_l = M::id();
        for (int i = 0; i < deg; ++i) {
            int u = graph[v][i].to();
            if (u != p) bfs(u, v, M::g(M::op(dp_l, dp_r[i + 1]), data[v]));
            dp_l = M::op(dp_l, dp[v][i]);
        }
        values[v] = M::g(dp_l, v);
    }
};
