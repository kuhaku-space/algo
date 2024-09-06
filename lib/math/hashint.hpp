#pragma once
#include <cstdint>
#include <iostream>
#include <utility>

struct HashInt {
    static constexpr std::uint64_t get_mod() noexcept { return mod; }

    constexpr HashInt() noexcept : x(0) {}
    constexpr HashInt(int y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}
    constexpr HashInt(unsigned int y) noexcept : x(y % mod) {}
    constexpr HashInt(long y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}
    constexpr HashInt(unsigned long y) noexcept : x(y % mod) {}
    constexpr HashInt(long long y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}
    constexpr HashInt(unsigned long long y) noexcept : x(y % mod) {}

    constexpr HashInt &operator+=(const HashInt &rhs) noexcept {
        if ((x += rhs.x) >= mod) x -= mod;
        return *this;
    }
    constexpr HashInt &operator-=(const HashInt &rhs) noexcept {
        if ((x += mod - rhs.x) >= mod) x -= mod;
        return *this;
    }
    constexpr HashInt &operator*=(const HashInt &rhs) noexcept {
        std::uint64_t au = x >> 31, ad = x & mask31;
        std::uint64_t bu = rhs.x >> 31, bd = rhs.x & mask31;
        std::uint64_t mid = ad * bu + au * bd;
        std::uint64_t midu = mid >> 30, midd = mid & mask30;
        x = _mod(au * bu * 2 + midu + (midd << 31) + ad * bd);
        return *this;
    }
    constexpr HashInt &operator/=(const HashInt &rhs) noexcept {
        *this *= rhs.inverse();
        return *this;
    }

    constexpr HashInt &operator++() noexcept {
        if ((++x) >= mod) x -= mod;
        return *this;
    }
    constexpr HashInt operator++(int) noexcept {
        HashInt tmp(*this);
        operator++();
        return tmp;
    }
    constexpr HashInt &operator--() noexcept {
        if ((x += mod - 1) >= mod) x -= mod;
        return *this;
    }
    constexpr HashInt operator--(int) noexcept {
        HashInt tmp(*this);
        operator--();
        return tmp;
    }

    constexpr HashInt operator-() const noexcept { return HashInt(-x); }
    constexpr HashInt operator+(const HashInt &rhs) const noexcept { return HashInt(*this) += rhs; }
    constexpr HashInt operator-(const HashInt &rhs) const noexcept { return HashInt(*this) -= rhs; }
    constexpr HashInt operator*(const HashInt &rhs) const noexcept { return HashInt(*this) *= rhs; }
    constexpr HashInt operator/(const HashInt &rhs) const noexcept { return HashInt(*this) /= rhs; }

    constexpr bool operator==(const HashInt &rhs) const noexcept { return x == rhs.x; }
    constexpr bool operator!=(const HashInt &rhs) const noexcept { return x != rhs.x; }

    constexpr explicit operator long() const noexcept { return x; }
    constexpr explicit operator unsigned long() const noexcept { return x; }
    constexpr explicit operator long long() const noexcept { return x; }
    constexpr explicit operator unsigned long long() const noexcept { return x; }

    friend std::istream &operator>>(std::istream &is, HashInt &rhs) {
        std::int64_t t;
        is >> t;
        rhs = HashInt(t);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const HashInt &rhs) { return os << rhs.x; }

    constexpr HashInt inverse() const noexcept {
        std::int64_t a = x, b = mod, u = 1, v = 0, t = 0, tmp = 0;
        while (b > 0) {
            t = a / b;
            tmp = a - t * b, a = b, b = tmp;  // std::swap(a -= t * b, b);
            tmp = u - t * v, u = v, v = tmp;  // std::swap(u -= t * v, v);
        }
        return HashInt(u);
    }

    constexpr HashInt pow(std::uint64_t n) const noexcept { return HashInt(*this).pow_self(n); }
    constexpr HashInt &pow_self(std::uint64_t n) noexcept {
        HashInt res(1);
        for (; n > 0; n >>= 1) {
            if (n & 1) res *= *this;
            *this *= *this;
        }
        *this = res;
        return *this;
    }

  private:
    std::uint64_t x;

    static constexpr std::uint64_t mod = (1ul << 61) - 1;
    static constexpr std::uint64_t mask30 = (1ul << 30) - 1;
    static constexpr std::uint64_t mask31 = (1ul << 31) - 1;

    constexpr std::uint64_t _mod(std::uint64_t x) const {
        std::uint64_t xu = x >> 61, xd = x & mod;
        std::uint64_t res = xu + xd;
        if (res >= mod) res -= mod;
        return res;
    }
};
