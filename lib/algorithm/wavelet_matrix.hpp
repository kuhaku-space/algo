#include "data_structure/bit_vector.hpp"
#include "template/template.hpp"

template <typename T, int MAXLOG>
struct wavelet_matrix {
    int length;
    bit_vector matrix[MAXLOG];
    int mid[MAXLOG];

    wavelet_matrix() = default;

    wavelet_matrix(vector<T> v) : length(v.size()) {
        vector<T> l(length), r(length);
        for (int level = MAXLOG - 1; level >= 0; level--) {
            matrix[level] = bit_vector(length + 1);
            int left = 0, right = 0;
            for (int i = 0; i < length; i++) {
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
            for (int i = 0; i < right; i++) { v[left + i] = r[i]; }
        }
    }

    pair<int, int> succ(bool f, int l, int r, int level) {
        return {matrix[level].rank(f, l) + mid[level] * f,
                matrix[level].rank(f, r) + mid[level] * f};
    }

    T access(int k) {
        T ret = 0;
        for (int level = MAXLOG - 1; level >= 0; level--) {
            bool f = matrix[level][k];
            if (f) ret |= T(1) << level;
            k = matrix[level].rank(f, k) + mid[level] * f;
        }
        return ret;
    }

    T operator[](const int &k) { return access(k); }

    int rank(const T &x, int r) {
        int l = 0;
        for (int level = MAXLOG - 1; level >= 0; level--) {
            tie(l, r) = succ((x >> level) & 1, l, r, level);
        }
        return r - l;
    }

    T kth_smallest(int l, int r, int k) {
        assert(0 <= k && k < r - l);
        T ret = 0;
        for (int level = MAXLOG - 1; level >= 0; level--) {
            int cnt = matrix[level].rank(false, r) - matrix[level].rank(false, l);
            bool f = cnt <= k;
            if (f) {
                ret |= T(1) << level;
                k -= cnt;
            }
            tie(l, r) = succ(f, l, r, level);
        }
        return ret;
    }

    T kth_largest(int l, int r, int k) { return kth_smallest(l, r, r - l - k - 1); }

    int range_freq(int l, int r, T upper) {
        int ret = 0;
        for (int level = MAXLOG - 1; level >= 0; level--) {
            bool f = ((upper >> level) & 1);
            if (f) ret += matrix[level].rank(false, r) - matrix[level].rank(false, l);
            tie(l, r) = succ(f, l, r, level);
        }
        return ret;
    }

    int range_freq(int l, int r, T lower, T upper) {
        return range_freq(l, r, upper) - range_freq(l, r, lower);
    }

    T prev_value(int l, int r, T upper) {
        int cnt = range_freq(l, r, upper);
        return cnt == 0 ? T(-1) : kth_smallest(l, r, cnt - 1);
    }

    T next_value(int l, int r, T lower) {
        int cnt = range_freq(l, r, lower);
        return cnt == r - l ? T(-1) : kth_smallest(l, r, cnt);
    }
};
