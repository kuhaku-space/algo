#pragma once
#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

/// @brief 行列の四則演算・行列式・累乗・転置
/// @tparam T 要素の型
/// @complexity $r\times c$ 行列の加減算・転置は $O(rc)$、行列積は
/// $O(rck)$。$n\times n$ 行列の行列式は $O(n^3)$、k乗は $O(n^3\log k)$
template <class T>
struct Matrix {
    /// @brief 空の行列を作る
    /// @complexity $O(1)$
    Matrix() = default;
    /// @brief `x` 行 `x` 列の零行列を作る
    /// @complexity $O(x^2)$
    Matrix(int x) : v(x, std::vector<T>(x)) {}
    /// @brief `x` 行 `y` 列の零行列を作る
    /// @complexity $O(xy)$
    Matrix(int x, int y) : v(x, std::vector<T>(y)) {}
    /// @brief 二次元配列 `_v` をコピーして行列を作る
    /// @complexity $O(rc)$
    Matrix(const std::vector<std::vector<T>> &_v) : v(_v) {}

    /// @brief `i` 行目を読み取り専用で返す
    /// @complexity $O(1)$
    const auto &operator[](int i) const { return v[i]; }
    /// @brief `i` 行目を返す
    /// @complexity $O(1)$
    auto &operator[](int i) { return v[i]; }
    /// @brief 先頭行を指す読み取り専用イテレータを返す
    /// @complexity $O(1)$
    const auto begin() const { return v.begin(); }
    /// @brief 先頭行を指すイテレータを返す
    /// @complexity $O(1)$
    auto begin() { return v.begin(); }
    /// @brief 行列の終端を指す読み取り専用イテレータを返す
    /// @complexity $O(1)$
    const auto end() const { return v.end(); }
    /// @brief 行列の終端を指すイテレータを返す
    /// @complexity $O(1)$
    auto end() { return v.end(); }

    /// @brief 同じ大きさの行列 `rhs` を要素ごとに加算する
    /// @complexity $O(rc)$
    Matrix &operator+=(const Matrix &rhs) {
        assert(v.size() == rhs.v.size());
        assert(v[0].size() == rhs.v[0].size());
        for (int i = 0; i < (int)v.size(); ++i) {
            for (int j = 0; j < (int)v[0].size(); ++j) v[i][j] += rhs.v[i][j];
        }
        return *this;
    }
    /// @brief 同じ大きさの行列 `rhs` を要素ごとに減算する
    /// @complexity $O(rc)$
    Matrix &operator-=(const Matrix &rhs) {
        assert(v.size() == rhs.v.size());
        assert(v[0].size() == rhs.v[0].size());
        for (int i = 0; i < (int)v.size(); ++i) {
            for (int j = 0; j < (int)v[0].size(); ++j) v[i][j] -= rhs.v[i][j];
        }
        return *this;
    }
    /// @brief 行列 `rhs` を右から乗算する
    /// @complexity 左辺を $r\times k$、右辺を $k\times c$ として $O(rkc)$
    Matrix &operator*=(const Matrix &rhs) {
        assert(v[0].size() == rhs.v.size());
        int x = v.size(), y = rhs.v[0].size(), z = rhs.v.size();
        std::vector<std::vector<T>> tmp(x, std::vector<T>(y));
        for (int i = 0; i < x; ++i) {
            for (int k = 0; k < z; ++k) {
                for (int j = 0; j < y; ++j) tmp[i][j] += v[i][k] * rhs.v[k][j];
            }
        }
        std::swap(v, tmp);
        return *this;
    }

    /// @brief 全要素の符号を反転した行列を返す
    /// @complexity $O(rc)$
    Matrix operator-() const {
        std::vector<std::vector<T>> tmp(v);
        for (auto &v : tmp)
            for (auto &x : v) x = -x;
        return Matrix(tmp);
    }

    /// @brief 行列和を返す
    /// @complexity $O(rc)$
    Matrix operator+(const Matrix &rhs) const { return Matrix(*this) += rhs; }
    /// @brief 行列差を返す
    /// @complexity $O(rc)$
    Matrix operator-(const Matrix &rhs) const { return Matrix(*this) -= rhs; }
    /// @brief 行列積を返す
    /// @complexity 左辺を $r\times k$、右辺を $k\times c$ として $O(rkc)$
    Matrix operator*(const Matrix &rhs) const { return Matrix(*this) *= rhs; }

    /// @brief 列ベクトル `rhs` を右から掛けた結果を返す
    /// @complexity $O(rc)$
    std::vector<T> operator*(const std::vector<T> &rhs) {
        assert(v[0].size() == rhs.size());
        int x = v.size(), y = v[0].size();
        std::vector<T> res(x);
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) res[i] += v[i][j] * rhs[j];
        }
        return res;
    }

    /// @brief 正方行列の行列式を返す
    /// @complexity $O(n^3)$
    T det() const {
        assert(v.size() == v[0].size());
        std::vector<std::vector<T>> u(v);
        int n = u.size();
        T ans = 1;
        for (int i = 0; i < n; ++i) {
            if (u[i][i] == T(0)) {
                for (int j = i + 1; j < n; ++j) {
                    if (u[j][i] != T(0)) {
                        std::swap(u[j], u[i]);
                        ans *= -1;
                        break;
                    }
                }
                if (u[i][i] == T(0)) return T(0);
            }
            ans *= u[i][i];
            T t = T(1) / u[i][i];
            for (int j = i; j < n; ++j) u[i][j] *= t;
            for (int k = i + 1; k < n; ++k) {
                if (u[k][i] == T(0)) continue;
                ans *= u[k][i];
                t = T(1) / u[k][i];
                for (int j = i; j < n; ++j) u[k][j] = u[k][j] * t - u[i][j];
            }
        }
        return ans;
    }

    /// @brief 正方行列の `k` 乗を返す
    /// @complexity $O(n^3\log k)$
    Matrix pow(std::int64_t k) const {
        assert(v.size() == v[0].size());
        int n = v.size();
        Matrix res(n, n), mul(v);
        res.unit_matrix();
        for (; k > 0; k >>= 1) {
            if (k & 1) res *= mul;
            mul *= mul;
        }
        return res;
    }

    /// @brief 正方行列を単位行列に変更する
    /// @complexity $O(n^2)$
    void unit_matrix() {
        assert(v.size() == v[0].size());
        int n = v.size();
        for (int i = 0; i < n; ++i) {
            v[i].assign(n, T(0));
            v[i][i] = T(1);
        }
    }

    /// @brief 転置行列を返す
    /// @complexity $O(rc)$
    Matrix transposed() const {
        int x = v[0].size(), y = v.size();
        std::vector<std::vector<T>> res(x, std::vector<T>(y));
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) { res[i][j] = v[j][i]; }
        }
        return Matrix(res);
    }

    /// @brief 行列の全要素を標準エラー出力へ表示する
    /// @complexity $O(rc)$
    void print_debug() const {
        for (auto u : v) {
            std::cerr << "[";
            for (auto x : u) std::cerr << x << ", ";
            std::cerr << "]\n";
        }
    }

  private:
    std::vector<std::vector<T>> v;
};
