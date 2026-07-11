#pragma once
#include <vector>
#include "algorithm/compress.hpp"
#include "wavelet/wavelet_matrix.hpp"

/// @brief ウェーブレット行列（座標圧縮）
/// @see https://ei1333.github.io/library/structure/wavelet/wavelet-matrix.hpp
template <class T, int L = 20>
struct CompressedWaveletMatrix {
    CompressedWaveletMatrix() = default;
    CompressedWaveletMatrix(const std::vector<T> &v) : cps(v) {
        int n = v.size();
        std::vector<int> t(n);
        for (int i = 0; i < n; ++i) t[i] = cps.get(v[i]);
        mat = WaveletMatrix<int, L>(t);
    }

    T access(int k) const { return cps[mat.access(k)]; }
    T operator[](int k) const { return access(k); }

    /// count i s.t. (0 <= i < r) && v[i] == x
    int rank(int r, T x) const {
        auto pos = cps.get(x);
        if (pos == cps.size() || cps[pos] != x) return 0;
        return mat.rank(r, pos);
    }

    /// count i s.t. (l <= i < r) && v[i] == x
    int rank(int l, int r, T x) const { return rank(r, x) - rank(l, x); }

    /// k-th smallest number in v[l ... r-1]
    T kth_smallest(int l, int r, int k) const { return cps[mat.kth_smallest(l, r, k)]; }

    /// k-th largest number in v[l ... r-1]
    T kth_largest(int l, int r, int k) const { return cps[mat.kth_largest(l, r, k)]; }

    /// count i s.t. (l <= i < r) && (v[i] < upper)
    int range_freq(int l, int r, T upper) const { return mat.range_freq(l, r, cps.get(upper)); }

    /// count i s.t. (l <= i < r) && (lower <= v[i] < upper)
    int range_freq(int l, int r, T lower, T upper) const {
        return mat.range_freq(l, r, cps.get(lower), cps.get(upper));
    }

    /// max v[i] s.t. (l <= i < r) && (v[i] < upper)
    T prev_value(int l, int r, T upper) const {
        auto res = mat.prev_value(l, r, cps.get(upper));
        return res == -1 ? T(-1) : cps[res];
    }

    /// min v[i] s.t. (l <= i < r) && (lower <= v[i])
    T next_value(int l, int r, T lower) const {
        auto res = mat.next_value(l, r, cps.get(lower));
        return res == -1 ? T(-1) : cps[res];
    }

  private:
    WaveletMatrix<int, L> mat;
    coordinate_compression<T> cps;
};
