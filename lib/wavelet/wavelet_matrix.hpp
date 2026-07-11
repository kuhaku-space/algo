#pragma once
#include <vector>
#include "internal/internal_bit_vector.hpp"
#include "internal/wavelet_matrix_base.hpp"

/// @brief ウェーブレット行列
/// @see https://ei1333.github.io/library/structure/wavelet/wavelet-matrix.hpp
template <class T, int L = 20>
struct WaveletMatrix : internal::WaveletMatrixCore<internal::bit_vector, T, L> {
    using Base = internal::WaveletMatrixCore<internal::bit_vector, T, L>;
    using Base::length;
    using Base::matrix;
    using Base::mid;

    WaveletMatrix() = default;
    WaveletMatrix(std::vector<T> v) {
        length = v.size();
        std::vector<T> l(length), r(length);
        for (int level = L - 1; level >= 0; --level) {
            matrix[level] = internal::bit_vector(length + 1);
            int left = 0, right = 0;
            for (int i = 0; i < length; ++i) {
                if (v[i] >> level & 1) {
                    matrix[level].set(i);
                    r[right++] = v[i];
                } else {
                    l[left++] = v[i];
                }
            }
            mid[level] = left;
            matrix[level].build();
            v.swap(l);
            for (int i = 0; i < right; ++i) v[left + i] = r[i];
        }
    }
};
