#pragma once
#include <compare>
#include <utility>
#include <vector>
#include "persistent_ds/persistent_stack.hpp"

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
