#pragma once
#include <concepts>
#include <vector>
#include "graph/graph.hpp"
#include "segtree/monoid.hpp"

/// @brief 全方位木dp用モノイドの確定値型（`key_type`、省略時は `value_type`）
/// @details 全方位木dp は 2 つの型を扱う:
///          - `value_type`（集約型 Sum）: 単位元 `id` と `op` で畳み込まれる、部分木を集約した値の型。
///          - `key_type`（確定値型 Key）: 頂点で `g` により確定した値（= 出力）の型。`f` の入力でもある。
///          多くの問題は Sum = Key で済むため、`key_type` を省略すると `value_type` にフォールバックする。
/// @tparam M モノイド
/// @complexity 型特性のため実行時コストなし
template <class M>
struct rerooting_key {
    /// @brief 確定値型。既定では `M::value_type`
    /// @complexity 型エイリアスのため実行時コストなし
    using type = typename M::value_type;
};
/// @brief `M::key_type` が定義されている場合の確定値型
/// @complexity 型特性のため実行時コストなし
template <class M>
requires requires { typename M::key_type; }
struct rerooting_key<M> {
    /// @brief `M` が明示した確定値型
    /// @complexity 型エイリアスのため実行時コストなし
    using type = typename M::key_type;
};
/// @brief 全方位木 DP の確定値型
/// @complexity 型エイリアスのため実行時コストなし
template <class M>
using rerooting_key_t = typename rerooting_key<M>::type;

/// @brief 全方位木dp用モノイドの要件
/// @details 集約型 `value_type` 上のモノイド（単位元 `id`・子の集約 `op`）に加えて、
///          辺を通す変換 `f(確定値, 辺重み) -> 集約値` と、頂点で確定する変換
///          `g(集約値, 頂点データ) -> 確定値` を持つこと。確定値型は `key_type`
///          （省略時 `value_type`）。`f` / `g` は関数テンプレートでも非テンプレートでもよい。
/// @tparam M 判定対象のモノイド
/// @tparam W 辺重みの型
/// @tparam U 頂点データの型
/// @complexity コンパイル時の型制約のため実行時コストなし
template <class M, class W, class U>
concept rerooting_monoid =
    monoid<M> && requires(const rerooting_key_t<M> &k, const typename M::value_type &s, const W &w, const U &u) {
        { M::f(k, w) } -> std::convertible_to<typename M::value_type>;
        { M::g(s, u) } -> std::convertible_to<rerooting_key_t<M>>;
    };

/// @brief 全方位木dp
/// @see https://algo-logic.info/tree-dp/
/// @details 非連結（森）にも対応する。各連結成分をそれぞれ独立に処理する。
///          集約型 `value_type` と確定値型 `key_type`（省略時 `value_type`）を区別でき、
///          `operator[]` は確定値型を返す。
/// @tparam M 全方位木dp用モノイド（`rerooting_monoid`）
/// @tparam G 重み付きグラフ型（`list_graph<T>` / `csr_graph<T>` のいずれでも可）
/// @tparam U 頂点データの型
/// @complexity 構築は $O(V + E)$、結果の参照とイテレータ取得は $O(1)$
template <class M, weighted_graph_type G, class U>
requires rerooting_monoid<M, graph_weight_t<G>, U>
struct Rerooting {
  private:
    using Sum = typename M::value_type;  // 集約型（id / op の対象、dp が保持する型）
    using Key = rerooting_key_t<M>;      // 確定値型（g の結果・f の入力・出力）

  public:
    /// @brief グラフ `g` と各頂点のデータ `v` から全ての根に対する DP 値を計算する
    /// @complexity $O(V + E)$
    Rerooting(const G &g, const std::vector<U> &v) : g_(g), data(v), dp(g.size()), values(g.size()) { build(); }

    /// @brief 頂点 `i` を根とした結果を読み取り専用で返す
    /// @complexity $O(1)$
    const auto &operator[](int i) const { return values[i]; }
    /// @brief 頂点 `i` を根とした結果を返す
    /// @complexity $O(1)$
    auto &operator[](int i) { return values[i]; }
    /// @brief 結果列の先頭を指す読み取り専用イテレータを返す
    /// @complexity $O(1)$
    const auto begin() const { return values.begin(); }
    /// @brief 結果列の先頭を指すイテレータを返す
    /// @complexity $O(1)$
    auto begin() { return values.begin(); }
    /// @brief 結果列の終端を指す読み取り専用イテレータを返す
    /// @complexity $O(1)$
    const auto end() const { return values.end(); }
    /// @brief 結果列の終端を指すイテレータを返す
    /// @complexity $O(1)$
    auto end() { return values.end(); }

  private:
    G g_;
    const std::vector<U> &data;
    std::vector<std::vector<Sum>> dp;
    std::vector<Key> values;

    void build() {
        if ((int)g_.size() == 0) return;
        dfs_iter();
        bfs_iter();
    }

    // 反復版の dfs（再帰だと深い木でスタックオーバーフローしうる）。
    // 帰りがけに各頂点の確定値 ret[v] = M::g(op(子のdp), data[v]) を求め、
    // 親側の dp[親][自分への辺] = M::f(ret[v], 辺重み) を更新する。
    // 森に対応するため、未訪問の各頂点を根として回す。
    void dfs_iter() {
        int n = g_.size();
        std::vector<Key> ret(n);                 // 各頂点の確定値（設定直後に親側で消費）
        std::vector<Sum> res(n, M::id());        // 各頂点の子 dp の op 集約
        std::vector<int> par(n, -1), pe(n, -1);  // 親と「親→自分」の辺添字
        std::vector<bool> visited(n, false);     // 連結成分ごとに 1 度だけ根にするための訪問印
        struct frame {
            int v, p, idx;
        };
        std::vector<frame> stk;
        stk.reserve(n);
        for (int i = 0; i < n; ++i) dp[i] = std::vector<Sum>(g_[i].size(), M::id());
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

    // 反復版の bfs（行きがけに親から伝播する確定値 dp_p を渡しながら values を確定）。
    // 森に対応するため、未訪問の各頂点を根として回す。
    void bfs_iter() {
        int n = g_.size();
        std::vector<int> par(n, -1);
        std::vector<Key> dp_p_of(n);          // 各頂点が親から受け取る確定値 dp_p（根では未使用）
        std::vector<bool> visited(n, false);  // 連結成分ごとに 1 度だけ根にするための訪問印
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
                Key dp_p = dp_p_of[v];
                int deg = g_[v].size();
                std::vector<Sum> dp_r(deg + 1, M::id());
                for (int i = deg - 1; i >= 0; --i) {
                    auto e = g_[v][i];
                    if (e.to() == p) dp[v][i] = M::f(dp_p, e.weight());
                    dp_r[i] = M::op(dp[v][i], dp_r[i + 1]);
                }
                Sum dp_l = M::id();
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
