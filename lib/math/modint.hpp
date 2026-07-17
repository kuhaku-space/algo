#pragma once
#include <cassert>
#include <concepts>
#include <cstdint>
#include <iostream>
#include <type_traits>
#include "internal/internal_math.hpp"

namespace internal {

struct modint_base {};
struct static_modint_base {};

template <class T>
concept modint = std::is_base_of_v<modint_base, T>;

/// CRTP base sharing operator logic between static_modint and dynamic_modint.
/// Derived must provide:
///   static {constexpr} unsigned int umod();
///   static {constexpr} unsigned int mul(unsigned int a, unsigned int b);
///   static {constexpr} bool is_prime_mod();
template <class Derived>
struct modint_common : modint_base {
    using mint = Derived;

    constexpr unsigned int val() const { return _v; }

    constexpr mint &operator++() {
        ++_v;
        if (_v == Derived::umod()) _v = 0;
        return derived();
    }
    constexpr mint &operator--() {
        if (_v == 0) _v = Derived::umod();
        --_v;
        return derived();
    }
    constexpr mint operator++(int) {
        mint result = derived();
        ++*this;
        return result;
    }
    constexpr mint operator--(int) {
        mint result = derived();
        --*this;
        return result;
    }

    constexpr mint &operator+=(const mint &rhs) {
        _v += rhs._v;
        if (_v >= Derived::umod()) _v -= Derived::umod();
        return derived();
    }
    constexpr mint &operator-=(const mint &rhs) {
        _v += Derived::umod() - rhs._v;
        if (_v >= Derived::umod()) _v -= Derived::umod();
        return derived();
    }
    constexpr mint &operator*=(const mint &rhs) {
        _v = Derived::mul(_v, rhs._v);
        return derived();
    }
    constexpr mint &operator/=(const mint &rhs) { return *this *= rhs.inv(); }

    constexpr mint operator+() const { return derived(); }
    constexpr mint operator-() const { return mint() - derived(); }

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

    friend constexpr mint operator+(const mint &lhs, const mint &rhs) { return mint(lhs) += rhs; }
    friend constexpr mint operator-(const mint &lhs, const mint &rhs) { return mint(lhs) -= rhs; }
    friend constexpr mint operator*(const mint &lhs, const mint &rhs) { return mint(lhs) *= rhs; }
    friend constexpr mint operator/(const mint &lhs, const mint &rhs) { return mint(lhs) /= rhs; }
    friend constexpr bool operator==(const mint &lhs, const mint &rhs) { return lhs._v == rhs._v; }
    friend constexpr bool operator!=(const mint &lhs, const mint &rhs) { return lhs._v != rhs._v; }
    friend std::istream &operator>>(std::istream &is, mint &rhs) {
        std::int64_t t;
        is >> t;
        rhs = mint(t);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const mint &rhs) { return os << rhs._v; }

  protected:
    unsigned int _v = 0;

  private:
    constexpr mint &derived() { return *static_cast<mint *>(this); }
    constexpr const mint &derived() const { return *static_cast<const mint *>(this); }
};

}  // namespace internal

template <int m>
requires(m >= 1)
struct static_modint : internal::static_modint_base, internal::modint_common<static_modint<m>> {
    using mint = static_modint;
    using base = internal::modint_common<static_modint>;
    using base::_v;

  public:
    static constexpr unsigned int umod() { return m; }
    static constexpr bool is_prime_mod() { return internal::is_prime<m>; }
    static constexpr unsigned int mul(unsigned int a, unsigned int b) {
        return (unsigned int)((std::uint64_t)a * b % umod());
    }

    static constexpr int mod() { return m; }
    static constexpr mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    constexpr static_modint() = default;
    template <std::integral T>
    constexpr static_modint(T v) {
        std::int64_t x = (std::int64_t)(v % (std::int64_t)(umod()));
        if (x < 0) x += umod();
        _v = (unsigned int)(x);
    }
    template <std::unsigned_integral T>
    constexpr static_modint(T v) {
        _v = (unsigned int)(v % umod());
    }
};

template <int id>
struct dynamic_modint : internal::modint_common<dynamic_modint<id>> {
    using mint = dynamic_modint;
    using base = internal::modint_common<dynamic_modint>;
    using base::_v;

  public:
    static unsigned int umod() { return bt.umod(); }
    static bool is_prime_mod() { return false; }
    static unsigned int mul(unsigned int a, unsigned int b) { return bt.mul(a, b); }

    static int mod() { return (int)(bt.umod()); }
    static void set_mod(int m) {
        assert(1 <= m);
        bt = internal::barrett(m);
    }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    dynamic_modint() = default;
    template <std::integral T>
    dynamic_modint(T v) {
        std::int64_t x = (std::int64_t)(v % (std::int64_t)(mod()));
        if (x < 0) x += mod();
        _v = (unsigned int)(x);
    }
    template <std::unsigned_integral T>
    dynamic_modint(T v) {
        _v = (unsigned int)(v % mod());
    }

  private:
    static internal::barrett bt;
};
template <int id>
internal::barrett dynamic_modint<id>::bt(998244353);

using modint998 = static_modint<998244353>;
using modint107 = static_modint<1000000007>;
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
