#pragma once
#include <cstdint>
#include <iostream>
#include <utility>

/// @brief 法 $2^{61}-1$ 上の整数型
/// @details ローリングハッシュ向けに、加減乗除・比較・累乗・逆元を提供する。
/// @complexity 加減乗算と比較は $O(1)$、`pow(n)` は $O(\log n)$、
/// `inv()` は $O(\log mod)$
struct HashInt {
    /// @brief 法 $2^{61}-1$ を返す
    /// @complexity $O(1)$
    static constexpr std::uint64_t get_mod() noexcept { return mod; }

    /// @brief 0 で初期化する
    /// @complexity $O(1)$
    constexpr HashInt() noexcept : x(0) {}
    /// @brief 整数 `y` を法で正規化して初期化する
    /// @complexity $O(1)$
    constexpr HashInt(int y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}
    /// @brief 整数 `y` を法で正規化して初期化する
    /// @complexity $O(1)$
    constexpr HashInt(unsigned int y) noexcept : x(y % mod) {}
    /// @brief 整数 `y` を法で正規化して初期化する
    /// @complexity $O(1)$
    constexpr HashInt(long y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}
    /// @brief 整数 `y` を法で正規化して初期化する
    /// @complexity $O(1)$
    constexpr HashInt(unsigned long y) noexcept : x(y % mod) {}
    /// @brief 整数 `y` を法で正規化して初期化する
    /// @complexity $O(1)$
    constexpr HashInt(long long y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}
    /// @brief 整数 `y` を法で正規化して初期化する
    /// @complexity $O(1)$
    constexpr HashInt(unsigned long long y) noexcept : x(y % mod) {}

    /// @brief `rhs` を加算する
    /// @complexity $O(1)$
    constexpr HashInt &operator+=(const HashInt &rhs) noexcept {
        if ((x += rhs.x) >= mod) x -= mod;
        return *this;
    }
    /// @brief `rhs` を減算する
    /// @complexity $O(1)$
    constexpr HashInt &operator-=(const HashInt &rhs) noexcept {
        if ((x += mod - rhs.x) >= mod) x -= mod;
        return *this;
    }
    /// @brief `rhs` を乗算する
    /// @complexity $O(1)$
    constexpr HashInt &operator*=(const HashInt &rhs) noexcept {
        std::uint64_t au = x >> 31, ad = x & mask31;
        std::uint64_t bu = rhs.x >> 31, bd = rhs.x & mask31;
        std::uint64_t mid = ad * bu + au * bd;
        std::uint64_t midu = mid >> 30, midd = mid & mask30;
        x = _mod(au * bu * 2 + midu + (midd << 31) + ad * bd);
        return *this;
    }
    /// @brief `rhs` で除算する
    /// @complexity $O(\log mod)$
    constexpr HashInt &operator/=(const HashInt &rhs) noexcept {
        *this *= rhs.inv();
        return *this;
    }

    /// @brief 1 を加算して自身を返す
    /// @complexity $O(1)$
    constexpr HashInt &operator++() noexcept {
        if ((++x) >= mod) x -= mod;
        return *this;
    }
    /// @brief 1 を加算する前の値を返す
    /// @complexity $O(1)$
    constexpr HashInt operator++(int) noexcept {
        HashInt tmp(*this);
        operator++();
        return tmp;
    }
    /// @brief 1 を減算して自身を返す
    /// @complexity $O(1)$
    constexpr HashInt &operator--() noexcept {
        if ((x += mod - 1) >= mod) x -= mod;
        return *this;
    }
    /// @brief 1 を減算する前の値を返す
    /// @complexity $O(1)$
    constexpr HashInt operator--(int) noexcept {
        HashInt tmp(*this);
        operator--();
        return tmp;
    }

    /// @brief 加法逆元を返す
    /// @complexity $O(1)$
    constexpr HashInt operator-() const noexcept { return HashInt(-x); }
    /// @brief `rhs` との和を返す
    /// @complexity $O(1)$
    constexpr HashInt operator+(const HashInt &rhs) const noexcept { return HashInt(*this) += rhs; }
    /// @brief `rhs` との差を返す
    /// @complexity $O(1)$
    constexpr HashInt operator-(const HashInt &rhs) const noexcept { return HashInt(*this) -= rhs; }
    /// @brief `rhs` との積を返す
    /// @complexity $O(1)$
    constexpr HashInt operator*(const HashInt &rhs) const noexcept { return HashInt(*this) *= rhs; }
    /// @brief `rhs` との商を返す
    /// @complexity $O(\log mod)$
    constexpr HashInt operator/(const HashInt &rhs) const noexcept { return HashInt(*this) /= rhs; }

    /// @brief `rhs` と等しいなら true を返す
    /// @complexity $O(1)$
    constexpr bool operator==(const HashInt &rhs) const noexcept { return x == rhs.x; }
    /// @brief `rhs` と異なるなら true を返す
    /// @complexity $O(1)$
    constexpr bool operator!=(const HashInt &rhs) const noexcept { return x != rhs.x; }

    /// @brief 正規化済みの値を `long` へ変換する
    /// @complexity $O(1)$
    constexpr explicit operator long() const noexcept { return x; }
    /// @brief 正規化済みの値を `unsigned long` へ変換する
    /// @complexity $O(1)$
    constexpr explicit operator unsigned long() const noexcept { return x; }
    /// @brief 正規化済みの値を `long long` へ変換する
    /// @complexity $O(1)$
    constexpr explicit operator long long() const noexcept { return x; }
    /// @brief 正規化済みの値を `unsigned long long` へ変換する
    /// @complexity $O(1)$
    constexpr explicit operator unsigned long long() const noexcept { return x; }

    /// @brief 入力ストリームから整数を読み込む
    /// @complexity $O(1)$
    friend std::istream &operator>>(std::istream &is, HashInt &rhs) {
        std::int64_t t;
        is >> t;
        rhs = HashInt(t);
        return is;
    }
    /// @brief 正規化済みの値を出力ストリームへ書き込む
    /// @complexity $O(1)$
    friend std::ostream &operator<<(std::ostream &os, const HashInt &rhs) { return os << rhs.x; }

    /// @brief 乗法逆元を返す
    /// @complexity $O(\log mod)$
    constexpr HashInt inv() const noexcept {
        std::int64_t a = x, b = mod, u = 1, v = 0, t = 0, tmp = 0;
        while (b > 0) {
            t = a / b;
            tmp = a - t * b, a = b, b = tmp;  // std::swap(a -= t * b, b);
            tmp = u - t * v, u = v, v = tmp;  // std::swap(u -= t * v, v);
        }
        return HashInt(u);
    }

    /// @brief 自身の `n` 乗を返す
    /// @complexity $O(\log n)$
    constexpr HashInt pow(std::uint64_t n) const noexcept { return HashInt(*this).pow_self(n); }
    /// @brief 自身を `n` 乗へ更新して返す
    /// @complexity $O(\log n)$
    constexpr HashInt &pow_self(std::uint64_t n) noexcept {
        HashInt res(1);
        for (; n > 0; n >>= 1) {
            if (n & 1) res *= *this;
            *this *= *this;
        }
        *this = res;
        return *this;
    }

    /// @brief $[0,2^{61}-1)$ に正規化された内部値を返す
    /// @complexity $O(1)$
    constexpr std::uint64_t val() const noexcept { return x; }

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
