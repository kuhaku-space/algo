#pragma once
#include <cmath>
#include <cstdint>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include "segtree/monoid.hpp"

/// @see https://maspypy.com/モノイド作用に関する離散対数問題

namespace internal {

/// @brief モノイド作用に関する離散対数問題の本体（Baby-step Giant-step）
/// @details 作用素 `x`（演算 `op` で合成、単位元 `id`）を状態に作用 `act` させ、
///          `x^n` を `s` に作用させた結果が `t` と一致する最小の `n` を `[lb, ub)` から返す。
///          群とは限らず逆元を仮定しないため、giant-step での一致は候補にすぎず、
///          区間を線形走査して実際の解を確認する。線形走査が 2 回空振りしたら解なしと判定する。
///          `to_key` は到達しうる状態上で単射（衝突しない完全キー）であることを呼び出し側が保証する。
/// @return 最小の `n`。存在しなければ -1。
/// @note `N = ub - lb`、ブロック幅 `√N` で baby-step・giant-step を回すため全体 O(√N)。
///       作用 `act` は O(√N) 回（baby-step √N + giant-step √N + 線形走査は高々 2 ブロックで 2√N）、
///       合成 `op` は二分累乗の O(log N) 回。
/// @complexity $N=ub-lb$ として期待 $O(\sqrt N)$
template <class X, class S, class Op, class Act, class Key>
std::int64_t discrete_log_core(X x, S s, const S &t, const X &id, Op op, Act act, Key to_key, std::int64_t lb,
                               std::int64_t ub) {
    if (lb >= ub) return -1;

    // x^n を二分累乗で計算
    auto xpow = [&](std::int64_t n) {
        X p = x, res = id;
        while (n) {
            if (n & 1) res = op(res, p);
            p = op(p, p);
            n >>= 1;
        }
        return res;
    };

    const auto key_t = to_key(t);
    s = act(xpow(lb), s);  // 探索開始位置まで進める（x^lb s）
    const std::uint64_t lim = static_cast<std::uint64_t>(ub - lb);
    const std::int64_t block = static_cast<std::int64_t>(std::sqrt(static_cast<long double>(lim))) + 1;

    // baby-step: x^j t（1 <= j <= block）のキーを記録
    std::unordered_set<std::decay_t<decltype(key_t)>> seen;
    seen.reserve(static_cast<std::size_t>(block) * 2);
    {
        S cur = t;
        for (std::int64_t j = 0; j < block; ++j) {
            cur = act(x, cur);
            seen.insert(to_key(cur));
        }
    }

    // giant-step: x^{k*block} s を block 刻みで進めて候補を探す
    const X giant = xpow(block);
    bool failed = false;
    for (std::int64_t k = 0; k <= block; ++k) {
        S next = act(giant, s);
        if (seen.count(to_key(next))) {
            // 候補ブロック [k*block, (k+1)*block) を線形走査
            S cur = s;
            for (std::int64_t i = 0; i < block; ++i) {
                if (to_key(cur) == key_t) {
                    const std::int64_t ans = k * block + i + lb;
                    return ans >= ub ? -1 : ans;
                }
                cur = act(x, cur);
            }
            if (failed) return -1;  // 2 回目の空振り
            failed = true;
        }
        s = std::move(next);
    }
    return -1;
}

}  // namespace internal

/// @brief モノイド作用に関する離散対数問題
/// @details 作用素モノイド `M`（合成 `op`・単位元 `id`・作用 `f`）の元 `x` について、
///          `x^n` を状態 `s` に作用させた結果が `t` となる最小の `n` を `[lb, ub)` から返す。
///          逆元を仮定しないモノイド作用で動く（標準的な離散対数・関数反復の合成などを含む）。
/// @tparam M 作用素モノイド（`acts_on<M, U>` を満たすこと）
/// @tparam U 状態の型
/// @tparam Key 状態を単射に写すキー関数 `U -> 整数等`
/// @return 最小の `n`。存在しなければ -1。
/// @complexity `N = ub - lb` として O(√N)。内訳はモノイド作用 `f` が O(√N) 回、
///       モノイド合成 `op` が O(log N) 回、キー関数 `to_key` が O(√N) 回（ハッシュ集合操作込み）。
template <class M, class U, class Key>
requires acts_on<M, U>
std::int64_t discrete_log_acted(const typename M::value_type &x, U s, U t, Key to_key, std::int64_t lb,
                                std::int64_t ub) {
    using X = typename M::value_type;
    return internal::discrete_log_core<X, U>(
        x, std::move(s), std::move(t), M::id(), [](const X &a, const X &b) { return M::op(a, b); },
        [](const X &o, const U &v) { return U(M::f(o, v)); }, std::move(to_key), lb, ub);
}

/// @brief モノイド `M` における離散対数 `a^n = b`
/// @details 作用を左からの合成 `op` とみなした特殊形。群の `log_a b` を含む。
/// @tparam M モノイド
/// @tparam Key 値を単射に写すキー関数
/// @return 最小の `n`（`[lb, ub)`）。存在しなければ -1。
/// @complexity `N = ub - lb` として O(√N)（合成 `op` を O(√N) 回・二分累乗で O(log N) 回）。
template <class M, class Key>
requires monoid<M>
std::int64_t discrete_log_monoid(typename M::value_type a, typename M::value_type b, Key to_key, std::int64_t lb,
                                 std::int64_t ub) {
    using X = typename M::value_type;
    return internal::discrete_log_core<X, X>(
        a, M::id(), std::move(b), M::id(), [](const X &x, const X &y) { return M::op(x, y); },
        [](const X &o, const X &v) { return M::op(o, v); }, std::move(to_key), lb, ub);
}
