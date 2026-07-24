#pragma once
#include <vector>
#include "algorithm/compress.hpp"
#include "wavelet/wavelet_matrix.hpp"

/// @brief ウェーブレット行列（座標圧縮）
/// @complexity 構築は $O(n\log n+nL)$、各問い合わせは $O(L)$
/// @see https://ei1333.github.io/library/structure/wavelet/wavelet-matrix.hpp
template <class T, int L = 20>
struct CompressedWaveletMatrix {
    /// @brief 空のウェーブレット行列を作る
    /// @complexity $O(1)$
    CompressedWaveletMatrix() = default;
    /// @brief 列 `v` を座標圧縮してウェーブレット行列を構築する
    /// @complexity $O(n\log n+nL)$
    CompressedWaveletMatrix(const std::vector<T> &v) : cps(v) {
        int n = v.size();
        std::vector<int> t(n);
        for (int i = 0; i < n; ++i) t[i] = cps.get(v[i]);
        mat = WaveletMatrix<int, L>(t);
    }

    /// @brief `k` 番目の値を返す
    /// @complexity $O(L)$
    T access(int k) const { return cps[mat.access(k)]; }
    /// @brief `access(k)` の別名
    /// @complexity $O(L)$
    T operator[](int k) const { return access(k); }

    /// @brief $0 \le i < r$ かつ $v_i=x$ を満たす要素数を返す
    /// @complexity $O(L+\log n)$
    int rank(int r, T x) const {
        auto pos = cps.get(x);
        if (pos == cps.size() || cps[pos] != x) return 0;
        return mat.rank(r, pos);
    }

    /// @brief $l \le i < r$ かつ $v_i=x$ を満たす要素数を返す
    /// @complexity $O(L+\log n)$
    int rank(int l, int r, T x) const { return rank(r, x) - rank(l, x); }

    /// @brief 区間 $[l,r)$ 内で `k` 番目に小さい値を返す（0-indexed）
    /// @complexity $O(L)$
    T kth_smallest(int l, int r, int k) const { return cps[mat.kth_smallest(l, r, k)]; }

    /// @brief 区間 $[l,r)$ 内で `k` 番目に大きい値を返す（0-indexed）
    /// @complexity $O(L)$
    T kth_largest(int l, int r, int k) const { return cps[mat.kth_largest(l, r, k)]; }

    /// @brief 区間 $[l,r)$ にある `upper` 未満の要素数を返す
    /// @complexity $O(L+\log n)$
    int range_freq(int l, int r, T upper) const { return mat.range_freq(l, r, cps.get(upper)); }

    /// @brief 区間 $[l,r)$ にある $[lower,upper)$ 内の要素数を返す
    /// @complexity $O(L+\log n)$
    int range_freq(int l, int r, T lower, T upper) const {
        return mat.range_freq(l, r, cps.get(lower), cps.get(upper));
    }

    /// @brief 区間 $[l,r)$ にある `upper` 未満の最大値を返す
    /// @details 該当する値がなければ `T(-1)` を返す。
    /// @complexity $O(L+\log n)$
    T prev_value(int l, int r, T upper) const {
        auto res = mat.prev_value(l, r, cps.get(upper));
        return res == -1 ? T(-1) : cps[res];
    }

    /// @brief 区間 $[l,r)$ にある `lower` 以上の最小値を返す
    /// @details 該当する値がなければ `T(-1)` を返す。
    /// @complexity $O(L+\log n)$
    T next_value(int l, int r, T lower) const {
        auto res = mat.next_value(l, r, cps.get(lower));
        return res == -1 ? T(-1) : cps[res];
    }

  private:
    WaveletMatrix<int, L> mat;
    coordinate_compression<T> cps;
};
