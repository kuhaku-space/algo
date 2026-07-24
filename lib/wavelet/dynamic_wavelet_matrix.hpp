#pragma once
#include <vector>
#include "internal/dynamic_bit_vector.hpp"
#include "internal/wavelet_matrix_base.hpp"

/// @brief 要素の挿入・削除が可能な動的ウェーブレット行列
/// @complexity 構築は期待 $O(nL\log n)$、各操作は期待 $O(L\log n)$
template <class T, int L = 20>
struct DynamicWaveletMatrix : internal::WaveletMatrixCore<internal::dynamic_bit_vector, T, L> {
    /// @brief 共通実装の基底型
    /// @complexity 型エイリアスのため実行時コストなし
    using Base = internal::WaveletMatrixCore<internal::dynamic_bit_vector, T, L>;
    /// @brief 要素数を保持する基底クラスのメンバ
    /// @complexity $O(1)$ で参照可能
    using Base::length;
    /// @brief 各レベルの動的ビットベクトルを保持する基底クラスのメンバ
    /// @complexity 1 レベルの参照は $O(1)$
    using Base::matrix;
    /// @brief 各レベルの 0 の個数を保持する基底クラスのメンバ
    /// @complexity 1 レベルの参照は $O(1)$
    using Base::mid;

    /// @brief 空の動的ウェーブレット行列を作る
    /// @complexity $O(1)$
    DynamicWaveletMatrix() = default;
    /// @brief 列 `v` から動的ウェーブレット行列を構築する
    /// @complexity 期待 $O(nL\log n)$
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

    /// @brief 位置 `k` に値 `val` を挿入する
    /// @complexity 期待 $O(L\log n)$
    void insert(int k, T val) {
        for (int level = L - 1; level >= 0; --level) {
            const bool f = val >> level & 1;
            matrix[level].insert(k, f);
            k = matrix[level].rank(f, k);
            if (f) k += mid[level];
            else ++mid[level];
        }
    }

    /// @brief 位置 `k` の要素を削除する
    /// @complexity 期待 $O(L\log n)$
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

    /// @brief `k` 番目の値を返す
    /// @complexity 期待 $O(L\log n)$
    T access(int k) const { return Base::access(k); }

    /// @brief `access(k)` の別名
    /// @complexity 期待 $O(L\log n)$
    T operator[](int k) const { return access(k); }

    /// @brief $0 \le i < r$ かつ $v_i=x$ を満たす要素数を返す
    /// @complexity 期待 $O(L\log n)$
    int rank(int r, T x) const { return Base::rank(r, x); }

    /// @brief $l \le i < r$ かつ $v_i=x$ を満たす要素数を返す
    /// @complexity 期待 $O(L\log n)$
    int rank(int l, int r, T x) const { return Base::rank(l, r, x); }

    /// @brief 区間 $[l,r)$ 内で `k` 番目に小さい値を返す（0-indexed）
    /// @complexity 期待 $O(L\log n)$
    T kth_smallest(int l, int r, int k) const { return Base::kth_smallest(l, r, k); }

    /// @brief 区間 $[l,r)$ 内で `k` 番目に大きい値を返す（0-indexed）
    /// @complexity 期待 $O(L\log n)$
    T kth_largest(int l, int r, int k) const { return Base::kth_largest(l, r, k); }

    /// @brief 区間 $[l,r)$ にある `upper` 未満の要素数を返す
    /// @complexity 期待 $O(L\log n)$
    int range_freq(int l, int r, T upper) const { return Base::range_freq(l, r, upper); }

    /// @brief 区間 $[l,r)$ にある $[lower,upper)$ 内の要素数を返す
    /// @complexity 期待 $O(L\log n)$
    int range_freq(int l, int r, T lower, T upper) const { return Base::range_freq(l, r, lower, upper); }

    /// @brief 区間 $[l,r)$ にある `upper` 未満の最大値を返す
    /// @details 該当する値がなければ `T(-1)` を返す。
    /// @complexity 期待 $O(L\log n)$
    T prev_value(int l, int r, T upper) const { return Base::prev_value(l, r, upper); }

    /// @brief 区間 $[l,r)$ にある `lower` 以上の最小値を返す
    /// @details 該当する値がなければ `T(-1)` を返す。
    /// @complexity 期待 $O(L\log n)$
    T next_value(int l, int r, T lower) const { return Base::next_value(l, r, lower); }
};
