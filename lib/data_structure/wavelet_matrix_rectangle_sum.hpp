#include <cassert>
#include <numeric>
#include <tuple>
#include <vector>
#include "internal/internal_bit_vector.hpp"

template <class T, class U = T, int L = 30>
struct wavelet_matrix_rectangle_sum {
    wavelet_matrix_rectangle_sum() = default;
    template <class Value>
    wavelet_matrix_rectangle_sum(const std::vector<T> &v, const std::vector<Value> &u)
        : length(v.size()) {
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
    }

    U range_sum(int r, T x) const { return range_sum(0, r, x); }

    U range_sum(int l, int r, T x) const {
        for (int level = L - 1; level >= 0; level--)
            std::tie(l, r) = succ((x >> level) & 1, l, r, level);
        return cs[0][matrix[0].rank(false, r)] - cs[0][matrix[0].rank(false, l)];
    }

    U rect_sum(int l, int r, T upper) const {
        U res = 0;
        for (int level = L - 1; level >= 0; level--) {
            bool f = (upper >> level) & 1;
            if (f)
                res += cs[level][matrix[level].rank(false, r)] -
                       cs[level][matrix[level].rank(false, l)];
            std::tie(l, r) = succ(f, l, r, level);
        }
        return res;
    }

    U rect_sum(int l, int r, T lower, T upper) const {
        return rect_sum(l, r, upper) - rect_sum(l, r, lower);
    }

  private:
    int length;
    internal::bit_vector matrix[L];
    int mid[L];
    std::vector<U> cs[L];

    std::pair<int, int> succ(bool f, int l, int r, int level) const {
        return {matrix[level].rank(f, l) + mid[level] * f,
                matrix[level].rank(f, r) + mid[level] * f};
    }
};
