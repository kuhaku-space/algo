#pragma once
#include <cassert>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>
#include "internal/internal_bit_vector.hpp"
#include "internal/wavelet_matrix_base.hpp"

/// @brief 重み付きウェーブレット行列
template <class T, class U = T, int L = 30>
struct WaveletMatrixRectangleSum : private internal::WaveletMatrixCore<internal::bit_vector, T, L> {
    using Base = internal::WaveletMatrixCore<internal::bit_vector, T, L>;
    using Base::length;
    using Base::matrix;
    using Base::mid;
    using Base::succ;

    WaveletMatrixRectangleSum() = default;
    template <class Value>
    WaveletMatrixRectangleSum(const std::vector<T> &v, const std::vector<Value> &u) {
        length = v.size();
        assert(v.size() == u.size());
        std::vector<int> l(length), r(length), ord(length);
        std::iota(ord.begin(), ord.end(), 0);
        for (int level = L - 1; level >= 0; level--) {
            matrix[level] = internal::bit_vector(length + 1);
            int left = 0, right = 0;
            for (int i = 0; i < length; i++) {
                if ((v[ord[i]] >> level) & 1) {
                    matrix[level].set(i);
                    r[right++] = ord[i];
                } else {
                    l[left++] = ord[i];
                }
            }
            mid[level] = left;
            matrix[level].build();
            ord.swap(l);
            for (int i = 0; i < right; i++) ord[left + i] = r[i];
            cs[level].resize(length + 1);
            cs[level][0] = U(0);
            for (int i = 0; i < length; i++) cs[level][i + 1] = cs[level][i] + u[ord[i]];
        }
        total_cs.resize(length + 1);
        total_cs[0] = U(0);
        for (int i = 0; i < length; i++) total_cs[i + 1] = total_cs[i] + u[i];
    }

    /// sum of u[l ... r-1] (regardless of v)
    U total_sum(int l, int r) const { return total_cs[r] - total_cs[l]; }

    /// sum of the k smallest values in v[l ... r-1] (requires U == T and u == v)
    U kth_smallest_sum(int l, int r, int k) const {
        assert(0 <= k && k <= r - l);
        T val = T();
        U res = U();
        for (int level = L - 1; level >= 0; --level) {
            int cnt = matrix[level].rank(false, r) - matrix[level].rank(false, l);
            bool f = cnt <= k;
            if (f) {
                val |= T(1) << level;
                res += cs[level][matrix[level].rank(false, r)] - cs[level][matrix[level].rank(false, l)];
                k -= cnt;
            }
            std::tie(l, r) = succ(f, l, r, level);
        }
        return res + val * k;
    }

    /// sum of the k largest values in v[l ... r-1] (requires U == T and u == v)
    U kth_largest_sum(int l, int r, int k) const { return total_sum(l, r) - kth_smallest_sum(l, r, r - l - k); }

    U range_sum(int r, T x) const { return range_sum(0, r, x); }

    U range_sum(int l, int r, T x) const {
        for (int level = L - 1; level >= 0; level--) std::tie(l, r) = succ((x >> level) & 1, l, r, level);
        return cs[0][r] - cs[0][l];
    }

    U rect_sum(int l, int r, T upper) const { return rect_count_sum(l, r, upper).second; }

    U rect_sum(int l, int r, T lower, T upper) const { return rect_sum(l, r, upper) - rect_sum(l, r, lower); }

    /// count i s.t. (l <= i < r) && (v[i] < upper) と、そのときの u[i] の総和
    std::pair<int, U> rect_count_sum(int l, int r, T upper) const {
        int cnt = 0;
        U sum = U();
        for (int level = L - 1; level >= 0; level--) {
            bool f = (upper >> level) & 1;
            if (f) {
                int rl = matrix[level].rank(false, l), rr = matrix[level].rank(false, r);
                cnt += rr - rl;
                sum += cs[level][rr] - cs[level][rl];
            }
            std::tie(l, r) = succ(f, l, r, level);
        }
        return {cnt, sum};
    }

  private:
    std::vector<U> cs[L];
    std::vector<U> total_cs;
};
