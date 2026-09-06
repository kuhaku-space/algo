#pragma once
#include <compare>
#include <utility>
#include <vector>
#include "persistent_ds/persistent_stack.hpp"

/// @file
/// @brief 経路つき DP 値 (Traced)
/// @details DP の値に、そこへ至る経路を相乗りさせる値型。比較は `cost` のみで行い、経路は push が
///          $O(1)$ の永続スタックで保持する。経路を持ち回っても比較コストは増えないので、
///          DP の時間計算量は変わらない。
/// @details 遷移のたびに `then(w, label)` でラベルを積み、最後に `to_vector()` で始点から終点の順に
///          取り出す。遷移元を記録する配列と復元ループの両方が不要になるので、「DP 本体は書けたが
///          復元でバグる」「DP と復元で遷移の場合分けが食い違う」を避けたいときに使う。
/// @note `T` には `operator<=>` と `operator+` を要求する。`Label` に要求するのはコピー構築のみ。
/// @note 始点の `Traced` は経路が空なので、`to_vector()` に始点のラベルは含まれない。
/// @note 空間計算量は `then` の結果を採用した回数 $U$ について $O(U)$。永続スタックのノードは
///       解放しないので、状態数が非常に多い DP では遷移元を記録する方式のほうがメモリで有利になる。
/// @note 単一の値への explicit コンストラクタしか持たないため、`dp[i] = 0` のような代入は
///       コンパイルエラーになる。経路を落とす代入を事故で書けないようにするための制約。
/// @note `then` は `cost + w` でコストを合成する。別の合成が必要なときは
///       `Traced(std::max(dp[i].cost, w), dp[i].path.push(label))` のようにメンバから直接組む。
/// @note 最大化する DP では比較を反転させるだけでよい（`dp[j] < cand` で更新する）。
/// @code
/// #include <iostream>
/// #include <vector>
/// #include "dp/traced.hpp"
///
/// int main() {
///     // 段 i から i+1 へ a[i]、i+2 へ b[i] のコストで進むときの最小コストと経路
///     std::vector<long long> a = {2, 5, 1, 3}, b = {8, 4, 6};
///     constexpr long long inf = 1'000'000'000'000'000'000;
///     int n = 5;
///
///     std::vector<Traced<long long>> dp(n, Traced<long long>(inf));
///     dp[0] = Traced<long long>(0);
///     for (int i = 0; i < n; ++i) {
///         if (dp[i].cost == inf) continue;
///         if (i + 1 < n) {
///             if (auto cand = dp[i].then(a[i], i + 1); cand < dp[i + 1]) dp[i + 1] = cand;
///         }
///         if (i + 2 < n) {
///             if (auto cand = dp[i].then(b[i], i + 2); cand < dp[i + 2]) dp[i + 2] = cand;
///         }
///     }
///
///     std::cout << dp[n - 1].cost << '\n';
///     for (int v : dp[n - 1].to_vector()) std::cout << v << ' ';  // 始点 0 は含まない
///     std::cout << '\n';
/// }
/// @endcode

/// @brief 経路を相乗りさせたDPの値
/// @details 比較は `cost` のみで行い、経路は push が $O(1)$ の永続スタックで保持する。
///          そのため経路を持ち回っても比較コストは増えず、DPの時間計算量は変わらない。
///          遷移のたびに `then(w, label)` でラベルを積み、最後に `to_vector()` で
///          始点から終点の順に取り出す。遷移元を記録する配列と復元ループが不要になる。
/// @tparam T コストの型。`operator<=>` と `operator+` を持つこと。
/// @tparam Label 経路に積むラベルの型（頂点番号・選んだ添字など）
/// @note メモリは `then` の結果を採用した回数に比例し、永続スタックのノードは解放されない。
///       状態数が非常に多いDPでは、遷移元を記録する方式のほうがメモリで有利になる。
template <class T, class Label = int>
struct Traced {
    /// @brief コストの型
    /// @complexity 型エイリアスで実行時計算量はない
    using value_type = T;
    /// @brief ラベルの型
    /// @complexity 型エイリアスで実行時計算量はない
    using label_type = Label;
    /// @brief 経路を保持する永続スタックの型
    /// @complexity 型エイリアスで実行時計算量はない
    using path_type = persistent_stack<Label>;

    /// @brief 比較に使うコスト
    /// @complexity $O(1)$ で参照可能
    T cost;
    /// @brief 積んだラベルの列（先頭が最後に積んだラベル）
    /// @complexity $O(1)$ で参照可能
    path_type path;

    /// @brief コストを `T()`、経路を空にして構築する
    /// @complexity $O(1)$
    constexpr Traced() : cost(), path() {}

    /// @brief コストを指定し、経路を空にして構築する
    /// @note 経路の情報を落とさないよう暗黙変換にはしていない。
    /// @complexity $O(1)$
    constexpr explicit Traced(T _cost) : cost(std::move(_cost)), path() {}

    /// @brief コストと経路を直接指定して構築する
    /// @details `then` では表せない結合（`max(cost, w)` を使うボトルネック最短路など）は
    ///          `Traced(std::max(dp[i].cost, w), dp[i].path.push(label))` のように直接組む。
    /// @complexity $O(1)$
    constexpr Traced(T _cost, path_type _path) : cost(std::move(_cost)), path(std::move(_path)) {}

    /// @brief `cost` のみで比較する
    /// @complexity $O(1)$
    constexpr auto operator<=>(const Traced &rhs) const { return cost <=> rhs.cost; }

    /// @brief `cost` のみで比較する
    /// @complexity $O(1)$
    constexpr bool operator==(const Traced &rhs) const { return cost == rhs.cost; }

    /// @brief コストに w を足し、経路に label を積んだ値を返す
    /// @complexity $O(1)$
    Traced then(const T &w, const Label &label) const { return Traced(cost + w, path.push(label)); }

    /// @brief 積んだラベルの個数を返す
    /// @complexity $O(1)$
    constexpr int size() const { return path.size(); }

    /// @brief 積んだラベルを積んだ順（始点から終点）に返す
    /// @complexity 経路長を $L$ として $O(L)$
    std::vector<Label> to_vector() const {
        std::vector<Label> res(path.size());
        auto cur = path;
        for (int i = (int)res.size() - 1; i >= 0; --i) {
            res[i] = cur.top();
            cur = cur.pop();
        }
        return res;
    }
};
