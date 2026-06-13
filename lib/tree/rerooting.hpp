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
        if ((int)graph.size() == 0) return;
        dfs_iter();
        bfs_iter();
    }

    // 反復版の dfs（再帰だと深い木でスタックオーバーフローしうる）。
    // 帰りがけに各頂点の集約値 ret[v] = M::g(op(子のdp), data[v]) を確定し、
    // 親側の dp[親][自分への辺] を更新する。
    void dfs_iter() {
        int n = graph.size();
        std::vector<Value> ret(n, M::id());
        std::vector<Value> res(n, M::id());  // 各頂点の子 dp の op 集約
        std::vector<int> par(n, -1), pe(n, -1);  // 親と「親→自分」の辺添字
        struct frame {
            int v, p, idx;
        };
        std::vector<frame> st;
        for (int i = 0; i < n; ++i) dp[i] = std::vector<Value>(graph[i].size(), M::id());
        st.push_back({0, -1, 0});
        while (!st.empty()) {
            frame &f = st.back();
            int v = f.v;
            if (f.idx < (int)graph[v].size()) {
                int i = f.idx++;
                auto e = graph[v][i];
                if (e.to() == f.p) continue;
                par[e.to()] = v;
                pe[e.to()] = i;
                st.push_back({e.to(), v, 0});
            } else {
                ret[v] = M::g(res[v], data[v]);
                int p = par[v];
                st.pop_back();
                if (p != -1) {
                    dp[p][pe[v]] = M::f(ret[v], graph[p][pe[v]].weight());
                    res[p] = M::op(res[p], dp[p][pe[v]]);
                }
            }
        }
    }

    // 反復版の bfs（行きがけに親から伝播する dp_p を渡しながら values を確定）。
    void bfs_iter() {
        int n = graph.size();
        std::vector<int> par(n, -1);
        std::vector<Value> dp_p_of(n, M::id());  // 各頂点が親から受け取る dp_p
        std::vector<int> st = {0};
        // 行きがけ順に処理（スタックでも順序非依存: values は各頂点 1 回書く）
        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            int p = par[v];
            Value dp_p = dp_p_of[v];
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
                if (u != p) {
                    par[u] = v;
                    dp_p_of[u] = M::g(M::op(dp_l, dp_r[i + 1]), data[v]);
                    st.push_back(u);
                }
                dp_l = M::op(dp_l, dp[v][i]);
            }
            values[v] = M::g(dp_l, data[v]);
        }
    }
};
