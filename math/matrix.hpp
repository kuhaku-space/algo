#include "_base.hpp"

// 行列ライブラリ
template <class T>
struct Matrix {
    vector<vector<T>> v;

    Matrix(int64_t x) {
        v = vector<vector<T>>(x, vector<T>(x));
    }

    Matrix(int64_t x, int64_t y) {
        v = vector<vector<T>>(x, vector<T>(y));
    }

    Matrix(vector<vector<T>> _v) : v(_v) {}

    const vector<T> &operator[](const int64_t i) const {
        assert(i >= 0 && i < v.size());
        return v[i];
    }
    vector<T> &operator[](const int64_t i) {
        assert(i >= 0 && i < v.size());
        return v[i];
    }

    Matrix &operator+=(const Matrix &rhs) {
        assert(v.size() == rhs.v.size());
        assert(v[0].size() == rhs.v[0].size());
        for (int64_t i = 0; i < v.size(); ++i) {
            for (int64_t j = 0; j < v[0].size(); ++j) v[i][j] += rhs.v[i][j];
        }
        return *this;
    }

    Matrix &operator-=(const Matrix &rhs) {
        assert(v.size() == rhs.v.size());
        assert(v[0].size() == rhs.v[0].size());
        for (int64_t i = 0; i < v.size(); ++i) {
            for (int64_t j = 0; j < v[0].size(); ++j) v[i][j] -= rhs.v[i][j];
        }
        return *this;
    }

    Matrix &operator*=(const Matrix &rhs) {
        assert(v[0].size() == rhs.v.size());
        int64_t x = v.size(), y = rhs.v[0].size(), z = rhs.v.size();
        vector<vector<T>> tmp(x, vector<T>(y));
        for (int64_t i = 0; i < x; ++i) {
            for (int64_t j = 0; j < y; ++j) {
                for (int64_t k = 0; k < z; ++k)
                    tmp[i][j] += v[i][k] * rhs.v[k][j];
            }
        }
        swap(v, tmp);
        return *this;
    }

    Matrix operator-() const {
        vector<vector<T>> tmp = v;
        for (auto &i : tmp)
            for (auto &j : i) j = -j;
        return Matrix(tmp);
    }

    Matrix operator+(const Matrix &rhs) const { return Matrix(*this) += rhs; }
    Matrix operator-(const Matrix &rhs) const { return Matrix(*this) -= rhs; }
    Matrix operator*(const Matrix &rhs) const { return Matrix(*this) *= rhs; }

    Matrix pow(int64_t n) const {
        Matrix res(v), mul(v);
        res.unit_matrix();
        for (; n > 0; n >>= 1) {
            if (n & 1) res *= mul;
            mul *= mul;
        }
        return res;
    }

    void unit_matrix() {
        assert(v.size() == v[0].size());
        int64_t n = v.size();
        for (int64_t i = 0; i < n; ++i) {
            v[i].assign(n, T(0));
            v[i][i] = T(1);
        }
    }

    Matrix transposed() const {
        int64_t x = v[0].size(), y = v.size();
        vector<vector<T>> res(x, vector<T>(y));
        for (int64_t i = 0; i < x; ++i) {
            for (int64_t j = 0; j < y; ++j) {
                res[i][j] = v[j][i];
            }
        }
        return Matrix(res);
    }

    void debug_print() const {
        for (auto i : v) {
            cerr << "[";
            for (auto j : i) cerr << j << ", ";
            cerr << "]" << endl;
        }
    }
};
