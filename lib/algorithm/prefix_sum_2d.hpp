#pragma once
#include <cassert>
#include <cstdint>
#include <vector>

/// @brief 二次元累積和
/// @tparam T 値の型
/// @tparam RangeAdd true なら矩形加算（差分配列）、false なら点更新として構築する。
template <class T = std::int64_t, bool RangeAdd = false>
struct PrefixSum2D {
    /// @brief 空の二次元累積和を構築する
    /// @complexity $O(1)$
    PrefixSum2D() : PrefixSum2D(0, 0) {}

    /// @brief n行m列の0初期化された表を構築する
    /// @complexity $O(nm)$
    PrefixSum2D(int _n, int _m) : n(_n), m(_m), data(_n + 1, std::vector<T>(_m + 1)) {}

    /// @brief 二次元配列から累積和を構築する
    /// @complexity 行数を $n$、列数を $m$ として $O(nm)$
    template <class U>
    PrefixSum2D(const std::vector<std::vector<U>> &v)
        : n(v.size()), m(n == 0 ? 0 : v[0].size()), data(n + 1, std::vector<T>(m + 1)) {
        for (int i = 0; i < n; ++i) {
            assert(int(v[i].size()) == m);
            for (int j = 0; j < m; ++j) data[i][j] = v[i][j];
        }
        build_suffix();
    }

    /// @brief v[x][y] = val（build 前のみ有効）
    /// @complexity $O(1)$
    void set(int x, int y, T val)
    requires(!RangeAdd)
    {
        data[x][y] = val;
    }
    /// @brief v[x][y] += val（build 前のみ有効）
    /// @complexity $O(1)$
    void add(int x, int y, T val) {
        if constexpr (RangeAdd) add(x, y, x + 1, y + 1, val);
        else data[x][y] += val;
    }
    /// @brief 半開矩形 $[x_1,x_2)\times[y_1,y_2)$ へ val を加算する（build 前のみ有効）
    /// @complexity $O(1)$
    void add(int x1, int y1, int x2, int y2, T val)
    requires RangeAdd
    {
        assert(0 <= x1 && x1 <= x2 && x2 <= n && 0 <= y1 && y1 <= y2 && y2 <= m);
        data[x1][y1] += val, data[x1][y2] -= val;
        data[x2][y1] -= val, data[x2][y2] += val;
    }

    /// @brief build前の値から二次元累積和を構築する
    /// @complexity $O(nm)$
    void build() {
        if constexpr (RangeAdd) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j <= m; ++j) data[i + 1][j] += data[i][j];
            }
            for (int i = 0; i <= n; ++i) {
                for (int j = 0; j < m; ++j) data[i][j + 1] += data[i][j];
            }
        }
        build_suffix();
    }

    /// @brief v[x][y]を返す
    /// @complexity $O(1)$
    T get(int x, int y) const {
        assert(0 <= x && x < n && 0 <= y && y < m);
        return sum(x, y, x + 1, y + 1);
    }

    /// @brief 接頭辞矩形 $[0,x)\times[0,y)$ の総和を返す
    /// @complexity $O(1)$
    T sum(int x, int y) const { return sum(0, 0, x, y); }

    /// @brief 半開矩形 $[x_1,x_2)\times[y_1,y_2)$ の総和を返す
    /// @complexity $O(1)$
    T sum(int x1, int y1, int x2, int y2) const {
        assert(0 <= x1 && x1 <= x2 && x2 <= n && 0 <= y1 && y1 <= y2 && y2 <= m);
        return data[x1][y1] - data[x1][y2] - data[x2][y1] + data[x2][y2];
    }

  private:
    int n = 0, m = 0;
    std::vector<std::vector<T>> data;

    // 値が入った data を、右下からの suffix 和の表に変える。
    void build_suffix() {
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) data[i][j] += data[i][j + 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) data[i][j] += data[i + 1][j];
        }
    }
};
