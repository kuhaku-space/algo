#pragma once
#include <compare>
#include <concepts>
#include <cstdint>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include "internal/internal_type_traits.hpp"

/// 「整数っぽい」型: 四則演算・剰余・単項 -・全順序を持ち 0/1 を直接初期化できる。
/// std::int64_t・__int128・BigInt 等、Fraction の T として使える型を表す。
template <class T>
concept integer_like = std::regular<T> && std::totally_ordered<T> && requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
    { a - b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
    { a / b } -> std::convertible_to<T>;
    { a % b } -> std::convertible_to<T>;
    { -a } -> std::convertible_to<T>;
    T(0);
    T(1);
};

/// @brief 分数ライブラリ
/// @tparam T 分子・分母を保持する整数型（既定は std::int64_t）。integer_like を満たせば
///           BigInt など任意精度型も指定できる。
template <integer_like T = std::int64_t>
struct Fraction : internal::field_base {
    Fraction() : x(T(0)), y(T(1)) {}
    Fraction(T _x, T _y = T(1)) : x(_x), y(_y) { reduce(); }

    Fraction &operator+=(const Fraction &rhs) {
        x = x * rhs.y + y * rhs.x;
        y *= rhs.y;
        reduce();
        return *this;
    }
    Fraction &operator-=(const Fraction &rhs) {
        x = x * rhs.y - y * rhs.x;
        y *= rhs.y;
        reduce();
        return *this;
    }
    Fraction &operator*=(const Fraction &rhs) {
        x *= rhs.x, y *= rhs.y;
        reduce();
        return *this;
    }
    Fraction &operator/=(const Fraction &rhs) {
        x *= rhs.y, y *= rhs.x;
        reduce();
        return *this;
    }

    Fraction &operator++() {
        x += y;
        return *this;
    }
    Fraction operator++(int) {
        Fraction tmp(*this);
        operator++();
        return tmp;
    }
    Fraction &operator--() {
        x -= y;
        return *this;
    }
    Fraction operator--(int) {
        Fraction tmp(*this);
        operator--();
        return tmp;
    }

    Fraction operator-() const { return Fraction(-x, y); }

    Fraction operator+(const Fraction &rhs) const { return Fraction(*this) += rhs; }
    Fraction operator-(const Fraction &rhs) const { return Fraction(*this) -= rhs; }
    Fraction operator*(const Fraction &rhs) const { return Fraction(*this) *= rhs; }
    Fraction operator/(const Fraction &rhs) const { return Fraction(*this) /= rhs; }

    bool operator==(const Fraction &rhs) const { return x == rhs.x && y == rhs.y; }
    std::strong_ordering operator<=>(const Fraction &rhs) const { return x * rhs.y <=> rhs.x * y; }

    friend std::ostream &operator<<(std::ostream &os, const Fraction &rhs) { return os << rhs.to_double(); }

    friend std::istream &operator>>(std::istream &is, Fraction &a) {
        std::string s;
        is >> s;
        bool neg = false;
        std::string digits;
        int frac_len = 0;
        bool f = false;
        for (auto c : s) {
            if (c == '-') {
                neg = true;
                continue;
            }
            if (c == '.') {
                f = true;
                continue;
            }
            digits.push_back(c);
            if (f) ++frac_len;
        }
        if (digits.empty()) digits.push_back('0');

        T x;
        if constexpr (std::is_constructible_v<T, const std::string &>) {
            // BigInt 等、文字列から直接組み立てられる型はそちらを使う。
            // 1 桁ずつ x *= 10 する実装だと、乗算のたびに畳み込みベースの乗算が走り
            // 桁数に対して大幅に重くなる（BigInt の乗算に小さい数専用の高速パスが無いため）。
            x = T(digits);
        } else {
            x = T(0);
            for (auto c : digits) x = x * T(10) + T(c - '0');
        }
        if (neg) x = -x;

        T y;
        if constexpr (std::is_constructible_v<T, const std::string &>) {
            y = T("1" + std::string(frac_len, '0'));
        } else {
            y = T(1);
            for (int i = 0; i < frac_len; ++i) y *= T(10);
        }
        a = Fraction(x, y);
        return is;
    }

    double to_double() const { return (double)x / (double)y; }

  private:
    T x, y;

    // Euclid の互除法。std::gcd は標準整数型限定で BigInt を受け付けないため自前で持つ。
    static T gcd(T a, T b) {
        if (a < T(0)) a = -a;
        if (b < T(0)) b = -b;
        while (b != T(0)) {
            T t = a % b;
            a = b;
            b = t;
        }
        return a;
    }

    // 既約分数へ正規化する: gcd(|x|, |y|) = 1 かつ y > 0（x == 0 のときは y = 1）
    void reduce() {
        if (x == T(0)) {
            y = T(1);
            return;
        }
        T g = gcd(x, y);
        x /= g, y /= g;
        if (y < T(0)) x *= T(-1), y *= T(-1);
    }
};
