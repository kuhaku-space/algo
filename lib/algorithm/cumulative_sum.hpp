#pragma once
#include <cassert>
#include <vector>

/// @brief 二次元累積和
template <class T>
struct cumulative_sum_2d {
    cumulative_sum_2d(int _n, int _m) : v(_n, std::vector<T>(_m)), n(_n), m(_m) {}
    cumulative_sum_2d(const std::vector<std::vector<T>> &_v) : v(_v) { build(); }

    void set(int x, int y, T val) { v[x][y] = val; }
    void add(int x, int y, T val) { v[x][y] += val; }

    void build() {
        n = v.size();
        assert(n > 0);
        m = v[0].size();
        assert(m > 0);
        v.resize(n + 1);
        for (int i = 0; i <= n; ++i) v[i].resize(m + 1);
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) v[i][j] += v[i][j + 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) v[i][j] += v[i + 1][j];
        }
    }

    T get(int x1, int y1, int x2, int y2) {
        assert(0 <= x1 && x1 <= x2 && x2 <= n && 0 <= y1 && y1 <= y2 && y2 <= m);
        return v[x1][y1] - v[x1][y2] - v[x2][y1] + v[x2][y2];
    }

  private:
    std::vector<std::vector<T>> v;
    int n, m;
};
