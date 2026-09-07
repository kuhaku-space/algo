#pragma once
#include <cassert>
#include <cstdint>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>
#include "segtree/monoid.hpp"

/// @file
/// @brief ダブリング (doubling)
/// @details 写像を繰り返し適用した遷移先を $O(\log k)$ で求める。各頂点から $2^i$ 回進んだ先を
///          前計算するため、関数グラフ上のジャンプや巨大な回数のシミュレーションに使える。
/// @details モノイドを指定すると、遷移先だけでなく通過した頂点に対応する値も同じ順序で集約できる。
/// @note `0 <= step < 2^L` を満たす必要がある。必要な最大ジャンプ数に合わせて `L` を指定する。
/// @note 集約値 `values[v]` は、頂点 `v` から次の頂点へ進む 1 ステップに対応する。
/// @note `to[v] == -1` は遷移先が存在しないことを表し、以後のジャンプ先も `-1` になる。
/// @note `max_step` は `M` を指定した場合だけ使える。`check` は集約値に対して真から偽へ
///       一度だけ変化する単調な述語であること。
/// @code
/// #include <iostream>
/// #include <vector>
/// #include "algorithm/doubling.hpp"
/// #include "segtree/monoid.hpp"
///
/// int main() {
///     std::vector<int> to = {1, 2, 0};
///
///     Doubling<60> jumps(to);
///     std::cout << jumps.jump(0, 5) << '\n';  // 0 -> 1 -> 2 -> 0 -> 1 -> 2
///
///     std::vector<long long> cost = {10, 20, 30};
///     Doubling<60, Add<long long>> sums(to, cost);
///     auto [vertex, total] = sums.jump(0, 5);
///     std::cout << vertex << ' ' << total << '\n';
/// }
/// @endcode

/// @brief ダブリングで `M` が取れる型か（void または monoid）
/// @details `void` は集約なし（遷移先のみ）、`monoid` は遷移に沿った値の集約を表す。
/// @complexity コンパイル時制約であり実行時計算量はない
template <class M>
concept doubling_monoid = std::is_void_v<M> || monoid<M>;

/// @brief ダブリング
/// @details 各要素の「次の遷移先」を $2^k$ ステップ分前計算し、`jump` で
///          任意ステップ数のジャンプを $O(\log k)$ で行う。
///          モノイド `M` を与えると遷移に沿った値を集約し、`jump` が `{遷移先, 集約値}` を返す。
/// @tparam L 前計算する段数（$2^L$ ステップまで扱える）。
/// @tparam M モノイド型（`value_type` / `id()` / `op()` を持つ）。`void` なら遷移先のみを
///           扱い、`jump` は `int` を返す（`max_step` は提供しない）。
/// @note `void` は内部で `std::monostate` に正規化し、本体を 1 つに保つ。集約表は
///       モノイドがあるときだけ実体を持つ。
template <int L = 20, doubling_monoid M = void>
struct Doubling {
  private:
    static constexpr bool has_monoid = !std::is_void_v<M>;
    // M=void のときは value_type=monostate を持つ空モノイド型へ差し替える。
    // conditional_t は型を選ぶだけで ::value_type の評価は選択後の 1 回なので、
    // void::value_type のハードエラーは起きない。
    struct VoidMonoid {
        using value_type = std::monostate;
    };
    using stored_value = typename std::conditional_t<has_monoid, M, VoidMonoid>::value_type;

  public:
    /// @brief 遷移先のみを前計算する
    /// @param to 各頂点から1ステップ後の遷移先
    /// @complexity 頂点数を $n$ として $O(Ln)$
    explicit Doubling(const std::vector<int> &to)
    requires(!has_monoid)
        : Doubling((int)to.size()) {
        build(to, std::vector<std::monostate>(to.size()));
    }
    /// @brief 遷移先と各ステップの集約値を前計算する
    /// @param to 各頂点から1ステップ後の遷移先
    /// @param values 各頂点から進む1ステップに対応する値
    /// @complexity 頂点数を $n$ として $O(Ln)$
    template <class U>
    requires has_monoid
    Doubling(const std::vector<int> &to, const std::vector<U> &values) : Doubling((int)to.size()) {
        build(to, values);
    }

    /// @brief vからstepステップ後の遷移先と必要なら集約値を返す
    /// @complexity $O(L)=O(\log \mathrm{step})$
    auto jump(int v, std::uint64_t step) const {
        assert(-1 <= v && v < n);
        if constexpr (has_monoid) {
            stored_value res = M::id();
            for (int i = 0; step > 0; step >>= 1, ++i) {
                if ((step & 1) && v != -1) {
                    res = M::op(res, prod_table[i][v]);
                    v = next_table[i][v];
                }
            }
            return std::make_pair(v, res);
        } else {
            for (int i = 0; step > 0; step >>= 1, ++i) {
                if ((step & 1) && v != -1) v = next_table[i][v];
            }
            return v;
        }
    }

    /// @brief check(M::op(init, accumulated)) が真である最大ステップ数を返す
    /// @details check は単調 (真→偽に一度だけ変化) を仮定する
    /// @complexity $O(L)$
    template <class F>
    requires has_monoid
    std::uint64_t max_step(int v, stored_value init, F check) const {
        assert(-1 <= v && v < n);
        stored_value acc = init;
        std::uint64_t steps = 0;
        for (int i = L - 1; i >= 0; --i) {
            if (v == -1) break;
            stored_value next_acc = M::op(acc, prod_table[i][v]);
            if (check(next_acc)) {
                acc = next_acc;
                v = next_table[i][v];
                steps |= std::uint64_t(1) << i;
            }
        }
        return steps;
    }

    /// @brief 単位元から開始してcheckが真である最大ステップ数を返す
    /// @details check は単調 (真→偽に一度だけ変化) を仮定する
    /// @complexity $O(L)$
    template <class F>
    requires has_monoid
    std::uint64_t max_step(int v, F check) const {
        return max_step(v, M::id(), check);
    }

  private:
    int n;
    std::vector<std::vector<int>> next_table;
    // モノイドがあるときだけ集約表を持つ（void のときは monostate で空コスト）。
    [[no_unique_address]]
    std::conditional_t<has_monoid, std::vector<std::vector<stored_value>>, std::monostate> prod_table;

    explicit Doubling(int _n) : n(_n), next_table(L, std::vector<int>(_n)) {
        if constexpr (has_monoid) prod_table.assign(L, std::vector<stored_value>(_n));
    }

    template <class U>
    void build(const std::vector<int> &to, const std::vector<U> &values) {
        assert((int)to.size() == n && (int)values.size() == n);
        for (int i = 0; i < n; ++i) {
            assert(-1 <= to[i] && to[i] < n);
            next_table[0][i] = to[i];
            if constexpr (has_monoid) prod_table[0][i] = values[i];
        }

        for (int i = 0; i < L - 1; ++i) {
            for (int v = 0; v < n; ++v) {
                int nxt = next_table[i][v];
                if (nxt != -1) {
                    next_table[i + 1][v] = next_table[i][nxt];
                    if constexpr (has_monoid) prod_table[i + 1][v] = M::op(prod_table[i][v], prod_table[i][nxt]);
                } else {
                    next_table[i + 1][v] = next_table[i][v];
                    if constexpr (has_monoid) prod_table[i + 1][v] = prod_table[i][v];
                }
            }
        }
    }
};
