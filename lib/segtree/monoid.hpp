#pragma once
#include <algorithm>
#include <concepts>
#include <limits>
#include <numeric>
#include <utility>

/// @brief モノイドの要件
/// @details 値型 `value_type`、単位元 `id()`、二項演算 `op()` を持つこと。
/// @tparam M 判定対象の型
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
template <class M, class U>
concept acts_on = monoid<M> && requires(const typename M::value_type &m, const U &x) {
    { M::f(m, x) } -> std::convertible_to<U>;
};

/// @brief 和モノイド
/// @tparam T 要素の型
template <class T>
struct Add {
    using value_type = T;
    static constexpr T id() noexcept { return T(0); }
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return lhs + rhs; }

    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return lhs + rhs;
    }
};

/// @brief 積モノイド
/// @tparam T 要素の型
template <class T>
struct Mul {
    using value_type = T;
    static constexpr T id() noexcept { return T(1); }
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return lhs * rhs; }

    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return lhs * rhs;
    }
};

/// @brief ビット積モノイド
/// @details 単位元は全ビットが 1 の値（符号付き型でも正しく動作する）。
/// @tparam T 要素の型
template <class T>
struct And {
    using value_type = T;
    static constexpr T id() noexcept { return ~T(0); }
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return lhs & rhs; }

    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return lhs & rhs;
    }
};

/// @brief ビット和モノイド
/// @tparam T 要素の型
template <class T>
struct Or {
    using value_type = T;
    static constexpr T id() noexcept { return T(0); }
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return lhs | rhs; }

    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return lhs | rhs;
    }
};

/// @brief ビット排他的論理和モノイド
/// @tparam T 要素の型
template <class T>
struct Xor {
    using value_type = T;
    static constexpr T id() noexcept { return T(0); }
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return lhs ^ rhs; }

    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return lhs ^ rhs;
    }
};

/// @brief 最小値モノイド
/// @details 単位元は型の最大値。
/// @tparam T 要素の型
template <class T>
struct Min {
    using value_type = T;
    static constexpr T id() noexcept { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return std::min(lhs, rhs); }

    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return std::min(U(lhs), rhs);
    }
};

/// @brief 最大値モノイド
/// @details 単位元は型の最小値。
/// @tparam T 要素の型
template <class T>
struct Max {
    using value_type = T;
    static constexpr T id() noexcept { return std::numeric_limits<T>::lowest(); }
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return std::max(lhs, rhs); }

    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return std::max(U(lhs), rhs);
    }
};

/// @brief 最大公約数モノイド
/// @details gcd(0, x) = x なので 0 が単位元。
/// @tparam T 要素の型
template <class T>
struct Gcd {
    using value_type = T;
    static constexpr T id() noexcept { return T(0); }
    static constexpr T op(const T &lhs, const T &rhs) { return std::gcd(lhs, rhs); }
};

/// @brief 最小公倍数モノイド
/// @details lcm(1, x) = x なので 1 が単位元。
/// @tparam T 要素の型
template <class T>
struct Lcm {
    using value_type = T;
    static constexpr T id() noexcept { return T(1); }
    static constexpr T op(const T &lhs, const T &rhs) { return std::lcm(lhs, rhs); }
};

/// @brief 上書きモノイド（後勝ち）
/// @details 「未設定」を表す番兵を単位元とする。値域にこの値を含めないこと。
/// @tparam T 要素の型
template <class T>
struct Update {
    using value_type = T;
    static constexpr T id() noexcept { return std::numeric_limits<T>::max(); }
    static constexpr T op(const T &lhs, const T &rhs) noexcept { return lhs == id() ? rhs : lhs; }

    template <class U>
    static constexpr U f(const T &lhs, const U &rhs) noexcept {
        return lhs == id() ? rhs : U(lhs);
    }
};

/// @brief アフィン変換モノイド
/// @details f(x) = a * x + b を [a, b] で表す。op(g, h) は「先に g、次に h を適用」した合成。
/// @tparam T 係数の型
template <class T>
struct Affine {
    using P = std::pair<T, T>;
    using value_type = P;
    static constexpr P id() { return P(T(1), T(0)); }
    static constexpr P op(const P &lhs, const P &rhs) {
        return {lhs.first * rhs.first, rhs.first * lhs.second + rhs.second};
    }
};

/// @brief モノイドの演算順序を反転するアダプタ
/// @tparam M 元となるモノイド
template <class M>
struct Rev {
    using value_type = typename M::value_type;
    static constexpr value_type id() { return M::id(); }
    static constexpr value_type op(const value_type &lhs, const value_type &rhs) { return M::op(rhs, lhs); }
};
