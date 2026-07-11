#pragma once
#include <vector>
#include "wavelet/wavelet_matrix_rectangle_sum.hpp"

/// @brief 区間 [l, r) について sum(min(A_i, x)) を求める
template <class T, class U = T, int L = 30>
struct RangeMinSum {
    RangeMinSum() = default;
    explicit RangeMinSum(const std::vector<T> &v) : wm(v, v) {}

    U query(int l, int r, T x) const {
        auto [cnt, sum] = wm.rect_count_sum(l, r, x + 1);
        return sum + U(x) * U(r - l - cnt);
    }

  private:
    WaveletMatrixRectangleSum<T, U, L> wm;
};
