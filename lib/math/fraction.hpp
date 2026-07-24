#pragma once
#include <compare>
#include <concepts>
#include <cstdint>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include "internal/internal_type_traits.hpp"

/// @brief Fraction の要素型に必要な整数演算を表す concept
/// @details 四則演算・剰余・単項 -・全順序を持ち、0/1 を直接初期化できる型。
///          std::int64_t・__int128・BigInt などが該当する。
/// @complexity コンパイル時制約で実行時計算量はない
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
    /// @brief 0を構築する
    /// @complexity $T$ の構築 $O(1)$ 回分
    Fraction() : x(T(0)), y(T(1)) {}

    /// @brief 分子 _x、分母 _y の既約分数を構築する
    /// @complexity $M=\max(|_x|,|_y|)$ として、$T$ 上の Euclid 法 $O(\log M)$ 反復
    Fraction(T _x, T _y = T(1)) : x(_x), y(_y) { reduce(); }

    /// @brief rhsを加算して既約化する
    /// @complexity 値の大きさを $M$ として、$T$ 上の Euclid 法 $O(\log M)$ 反復
    Fraction &operator+=(const Fraction &rhs) {
        x = x * rhs.y + y * rhs.x;
        y *= rhs.y;
        reduce();
        return *this;
    }

    /// @brief rhsを減算して既約化する
    /// @complexity 値の大きさを $M$ として、$T$ 上の Euclid 法 $O(\log M)$ 反復
    Fraction &operator-=(const Fraction &rhs) {
        x = x * rhs.y - y * rhs.x;
        y *= rhs.y;
        reduce();
        return *this;
    }

    /// @brief rhsを乗算して既約化する
    /// @complexity 値の大きさを $M$ として、$T$ 上の Euclid 法 $O(\log M)$ 反復
    Fraction &operator*=(const Fraction &rhs) {
        x *= rhs.x, y *= rhs.y;
        reduce();
        return *this;
    }

    /// @brief rhsで除算して既約化する
    /// @complexity 値の大きさを $M$ として、$T$ 上の Euclid 法 $O(\log M)$ 反復
    Fraction &operator/=(const Fraction &rhs) {
        x *= rhs.y, y *= rhs.x;
        reduce();
        return *this;
    }

    /// @brief 1を加算する
    /// @complexity $T$ の加算 $O(1)$ 回分
    Fraction &operator++() {
        x += y;
        return *this;
    }

    /// @brief 1を加算する前の値を返す
    /// @complexity $T$ のコピーと加算 $O(1)$ 回分
    Fraction operator++(int) {
        Fraction tmp(*this);
        operator++();
        return tmp;
    }

    /// @brief 1を減算する
    /// @complexity $T$ の減算 $O(1)$ 回分
    Fraction &operator--() {
        x -= y;
        return *this;
    }

    /// @brief 1を減算する前の値を返す
    /// @complexity $T$ のコピーと減算 $O(1)$ 回分
    Fraction operator--(int) {
        Fraction tmp(*this);
        operator--();
        return tmp;
    }

    /// @brief 符号を反転した値を返す
    /// @complexity 値の大きさを $M$ として、$T$ 上の Euclid 法 $O(\log M)$ 反復
    Fraction operator-() const { return Fraction(-x, y); }

    /// @brief rhsとの和を返す
    /// @complexity 値の大きさを $M$ として、$T$ 上の Euclid 法 $O(\log M)$ 反復
    Fraction operator+(const Fraction &rhs) const { return Fraction(*this) += rhs; }

    /// @brief rhsとの差を返す
    /// @complexity 値の大きさを $M$ として、$T$ 上の Euclid 法 $O(\log M)$ 反復
    Fraction operator-(const Fraction &rhs) const { return Fraction(*this) -= rhs; }

    /// @brief rhsとの積を返す
    /// @complexity 値の大きさを $M$ として、$T$ 上の Euclid 法 $O(\log M)$ 反復
    Fraction operator*(const Fraction &rhs) const { return Fraction(*this) *= rhs; }

    /// @brief rhsによる商を返す
    /// @complexity 値の大きさを $M$ として、$T$ 上の Euclid 法 $O(\log M)$ 反復
    Fraction operator/(const Fraction &rhs) const { return Fraction(*this) /= rhs; }

    /// @brief 同じ分数か返す
    /// @complexity $T$ の比較 $O(1)$ 回分
    bool operator==(const Fraction &rhs) const { return x == rhs.x && y == rhs.y; }

    /// @brief 大小を比較する
    /// @complexity $T$ の乗算 $O(1)$ 回分
    std::strong_ordering operator<=>(const Fraction &rhs) const { return x * rhs.y <=> rhs.x * y; }

    /// @brief 浮動小数点数として出力する
    /// @complexity $T$ から double への変換 $O(1)$ 回分
    friend std::ostream &operator<<(std::ostream &os, const Fraction &rhs) { return os << rhs.to_double(); }

    /// @brief 10進小数を厳密な分数として入力する
    /// @complexity 入力長を $n$ として $O(n)$ と、$T$ 上の既約化1回分
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

    /// @brief doubleへ変換する
    /// @complexity $T$ から double への変換 $O(1)$ 回分
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
