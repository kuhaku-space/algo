#pragma once
#include "graph/graph.hpp"
#include "template/template.hpp"

/**
 * @brief 全方位木dp
 * @see https://algo-logic.info/tree-dp/
 *
 * @tparam M モノイド
 * @tparam T 辺の重みの型
 */
template <class M, class T>
struct ReRooting {
  private:
    using Value = typename M::value_type;

  public:
    ReRooting(const Graph<T> &g) : graph(g), dp(g.size()), data(g.size()) { this->build(); }

    const auto &operator[](int i) const { return this->data[i]; }
    auto &operator[](int i) { return this->data[i]; }
    const auto begin() const { return this->data.begin(); }
    auto begin() { return this->data.begin(); }
    const auto end() const { return this->data.end(); }
    auto end() { return this->data.end(); }

  private:
    Graph<T> graph;
    std::vector<std::vector<Value>> dp;
    std::vector<Value> data;

    void build() {
        this->dfs(0);
        this->bfs(0);
    }

    Value dfs(int v, int p = -1) {
        Value res = M::id;
        int deg = graph[v].size();
        dp[v] = std::vector<Value>(deg, M::id);
        for (int i = 0; i < deg; ++i) {
            auto e = graph[v][i];
            if (e.to() == p) continue;
            dp[v][i] = M::f(dfs(e.to(), v), e.weight());
            res = M::op(res, dp[v][i]);
        }
        return M::g(res, v);
    }
    void bfs(int v, int p = -1, Value dp_p = M::id) {
        int deg = graph[v].size();
        std::vector<Value> dp_r(deg + 1, M::id);
        for (int i = deg - 1; i >= 0; --i) {
            auto e = graph[v][i];
            if (e.to() == p) dp[v][i] = M::f(dp_p, e.weight());
            dp_r[i] = M::op(dp[v][i], dp_r[i + 1]);
        }
        Value dp_l = M::id;
        for (int i = 0; i < deg; ++i) {
            int u = graph[v][i].to();
            if (u != p) this->bfs(u, v, M::g(M::op(dp_l, dp_r[i + 1]), v));
            dp_l = M::op(dp_l, dp[v][i]);
        }
        data[v] = M::g(dp_l, v);
    }
};
