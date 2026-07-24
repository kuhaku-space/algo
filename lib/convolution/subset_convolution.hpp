#pragma once
#include <algorithm>
#include <bit>
#include <vector>

/// @brief 部分集合畳み込み $c[S]=\sum_{T\subseteq S}a[T]b[S\setminus T]$ を求める
/// @param a 1つ目の集合関数
/// @param b 2つ目の集合関数
/// @return 部分集合畳み込み。入力長を含む最小の2の冪まで0で補われる
/// @complexity 出力長を $N=2^n$ として $O(n^2N)$
template <class T>
std::vector<T> subset_convolution(const std::vector<T> &a, const std::vector<T> &b) {
    int n = std::bit_ceil(std::max(a.size(), b.size()));
    int k = std::countr_zero<unsigned>(n);
    std::vector c(n, 0);
    for (int i = 0; i < n; ++i) c[i] = std::popcount((unsigned)i);
    std::vector u(n, std::vector(k + 1, T())), v(n, std::vector(k + 1, T()));
    for (int i = 0; i < (int)a.size(); ++i) u[i][c[i]] = a[i];
    for (int i = 0; i < (int)b.size(); ++i) v[i][c[i]] = b[i];
    for (int p = 1; p < n; p <<= 1) {
        for (int i = 0; i < n; ++i) {
            if ((i & p) == 0) {
                for (int j = 0; j <= k; ++j) {
                    u[i | p][j] += u[i][j];
                    v[i | p][j] += v[i][j];
                }
            }
        }
    }
    std::vector w(n, std::vector(k + 1, T()));
    for (int i = 0; i < n; ++i) {
        for (int p = 0; p <= k; ++p) {
            for (int q = 0; q <= k - p; ++q) w[i][p + q] += u[i][p] * v[i][q];
        }
    }
    for (int p = 1; p < n; p <<= 1) {
        for (int i = 0; i < n; ++i) {
            if ((i & p) == 0) {
                for (int j = 0; j <= k; ++j) w[i | p][j] -= w[i][j];
            }
        }
    }
    std::vector res(n, T());
    for (int i = 0; i < n; ++i) res[i] = w[i][c[i]];
    return res;
}
