#pragma once
#include <vector>
#include "internal/dynamic_bit_vector.hpp"
#include "internal/wavelet_matrix_base.hpp"

/// @brief 動的ウェーブレット行列
template <class T, int L = 20>
struct DynamicWaveletMatrix : internal::WaveletMatrixCore<internal::dynamic_bit_vector, T, L> {
    using Base = internal::WaveletMatrixCore<internal::dynamic_bit_vector, T, L>;
    using Base::length;
    using Base::matrix;
    using Base::mid;

    DynamicWaveletMatrix() = default;
    DynamicWaveletMatrix(std::vector<T> v) {
        length = v.size();
        std::vector<T> l(length), r(length);
        for (int level = L - 1; level >= 0; --level) {
            int left = 0, right = 0;
            for (int i = 0; i < length; ++i) {
                if (v[i] >> level & 1) {
                    matrix[level].insert(i, 1);
                    r[right++] = v[i];
                } else {
                    matrix[level].insert(i, 0);
                    l[left++] = v[i];
                }
            }
            mid[level] = left;
            v.swap(l);
            for (int i = 0; i < right; ++i) v[left + i] = r[i];
        }
    }

    void insert(int k, T val) {
        for (int level = L - 1; level >= 0; --level) {
            const bool f = val >> level & 1;
            matrix[level].insert(k, f);
            k = matrix[level].rank(f, k);
            if (f) k += mid[level];
            else ++mid[level];
        }
    }

    void erase(int k) {
        for (int level = L - 1; level >= 0; --level) {
            bool f = matrix[level][k];
            int p = matrix[level].rank(f, k);
            matrix[level].erase(k);
            if (f) p += mid[level];
            else --mid[level];
            k = p;
        }
    }
};
