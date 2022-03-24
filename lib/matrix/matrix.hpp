#include "template/template.hpp"

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

    const std::vector<T> &operator[](int i) const {
        assert(0 <= i && i < this->v.size());
        return this->v[i];
    }
    std::vector<T> &operator[](int i) {
        assert(0 <= i && i < this->v.size());
        return this->v[i];
    }

    Matrix &operator+=(const Matrix &rhs) {
        assert(this->v.size() == rhs.v.size());
        assert(this->v[0].size() == rhs.v[0].size());
        for (int i = 0; i < this->v.size(); ++i) {
            for (int j = 0; j < this->v[0].size(); ++j) this->v[i][j] += rhs.v[i][j];
        }
        return *this;
    }
    Matrix &operator-=(const Matrix &rhs) {
        assert(this->v.size() == rhs.v.size());
        assert(this->v[0].size() == rhs.v[0].size());
        for (int i = 0; i < this->v.size(); ++i) {
            for (int j = 0; j < this->v[0].size(); ++j) this->v[i][j] -= rhs.v[i][j];
        }
        return *this;
    }
    Matrix &operator*=(const Matrix &rhs) {
        assert(this->v[0].size() == rhs.v.size());
        int x = this->v.size(), y = rhs.v[0].size(), z = rhs.v.size();
        std::vector<std::vector<T>> tmp(x, std::vector<T>(y));
        for (int i = 0; i < x; ++i) {
            for (int k = 0; k < z; ++k) {
                for (int j = 0; j < y; ++j) tmp[i][j] += this->v[i][k] * rhs.v[k][j];
            }
        }
        swap(this->v, tmp);
        return *this;
    }

    Matrix operator-() const {
        std::vector<std::vector<T>> tmp = v;
        for (auto &i : tmp)
            for (auto &j : i) j = -j;
        return Matrix(tmp);
    }

    Matrix operator+(const Matrix &rhs) const { return Matrix(*this) += rhs; }
    Matrix operator-(const Matrix &rhs) const { return Matrix(*this) -= rhs; }
    Matrix operator*(const Matrix &rhs) const { return Matrix(*this) *= rhs; }

    std::vector<T> operator*(const std::vector<T> &rhs) {
        assert(this->v[0].size() == rhs.size());
        int x = this->v.size(), y = this->v[0].size();
        std::vector<T> res(x);
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) res[i] += this->v[i][j] * rhs[j];
        }
        return res;
    }

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
        assert(this->v.size() == this->v[0].size());
        int n = this->v.size();
        for (int i = 0; i < n; ++i) {
            this->v[i].assign(n, T(0));
            this->v[i][i] = T(1);
        }
    }

    Matrix transposed() const {
        int x = this->v[0].size(), y = this->v.size();
        std::vector<std::vector<T>> res(x, std::vector<T>(y));
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < y; ++j) { res[i][j] = v[j][i]; }
        }
        return Matrix(res);
    }

    void print_debug() const {
        for (auto i : v) {
            cerr << "[";
            for (auto j : i) cerr << j << ", ";
            cerr << "]" << endl;
        }
    }

  private:
    std::vector<std::vector<T>> v;
};