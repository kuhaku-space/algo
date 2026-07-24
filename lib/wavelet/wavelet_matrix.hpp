#pragma once
#include <vector>
#include "internal/internal_bit_vector.hpp"
#include "internal/wavelet_matrix_base.hpp"

/// @brief ウェーブレット行列
/// @complexity 構築は $O(nL)$、各問い合わせは $O(L)$
/// @see https://ei1333.github.io/library/structure/wavelet/wavelet-matrix.hpp
template <class T, int L = 20>
struct WaveletMatrix : internal::WaveletMatrixCore<internal::bit_vector, T, L> {
    /// @brief 共通実装の基底型
    /// @complexity 型エイリアスのため実行時コストなし
    using Base = internal::WaveletMatrixCore<internal::bit_vector, T, L>;
    /// @brief 要素数を保持する基底クラスのメンバ
    /// @complexity $O(1)$ で参照可能
    using Base::length;
    /// @brief 各レベルのビットベクトルを保持する基底クラスのメンバ
    /// @complexity 1 レベルの参照は $O(1)$
    using Base::matrix;
    /// @brief 各レベルの 0 の個数を保持する基底クラスのメンバ
    /// @complexity 1 レベルの参照は $O(1)$
    using Base::mid;

    /// @brief 空のウェーブレット行列を作る
    /// @complexity $O(1)$
    WaveletMatrix() = default;
    /// @brief 列 `v` からウェーブレット行列を構築する
    /// @complexity $O(nL)$
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

    /// @brief `k` 番目の値を返す
    /// @complexity $O(L)$
    T access(int k) const { return Base::access(k); }

    /// @brief `access(k)` の別名
    /// @complexity $O(L)$
    T operator[](int k) const { return access(k); }

    /// @brief $0 \le i < r$ かつ $v_i=x$ を満たす要素数を返す
    /// @complexity $O(L)$
    int rank(int r, T x) const { return Base::rank(r, x); }

    /// @brief $l \le i < r$ かつ $v_i=x$ を満たす要素数を返す
    /// @complexity $O(L)$
    int rank(int l, int r, T x) const { return Base::rank(l, r, x); }

    /// @brief 区間 $[l,r)$ 内で `k` 番目に小さい値を返す（0-indexed）
    /// @complexity $O(L)$
    T kth_smallest(int l, int r, int k) const { return Base::kth_smallest(l, r, k); }

    /// @brief 区間 $[l,r)$ 内で `k` 番目に大きい値を返す（0-indexed）
    /// @complexity $O(L)$
    T kth_largest(int l, int r, int k) const { return Base::kth_largest(l, r, k); }

    /// @brief 区間 $[l,r)$ にある `upper` 未満の要素数を返す
    /// @complexity $O(L)$
    int range_freq(int l, int r, T upper) const { return Base::range_freq(l, r, upper); }

    /// @brief 区間 $[l,r)$ にある $[lower,upper)$ 内の要素数を返す
    /// @complexity $O(L)$
    int range_freq(int l, int r, T lower, T upper) const { return Base::range_freq(l, r, lower, upper); }

    /// @brief 区間 $[l,r)$ にある `upper` 未満の最大値を返す
    /// @details 該当する値がなければ `T(-1)` を返す。
    /// @complexity $O(L)$
    T prev_value(int l, int r, T upper) const { return Base::prev_value(l, r, upper); }

    /// @brief 区間 $[l,r)$ にある `lower` 以上の最小値を返す
    /// @details 該当する値がなければ `T(-1)` を返す。
    /// @complexity $O(L)$
    T next_value(int l, int r, T lower) const { return Base::next_value(l, r, lower); }
};
