#pragma once
#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

/**
 * @brief 行列ライブラリ
 *
 * @tparam T 要素の型
 */
template <class T>
struct Matrix {
    Matrix() = default;
    Matrix(int x) : v(x, std::vector<T>(x)) {}
    Matrix(int x, int y) : v(x, std::vector<T>(y)) {}
    Matrix(const std::vector<std::vector<T>> &_v) : v(_v) {}

    const auto &operator[](int i) const { return v[i]; }
    auto &operator[](int i) { return v[i]; }
    const auto begin() const { return v.begin(); }
    auto begin() { return v.begin(); }
    const auto end() const { return v.end(); }
    auto end() { return v.end(); }

    Matrix &operator+=(const Matrix &rhs) {
        assert(v.size() == rhs.v.size());
        assert(v[0].size() == rhs.v[0].size());
        for (int i = 0; i < (int)v.size(); ++i) {
            for (int j = 0; j < (int)v[0].size(); ++j) v[i][j] += rhs.v[i][j];
        }
        return *this;
    }
    Matrix &operator-=(const Matrix &rhs) {
        assert(v.size() == rhs.v.size());
        assert(v[0].size() == rhs.v[0].size());
        for (int i = 0; i < (int)v.size(); ++i) {
            for (int j = 0; j < (int)v[0].size(); ++j) v[i][j] -= rhs.v[i][j];
        }
        return *this;
    }
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

    Matrix operator-() const {
        std::vector<std::vector<T>> tmp(v);
        for (auto &v : tmp)
            for (auto &x : v) x = -x;
        return Matrix(tmp);
    }

    Matrix operator+(const Matrix &rhs) const { return Matrix(*this) += rhs; }
    Matrix operator-(const Matrix &rhs) const { return Matrix(*this) -= rhs; }
    Matrix operator*(const Matrix &rhs) const { return Matrix(*this) *= rhs; }

    std::vector<T> operator*(const std::vector<T> &rhs) {
        assert(v[0].size() == rhs.size());
        int x = v.size(), y = v[0].size();
        std::vector<T> res(x);
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) res[i] += v[i][j] * rhs[j];
        }
        return res;
    }

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

    void unit_matrix() {
        assert(v.size() == v[0].size());
        int n = v.size();
        for (int i = 0; i < n; ++i) {
            v[i].assign(n, T(0));
            v[i][i] = T(1);
        }
    }

    Matrix transposed() const {
        int x = v[0].size(), y = v.size();
        std::vector<std::vector<T>> res(x, std::vector<T>(y));
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) { res[i][j] = v[j][i]; }
        }
        return Matrix(res);
    }

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
