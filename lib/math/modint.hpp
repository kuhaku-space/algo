#pragma once
#include <cassert>
#include <concepts>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include "internal/internal_math.hpp"
#include "internal/internal_type_traits.hpp"

namespace internal {

struct modint_base : field_base {};
struct static_modint_base {};

template <class T>
concept modint = std::is_base_of_v<modint_base, T>;

/// @brief static_modint と dynamic_modint が共有する公開演算
/// @details Derived は umod(), mul(), is_prime_mod() を提供する。
/// @complexity 各演算の行に記載
template <class Derived>
struct modint_common : modint_base {
    using mint = Derived;

    /// @brief 保持している標準剰余を返す
    /// @complexity $O(1)$
    constexpr unsigned int val() const { return _v; }

    /// @brief 1を加算する
    /// @complexity $O(1)$
    constexpr mint &operator++() {
        ++_v;
        if (_v == Derived::umod()) _v = 0;
        return derived();
    }

    /// @brief 1を減算する
    /// @complexity $O(1)$
    constexpr mint &operator--() {
        if (_v == 0) _v = Derived::umod();
        --_v;
        return derived();
    }

    /// @brief 1を加算する前の値を返す
    /// @complexity $O(1)$
    constexpr mint operator++(int) {
        mint result = derived();
        ++*this;
        return result;
    }

    /// @brief 1を減算する前の値を返す
    /// @complexity $O(1)$
    constexpr mint operator--(int) {
        mint result = derived();
        --*this;
        return result;
    }

    /// @brief rhsを加算する
    /// @complexity $O(1)$
    constexpr mint &operator+=(const mint &rhs) {
        _v += rhs._v;
        if (_v >= Derived::umod()) _v -= Derived::umod();
        return derived();
    }

    /// @brief rhsを減算する
    /// @complexity $O(1)$
    constexpr mint &operator-=(const mint &rhs) {
        _v += Derived::umod() - rhs._v;
        if (_v >= Derived::umod()) _v -= Derived::umod();
        return derived();
    }

    /// @brief rhsを乗算する
    /// @complexity $O(1)$
    constexpr mint &operator*=(const mint &rhs) {
        _v = Derived::mul(_v, rhs._v);
        return derived();
    }

    /// @brief rhsで除算する
    /// @complexity 素数法では法を $m$ として $O(\log m)$、動的法では $O(\log m)$
    constexpr mint &operator/=(const mint &rhs) { return *this *= rhs.inv(); }

    /// @brief 自身の値を返す
    /// @complexity $O(1)$
    constexpr mint operator+() const { return derived(); }

    /// @brief 加法逆元を返す
    /// @complexity $O(1)$
    constexpr mint operator-() const { return mint() - derived(); }

    /// @brief n乗を返す
    /// @complexity $O(\log n)$
    constexpr mint pow(std::int64_t n) const {
        assert(0 <= n);
        mint x = derived(), r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }

    /// @brief 乗法逆元を返す
    /// @complexity 法を $m$ として $O(\log m)$
    constexpr mint inv() const {
        if (Derived::is_prime_mod()) {
            assert(_v);
            return pow(Derived::umod() - 2);
        } else {
            auto eg = internal::inv_gcd(_v, Derived::umod());
            assert(eg.first == 1);
            return eg.second;
        }
    }

    /// @brief 和を返す
    /// @complexity $O(1)$
    friend constexpr mint operator+(const mint &lhs, const mint &rhs) { return mint(lhs) += rhs; }

    /// @brief 差を返す
    /// @complexity $O(1)$
    friend constexpr mint operator-(const mint &lhs, const mint &rhs) { return mint(lhs) -= rhs; }

    /// @brief 積を返す
    /// @complexity $O(1)$
    friend constexpr mint operator*(const mint &lhs, const mint &rhs) { return mint(lhs) *= rhs; }

    /// @brief 商を返す
    /// @complexity 法を $m$ として $O(\log m)$
    friend constexpr mint operator/(const mint &lhs, const mint &rhs) { return mint(lhs) /= rhs; }

    /// @brief 等しいか返す
    /// @complexity $O(1)$
    friend constexpr bool operator==(const mint &lhs, const mint &rhs) { return lhs._v == rhs._v; }

    /// @brief 異なるか返す
    /// @complexity $O(1)$
    friend constexpr bool operator!=(const mint &lhs, const mint &rhs) { return lhs._v != rhs._v; }

    /// @brief 整数を入力して法で正規化する
    /// @complexity $O(1)$
    friend std::istream &operator>>(std::istream &is, mint &rhs) {
        std::int64_t t;
        is >> t;
        rhs = mint(t);
        return is;
    }

    /// @brief 標準剰余を出力する
    /// @complexity $O(1)$
    friend std::ostream &operator<<(std::ostream &os, const mint &rhs) { return os << rhs._v; }

  protected:
    unsigned int _v = 0;

  private:
    constexpr mint &derived() { return *static_cast<mint *>(this); }
    constexpr const mint &derived() const { return *static_cast<const mint *>(this); }
};

}  // namespace internal

/// @brief コンパイル時に法を固定する modint
/// @complexity 四則演算は $O(1)$、累乗と逆元は $O(\log m)$
template <int m>
requires(m >= 1)
struct static_modint : internal::static_modint_base, internal::modint_common<static_modint<m>> {
    /// @brief この型自身
    /// @complexity 型エイリアスで実行時計算量はない
    using mint = static_modint;
    /// @brief 四則演算を実装する基底型
    /// @complexity 型エイリアスで実行時計算量はない
    using base = internal::modint_common<static_modint>;
    /// @brief 基底型が保持する正規化済みの値
    /// @complexity $O(1)$ で参照可能
    using base::_v;

  public:
    /// @brief 法を unsigned int で返す
    /// @complexity $O(1)$
    static constexpr unsigned int umod() { return m; }

    /// @brief 法が素数かをコンパイル時に返す
    /// @complexity コンパイル時定数で実行時計算量はない
    static constexpr bool is_prime_mod() { return internal::is_prime<m>; }

    /// @brief aとbを乗算して法mで剰余を取る
    /// @complexity $O(1)$
    static constexpr unsigned int mul(unsigned int a, unsigned int b) {
        return (unsigned int)((std::uint64_t)a * b % umod());
    }

    /// @brief 法を返す
    /// @complexity $O(1)$
    static constexpr int mod() { return m; }

    /// @brief 正規化済みの値vから検査なしで構築する
    /// @complexity $O(1)$
    static constexpr mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    /// @brief 0を構築する
    /// @complexity $O(1)$
    constexpr static_modint() = default;

    /// @brief 符号付き整数を法mで正規化して構築する
    /// @complexity $O(1)$
    template <std::integral T>
    constexpr static_modint(T v) {
        std::int64_t x = (std::int64_t)(v % (std::int64_t)(umod()));
        if (x < 0) x += umod();
        _v = (unsigned int)(x);
    }

    /// @brief 符号なし整数を法mで正規化して構築する
    /// @complexity $O(1)$
    template <std::unsigned_integral T>
    constexpr static_modint(T v) {
        _v = (unsigned int)(v % umod());
    }
};

/// @brief 実行時に法を設定する modint
/// @complexity 四則演算は $O(1)$、累乗と逆元は法を $m$ として $O(\log m)$
template <int id>
struct dynamic_modint : internal::modint_common<dynamic_modint<id>> {
    /// @brief この型自身
    /// @complexity 型エイリアスで実行時計算量はない
    using mint = dynamic_modint;
    /// @brief 四則演算を実装する基底型
    /// @complexity 型エイリアスで実行時計算量はない
    using base = internal::modint_common<dynamic_modint>;
    /// @brief 基底型が保持する正規化済みの値
    /// @complexity $O(1)$ で参照可能
    using base::_v;

  public:
    /// @brief 法を unsigned int で返す
    /// @complexity $O(1)$
    static unsigned int umod() { return bt.umod(); }

    /// @brief 法を素数として扱うか返す
    /// @complexity $O(1)$
    static bool is_prime_mod() { return false; }

    /// @brief aとbをBarrett reductionで乗算する
    /// @complexity $O(1)$
    static unsigned int mul(unsigned int a, unsigned int b) { return bt.mul(a, b); }

    /// @brief 現在の法を返す
    /// @complexity $O(1)$
    static int mod() { return (int)(bt.umod()); }

    /// @brief このidの法をmへ設定する
    /// @complexity $O(1)$
    static void set_mod(int m) {
        assert(1 <= m);
        bt = internal::barrett(m);
    }

    /// @brief 正規化済みの値vから検査なしで構築する
    /// @complexity $O(1)$
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    /// @brief 0を構築する
    /// @complexity $O(1)$
    dynamic_modint() = default;

    /// @brief 符号付き整数を現在の法で正規化して構築する
    /// @complexity $O(1)$
    template <std::integral T>
    dynamic_modint(T v) {
        std::int64_t x = (std::int64_t)(v % (std::int64_t)(mod()));
        if (x < 0) x += mod();
        _v = (unsigned int)(x);
    }

    /// @brief 符号なし整数を現在の法で正規化して構築する
    /// @complexity $O(1)$
    template <std::unsigned_integral T>
    dynamic_modint(T v) {
        _v = (unsigned int)(v % mod());
    }

  private:
    static internal::barrett bt;
};
template <int id>
internal::barrett dynamic_modint<id>::bt(998244353);

/// @brief 法998244353のstatic_modint
/// @complexity 型エイリアスで実行時計算量はない
using modint998 = static_modint<998244353>;

/// @brief 法1000000007のstatic_modint
/// @complexity 型エイリアスで実行時計算量はない
using modint107 = static_modint<1000000007>;

/// @brief 既定id -1のdynamic_modint
/// @complexity 型エイリアスで実行時計算量はない
using modint = dynamic_modint<-1>;

namespace internal {

template <class T>
concept static_modint_c = std::is_base_of_v<static_modint_base, T>;

template <class>
inline constexpr bool is_dynamic_modint_v = false;
template <int id>
inline constexpr bool is_dynamic_modint_v<dynamic_modint<id>> = true;

template <class T>
concept dynamic_modint_c = is_dynamic_modint_v<T>;

}  // namespace internal
