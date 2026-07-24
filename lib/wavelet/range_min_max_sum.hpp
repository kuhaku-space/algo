#pragma once
#include <vector>
#include "wavelet/wavelet_matrix_rectangle_sum.hpp"

/// @brief 区間 [l, r) について sum(min(A_i, x)) / sum(max(A_i, x)) を求める
/// @complexity 構築は $O(nL)$、問い合わせは $O(L)$
template <class T, class U = T, int L = 30>
struct RangeMinMaxSum {
    /// @brief 空のデータ構造を作る
    /// @complexity $O(1)$
    RangeMinMaxSum() = default;
    /// @brief 列 `v` からデータ構造を構築する
    /// @complexity $O(nL)$
    explicit RangeMinMaxSum(const std::vector<T> &v) : wm(v, v) {}

    /// @brief $\sum_{i=l}^{r-1}\min(v_i,x)$ を返す
    /// @complexity $O(L)$
    U query_min(int l, int r, T x) const {
        auto [cnt, sum] = wm.rect_count_sum(l, r, x + 1);
        return sum + U(x) * U(r - l - cnt);
    }

    /// @brief $\sum_{i=l}^{r-1}\max(v_i,x)$ を返す
    /// @complexity $O(L)$
    U query_max(int l, int r, T x) const { return wm.total_sum(l, r) + U(x) * U(r - l) - query_min(l, r, x); }

  private:
    WaveletMatrixRectangleSum<T, U, L> wm;
};
