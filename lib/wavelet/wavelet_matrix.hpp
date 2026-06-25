#pragma once
#include <cassert>
#include <tuple>
#include <vector>
#include "internal/internal_bit_vector.hpp"

/// @brief ウェーブレット行列
/// @see https://ei1333.github.io/library/structure/wavelet/wavelet-matrix.hpp
template <class T, int L = 20>
struct wavelet_matrix {
    wavelet_matrix() = default;
    wavelet_matrix(std::vector<T> v) : length(v.size()) {
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

    T access(int k) const {
        T res = 0;
        for (int level = L - 1; level >= 0; --level) {
            bool f = matrix[level][k];
            if (f) res |= T(1) << level;
            k = matrix[level].rank(f, k) + mid[level] * f;
        }
        return res;
    }
    T operator[](int k) const { return access(k); }

    /// count i s.t. (0 <= i < r) && v[i] == x
    int rank(int r, T x) const {
        int l = 0;
        for (int level = L - 1; level >= 0; --level) { std::tie(l, r) = succ((x >> level) & 1, l, r, level); }
        return r - l;
    }

    /// count i s.t. (l <= i < r) && v[i] == x
    int rank(int l, int r, T x) const { return rank(r, x) - rank(l, x); }

    /// k-th smallest number in v[l ... r-1]
    T kth_smallest(int l, int r, int k) const {
        assert(0 <= k && k < r - l);
        T res = 0;
        for (int level = L - 1; level >= 0; --level) {
            int cnt = matrix[level].rank(false, r) - matrix[level].rank(false, l);
            bool f = cnt <= k;
            if (f) {
                res |= T(1) << level;
                k -= cnt;
            }
            std::tie(l, r) = succ(f, l, r, level);
        }
        return res;
    }

    /// k-th largest number in v[l ... r-1]
    T kth_largest(int l, int r, int k) const { return kth_smallest(l, r, r - l - k - 1); }

    /// count i s.t. (l <= i < r) && (v[i] < upper)
    int range_freq(int l, int r, T upper) const {
        int res = 0;
        for (int level = L - 1; level >= 0; --level) {
            bool f = ((upper >> level) & 1);
            if (f) res += matrix[level].rank(false, r) - matrix[level].rank(false, l);
            std::tie(l, r) = succ(f, l, r, level);
        }
        return res;
    }

    /// count i s.t. (l <= i < r) && (lower <= v[i] < upper)
    int range_freq(int l, int r, T lower, T upper) const { return range_freq(l, r, upper) - range_freq(l, r, lower); }

    /// max v[i] s.t. (l <= i < r) && (v[i] < upper)
    T prev_value(int l, int r, T upper) const {
        int cnt = range_freq(l, r, upper);
        return cnt == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);
    }

    /// min v[i] s.t. (l <= i < r) && (lower <= v[i])
    T next_value(int l, int r, T lower) const {
        int cnt = range_freq(l, r, lower);
        return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);
    }

  private:
    int length;
    internal::bit_vector matrix[L];
    int mid[L];

    std::pair<int, int> succ(bool f, int l, int r, int level) const {
        return {matrix[level].rank(f, l) + mid[level] * f, matrix[level].rank(f, r) + mid[level] * f};
    }
};
