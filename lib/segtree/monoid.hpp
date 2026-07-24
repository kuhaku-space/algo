#pragma once
#include <algorithm>
#include <concepts>
#include <limits>
#include <numeric>
#include <utility>

/// @brief モノイドの要件
/// @details 値型 `value_type`、単位元 `id()`、二項演算 `op()` を持つこと。
/// @tparam M 判定対象の型
/// @complexity コンパイル時制約で実行時計算量はない
template <class M>
concept monoid = requires {
    typename M::value_type;
    { M::id() } -> std::same_as<typename M::value_type>;
    {
        M::op(std::declval<const typename M::value_type &>(), std::declval<const typename M::value_type &>())
    } -> std::same_as<typename M::value_type>;
};

/// @brief 作用素モノイド M を値型 U に作用させられるか
/// @details モノイドに加えて作用 `f(作用素, 値)` を持つこと。遅延セグ木では `op` が作用素の合成、
///          `f` が値への作用を表す。`f` は関数テンプレートでも非テンプレートでもよい。
/// @tparam M 作用素モノイド
/// @tparam U 作用させる値の型
/// @complexity コンパイル時制約で実行時計算量はない
template <class M, class U>
concept acts_on = monoid<M> && requires(const typename M::value_type &m, const U &x) {
    { M::f(m, x) } -> std::convertible_to<U>;
};

/// @brief 和モノイド
/// @tparam T 要素の型
/// @complexity 各演算 $O(1)$
template <class T>
struct Add {
    /// @brief 値型
    /// @complexity 型エイリアスで実行時計算量はない
    using value_type = T;
    /// @brief 加法単位元0を返す
    /// @complexity $O(1)$
    static constexpr T id() noexcept { return T(0); }
    /// @brief lhs+rhsを返す
    /// @complexity $O(1)$
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return lhs + rhs; }

    /// @brief lhsをrhsへ加算して作用する
    /// @complexity $O(1)$
    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return lhs + rhs;
    }
};

/// @brief 積モノイド
/// @tparam T 要素の型
/// @complexity 各演算 $O(1)$
template <class T>
struct Mul {
    /// @brief 値型
    /// @complexity 型エイリアスで実行時計算量はない
    using value_type = T;
    /// @brief 乗法単位元1を返す
    /// @complexity $O(1)$
    static constexpr T id() noexcept { return T(1); }
    /// @brief lhs*rhsを返す
    /// @complexity $O(1)$
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return lhs * rhs; }

    /// @brief lhsをrhsへ乗算して作用する
    /// @complexity $O(1)$
    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return lhs * rhs;
    }
};

/// @brief ビット積モノイド
/// @details 単位元は全ビットが 1 の値（符号付き型でも正しく動作する）。
/// @tparam T 要素の型
/// @complexity 各演算 $O(1)$
template <class T>
struct And {
    /// @brief 値型
    /// @complexity 型エイリアスで実行時計算量はない
    using value_type = T;
    /// @brief 全bitが1の単位元を返す
    /// @complexity $O(1)$
    static constexpr T id() noexcept { return ~T(0); }
    /// @brief bit積を返す
    /// @complexity $O(1)$
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return lhs & rhs; }

    /// @brief bit積を作用する
    /// @complexity $O(1)$
    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return lhs & rhs;
    }
};

/// @brief ビット和モノイド
/// @tparam T 要素の型
/// @complexity 各演算 $O(1)$
template <class T>
struct Or {
    /// @brief 値型
    /// @complexity 型エイリアスで実行時計算量はない
    using value_type = T;
    /// @brief 単位元0を返す
    /// @complexity $O(1)$
    static constexpr T id() noexcept { return T(0); }
    /// @brief bit和を返す
    /// @complexity $O(1)$
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return lhs | rhs; }

    /// @brief bit和を作用する
    /// @complexity $O(1)$
    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return lhs | rhs;
    }
};

/// @brief ビット排他的論理和モノイド
/// @tparam T 要素の型
/// @complexity 各演算 $O(1)$
template <class T>
struct Xor {
    /// @brief 値型
    /// @complexity 型エイリアスで実行時計算量はない
    using value_type = T;
    /// @brief 単位元0を返す
    /// @complexity $O(1)$
    static constexpr T id() noexcept { return T(0); }
    /// @brief bit排他的論理和を返す
    /// @complexity $O(1)$
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return lhs ^ rhs; }

    /// @brief bit排他的論理和を作用する
    /// @complexity $O(1)$
    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return lhs ^ rhs;
    }
};

/// @brief 最小値モノイド
/// @details 単位元は型の最大値。
/// @tparam T 要素の型
/// @complexity 各演算 $O(1)$
template <class T>
struct Min {
    /// @brief 値型
    /// @complexity 型エイリアスで実行時計算量はない
    using value_type = T;
    /// @brief 型の最大値を単位元として返す
    /// @complexity $O(1)$
    static constexpr T id() noexcept { return std::numeric_limits<T>::max(); }
    /// @brief 小さい方を返す
    /// @complexity $O(1)$
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return std::min(lhs, rhs); }

    /// @brief rhsをlhs以下へ制限する
    /// @complexity $O(1)$
    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return std::min(U(lhs), rhs);
    }
};

/// @brief 最大値モノイド
/// @details 単位元は型の最小値。
/// @tparam T 要素の型
/// @complexity 各演算 $O(1)$
template <class T>
struct Max {
    /// @brief 値型
    /// @complexity 型エイリアスで実行時計算量はない
    using value_type = T;
    /// @brief 型の最小値を単位元として返す
    /// @complexity $O(1)$
    static constexpr T id() noexcept { return std::numeric_limits<T>::lowest(); }
    /// @brief 大きい方を返す
    /// @complexity $O(1)$
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return std::max(lhs, rhs); }

    /// @brief rhsをlhs以上へ制限する
    /// @complexity $O(1)$
    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return std::max(U(lhs), rhs);
    }
};

/// @brief 最大値モノイド（単位元 0 固定）
/// @details 「何も選ばない」ことを単位元 0 として扱いたい場合に使う（`Max<T>` は単位元が型の最小値）。
/// @tparam T 要素の型
/// @complexity 各演算 $O(1)$
template <class T>
struct MaxZero {
    /// @brief 値型
    /// @complexity 型エイリアスで実行時計算量はない
    using value_type = T;
    /// @brief 単位元0を返す
    /// @complexity $O(1)$
    static constexpr T id() noexcept { return T(0); }
    /// @brief 大きい方を返す
    /// @complexity $O(1)$
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return std::max(lhs, rhs); }

    /// @brief rhsをlhs以上へ制限する
    /// @complexity $O(1)$
    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return std::max(U(lhs), rhs);
    }
};

/// @brief 最大公約数モノイド
/// @details gcd(0, x) = x なので 0 が単位元。
/// @tparam T 要素の型
/// @complexity `id`は $O(1)$、`op`は $O(\log\min(lhs,rhs))$
template <class T>
struct Gcd {
    /// @brief 値型
    /// @complexity 型エイリアスで実行時計算量はない
    using value_type = T;
    /// @brief 単位元0を返す
    /// @complexity $O(1)$
    static constexpr T id() noexcept { return T(0); }
    /// @brief 最大公約数を返す
    /// @complexity $O(\log\min(lhs,rhs))$
    static constexpr T op(const T &lhs, const T &rhs) { return std::gcd(lhs, rhs); }
};

/// @brief 最小公倍数モノイド
/// @details lcm(1, x) = x なので 1 が単位元。
/// @tparam T 要素の型
/// @complexity `id`は $O(1)$、`op`は $O(\log\min(lhs,rhs))$
template <class T>
struct Lcm {
    /// @brief 値型
    /// @complexity 型エイリアスで実行時計算量はない
    using value_type = T;
    /// @brief 単位元1を返す
    /// @complexity $O(1)$
    static constexpr T id() noexcept { return T(1); }
    /// @brief 最小公倍数を返す
    /// @complexity $O(\log\min(lhs,rhs))$
    static constexpr T op(const T &lhs, const T &rhs) { return std::lcm(lhs, rhs); }
};

/// @brief 上書きモノイド（後勝ち）
/// @details 「未設定」を表す番兵を単位元とする。値域にこの値を含めないこと。
/// @tparam T 要素の型
/// @complexity 各演算 $O(1)$
template <class T>
struct Update {
    /// @brief 値型
    /// @complexity 型エイリアスで実行時計算量はない
    using value_type = T;
    /// @brief 未設定を表す番兵を返す
    /// @complexity $O(1)$
    static constexpr T id() noexcept { return std::numeric_limits<T>::max(); }
    /// @brief 新しい上書き値を優先して合成する
    /// @complexity $O(1)$
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return lhs == id() ? rhs : lhs; }

    /// @brief 未設定でなければlhsでrhsを上書きする
    /// @complexity $O(1)$
    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return lhs == id() ? rhs : U(lhs);
    }
};

/// @brief アフィン変換モノイド
/// @details f(x) = a * x + b を [a, b] で表す。op(g, h) は「先に g、次に h を適用」した合成。
/// @tparam T 係数の型
/// @complexity 各演算 $O(1)$
template <class T>
struct Affine {
    /// @brief 係数pair型
    /// @complexity 型エイリアスで実行時計算量はない
    using P = std::pair<T, T>;
    /// @brief 値型
    /// @complexity 型エイリアスで実行時計算量はない
    using value_type = P;
    /// @brief 恒等変換を返す
    /// @complexity $O(1)$
    static constexpr P id() { return P(T(1), T(0)); }
    /// @brief 2つのアフィン変換を合成する
    /// @complexity $O(1)$
    static constexpr P op(const P &lhs, const P &rhs) {
        return {lhs.first * rhs.first, rhs.first * lhs.second + rhs.second};
    }
};

/// @brief モノイドの演算順序を反転するアダプタ
/// @tparam M 元となるモノイド
/// @complexity 元のモノイドの各演算と同じ
template <class M>
struct Rev {
    /// @brief 元のモノイドの値型
    /// @complexity 型エイリアスで実行時計算量はない
    using value_type = typename M::value_type;
    /// @brief 元のモノイドの単位元を返す
    /// @complexity $M::id$ と同じ
    static constexpr value_type id() { return M::id(); }
    /// @brief 引数順を逆にして元の演算を適用する
    /// @complexity $M::op$ と同じ
    static constexpr value_type op(const value_type &lhs, const value_type &rhs) { return M::op(rhs, lhs); }
};
