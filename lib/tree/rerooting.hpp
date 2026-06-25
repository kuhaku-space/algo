#pragma once
#include <concepts>
#include <vector>
#include "graph/graph.hpp"
#include "segtree/monoid.hpp"

/// @brief 全方位木dp用モノイドの要件
/// @details モノイド（子の集約 `op`・単位元 `id`）に加えて、辺を通す変換 `f(値, 辺重み)` と
///          頂点で確定する変換 `g(値, 頂点データ)` を持つこと。`f` / `g` は関数テンプレートでも
///          非テンプレートでもよい。
/// @tparam M 判定対象のモノイド
/// @tparam W 辺重みの型
/// @tparam U 頂点データの型
template <class M, class W, class U>
concept rerooting_monoid = monoid<M> && requires(const typename M::value_type &v, const W &w, const U &u) {
    { M::f(v, w) } -> std::convertible_to<typename M::value_type>;
    { M::g(v, u) } -> std::convertible_to<typename M::value_type>;
};

/// @brief 全方位木dp
/// @see https://algo-logic.info/tree-dp/
/// @details 非連結（森）にも対応する。各連結成分をそれぞれ独立に処理する。
/// @tparam M 全方位木dp用モノイド（`rerooting_monoid`）
/// @tparam G 重み付きグラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @tparam U 頂点データの型
template <class M, weighted_graph_type G, class U>
requires rerooting_monoid<M, graph_weight_t<G>, U>
struct ReRooting {
  private:
    using Value = typename M::value_type;

  public:
    ReRooting(const G &g, const std::vector<U> &v) : g_(g), data(v), dp(g.size()), values(g.size()) { build(); }

    const auto &operator[](int i) const { return values[i]; }
    auto &operator[](int i) { return values[i]; }
    const auto begin() const { return values.begin(); }
    auto begin() { return values.begin(); }
    const auto end() const { return values.end(); }
    auto end() { return values.end(); }

  private:
    G g_;
    const std::vector<U> &data;
    std::vector<std::vector<Value>> dp;
    std::vector<Value> values;

    void build() {
        if ((int)g_.size() == 0) return;
        dfs_iter();
        bfs_iter();
    }

    // 反復版の dfs（再帰だと深い木でスタックオーバーフローしうる）。
    // 帰りがけに各頂点の集約値 ret[v] = M::g(op(子のdp), data[v]) を確定し、
    // 親側の dp[親][自分への辺] を更新する。森に対応するため、未訪問の各頂点を根として回す。
    void dfs_iter() {
        int n = g_.size();
        std::vector<Value> ret(n, M::id());
        std::vector<Value> res(n, M::id());      // 各頂点の子 dp の op 集約
        std::vector<int> par(n, -1), pe(n, -1);  // 親と「親→自分」の辺添字
        std::vector<bool> visited(n, false);     // 連結成分ごとに 1 度だけ根にするための訪問印
        struct frame {
            int v, p, idx;
        };
        std::vector<frame> stk;
        stk.reserve(n);
        for (int i = 0; i < n; ++i) dp[i] = std::vector<Value>(g_[i].size(), M::id());
        for (int s = 0; s < n; ++s) {
            if (visited[s]) continue;
            visited[s] = true;
            stk.push_back({s, -1, 0});
            while (!stk.empty()) {
                frame &f = stk.back();
                int v = f.v;
                if (f.idx < (int)g_[v].size()) {
                    int i = f.idx++;
                    auto e = g_[v][i];
                    if (e.to() == f.p) continue;
                    par[e.to()] = v;
                    pe[e.to()] = i;
                    visited[e.to()] = true;
                    stk.push_back({e.to(), v, 0});
                } else {
                    ret[v] = M::g(res[v], data[v]);
                    int p = par[v];
                    stk.pop_back();
                    if (p != -1) {
                        dp[p][pe[v]] = M::f(ret[v], g_[p][pe[v]].weight());
                        res[p] = M::op(res[p], dp[p][pe[v]]);
                    }
                }
            }
        }
    }

    // 反復版の bfs（行きがけに親から伝播する dp_p を渡しながら values を確定）。
    // 森に対応するため、未訪問の各頂点を根として回す。
    void bfs_iter() {
        int n = g_.size();
        std::vector<int> par(n, -1);
        std::vector<Value> dp_p_of(n, M::id());  // 各頂点が親から受け取る dp_p
        std::vector<bool> visited(n, false);     // 連結成分ごとに 1 度だけ根にするための訪問印
        std::vector<int> stk;
        stk.reserve(n);
        for (int s = 0; s < n; ++s) {
            if (visited[s]) continue;
            visited[s] = true;
            stk.push_back(s);
            // 行きがけ順に処理（スタックでも順序非依存: values は各頂点 1 回書く）
            while (!stk.empty()) {
                int v = stk.back();
                stk.pop_back();
                int p = par[v];
                Value dp_p = dp_p_of[v];
                int deg = g_[v].size();
                std::vector<Value> dp_r(deg + 1, M::id());
                for (int i = deg - 1; i >= 0; --i) {
                    auto e = g_[v][i];
                    if (e.to() == p) dp[v][i] = M::f(dp_p, e.weight());
                    dp_r[i] = M::op(dp[v][i], dp_r[i + 1]);
                }
                Value dp_l = M::id();
                for (int i = 0; i < deg; ++i) {
                    int u = g_[v][i].to();
                    if (u != p) {
                        par[u] = v;
                        visited[u] = true;
                        dp_p_of[u] = M::g(M::op(dp_l, dp_r[i + 1]), data[v]);
                        stk.push_back(u);
                    }
                    dp_l = M::op(dp_l, dp[v][i]);
                }
                values[v] = M::g(dp_l, data[v]);
            }
        }
    }
};
