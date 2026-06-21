#pragma once
#include <cassert>
#include <cstdint>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

/// @brief ダブリング
/// @details 各要素の「次の遷移先」を 2^k ステップ分前計算し、`jump`/`solve` で
///          任意ステップ数のジャンプを O(log k) で行う。
///          モノイド `M` を与えると遷移に沿った値を集約し、`solve` が `{遷移先, 集約値}` を返す。
/// @tparam L 前計算する段数（2^L ステップまで扱える）。
/// @tparam M モノイド型（`value_type` / `id()` / `op()` を持つ）。`void` なら遷移先のみを
///           扱い、`jump`/`solve` は `int` を返す（`max_step` は提供しない）。
/// @note `void` は内部で `std::monostate` に正規化し、本体を 1 つに保つ。集約表は
///       モノイドがあるときだけ実体を持つ。
template <int L = 20, class M = void>
struct doubling {
  private:
    static constexpr bool has_monoid = !std::is_void_v<M>;
    // M=void でも実体化できるよう値型を正規化する（void のときは monostate）。
    template <class U>
    struct value_of {
        using type = std::monostate;
    };
    template <class U>
    requires(!std::is_void_v<U>)
    struct value_of<U> {
        using type = typename U::value_type;
    };
    using T = typename value_of<M>::type;

  public:
    // モノイドなし: 遷移先のみ。
    explicit doubling(const std::vector<int> &to)
    requires(!has_monoid)
        : doubling((int)to.size()) {
        build(to, std::vector<std::monostate>(to.size()));
    }
    // モノイドあり: 各要素の初期値 v を与える。
    template <class U>
    requires has_monoid
    doubling(const std::vector<int> &to, const std::vector<U> &v) : doubling((int)to.size()) {
        build(to, v);
    }

    // モノイドなしなら遷移先 int、ありなら {遷移先, 集約値}。
    auto jump(int f, std::uint64_t k) { return solve(f, k); }
    auto solve(int f, std::uint64_t k) {
        assert(-1 <= f && f < _size);
        if constexpr (has_monoid) {
            T res = M::id();
            for (int cnt = 0; k > 0; k >>= 1, ++cnt) {
                if ((k & 1) && f != -1) {
                    res = M::op(res, data[cnt][f]);
                    f = table[cnt][f];
                }
            }
            return std::make_pair(f, res);
        } else {
            for (int cnt = 0; k > 0; k >>= 1, ++cnt) {
                if ((k & 1) && f != -1) f = table[cnt][f];
            }
            return f;
        }
    }

    /// @brief check(M::op(init, accumulated)) が真である最大ステップ数を返す
    /// @details check は単調 (真→偽に一度だけ変化) を仮定する
    template <class F>
    requires has_monoid
    std::uint64_t max_step(int f, T init, F check) {
        assert(-1 <= f && f < _size);
        T acc = init;
        std::uint64_t steps = 0;
        for (int i = L - 1; i >= 0; --i) {
            if (f == -1) break;
            T next_acc = M::op(acc, data[i][f]);
            if (check(next_acc)) {
                acc = next_acc;
                f = table[i][f];
                steps |= std::uint64_t(1) << i;
            }
        }
        return steps;
    }

    template <class F>
    requires has_monoid
    std::uint64_t max_step(int f, F check) {
        return max_step(f, M::id(), check);
    }

  private:
    int _size;
    std::vector<std::vector<int>> table;
    // モノイドがあるときだけ集約表を持つ（void のときは monostate で空コスト）。
    [[no_unique_address]]
    std::conditional_t<has_monoid, std::vector<std::vector<T>>, std::monostate> data;

    explicit doubling(int n) : _size(n), table(L, std::vector<int>(n)) {
        if constexpr (has_monoid) data.assign(L, std::vector<T>(n));
    }

    template <class U>
    void build(const std::vector<int> &to, const std::vector<U> &v) {
        assert((int)to.size() == _size && (int)v.size() == _size);
        for (int i = 0; i < _size; ++i) {
            assert(-1 <= to[i] && to[i] < _size);
            table[0][i] = to[i];
            if constexpr (has_monoid) data[0][i] = v[i];
        }

        for (int i = 0; i < L - 1; ++i) {
            for (int j = 0; j < _size; ++j) {
                int k = table[i][j];
                if (k != -1) {
                    table[i + 1][j] = table[i][k];
                    if constexpr (has_monoid) data[i + 1][j] = M::op(data[i][j], data[i][k]);
                } else {
                    table[i + 1][j] = table[i][j];
                    if constexpr (has_monoid) data[i + 1][j] = data[i][j];
                }
            }
        }
    }
};
