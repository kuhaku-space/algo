#include "data_structure/bit_vector.hpp"
#include "template/template.hpp"

/**
 * @brief ウェーブレット行列
 * @details [参考](https://ei1333.github.io/library/structure/wavelet/wavelet-matrix.cpp.html)
 *
 * @tparam T
 * @tparam L
 */
template <class T, int L = 20>
struct wavelet_matrix {
    wavelet_matrix() = default;
    wavelet_matrix(std::vector<T> v) : length(v.size()) {
        std::vector<T> l(length), r(length);
        for (int level = L - 1; level >= 0; --level) {
            this->matrix[level] = bit_vector(this->length + 1);
            int left = 0, right = 0;
            for (int i = 0; i < this->length; ++i) {
                if (v[i] >> level & 1) {
                    this->matrix[level].set(i);
                    r[right++] = v[i];
                } else {
                    l[left++] = v[i];
                }
            }
            this->mid[level] = left;
            this->matrix[level].build();
            v.swap(l);
            for (int i = 0; i < right; ++i) {
                v[left + i] = r[i];
            }
        }
    }

    T access(int k) const {
        T res = 0;
        for (int level = L - 1; level >= 0; --level) {
            bool f = this->matrix[level][k];
            if (f) res |= T(1) << level;
            k = this->matrix[level].rank(f, k) + this->mid[level] * f;
        }
        return res;
    }
    T operator[](int k) const { return this->access(k); }

    /**
     * @brief count i s.t. (0 <= i < r) && v[i] == x
     *
     * @param x
     * @param r
     * @return int
     */
    int rank(int r, T x) const {
        int l = 0;
        for (int level = L - 1; level >= 0; --level) {
            std::tie(l, r) = this->succ((x >> level) & 1, l, r, level);
        }
        return r - l;
    }

    /**
     * @brief count i s.t. (l <= i < r) && v[i] == x
     *
     * @param l
     * @param r
     * @param x
     * @return int
     */
    int rank(int l, int r, T x) const { return this->rank(r, x) - this->rank(l, x); }

    /**
     * @brief k-th smallest number in v[l ... r-1]
     *
     * @param l
     * @param r
     * @param k
     * @return T
     */
    T kth_smallest(int l, int r, int k) const {
        assert(0 <= k && k < r - l);
        T res = 0;
        for (int level = L - 1; level >= 0; --level) {
            int cnt = this->matrix[level].rank(false, r) - this->matrix[level].rank(false, l);
            bool f = cnt <= k;
            if (f) {
                res |= T(1) << level;
                k -= cnt;
            }
            std::tie(l, r) = succ(f, l, r, level);
        }
        return res;
    }

    /**
     * @brief k-th largest number in v[l ... r-1]
     *
     * @param l
     * @param r
     * @param k
     * @return T
     */
    T kth_largest(int l, int r, int k) const { return this->kth_smallest(l, r, r - l - k - 1); }

    /**
     * @brief count i s.t. (l <= i < r) && (v[i] < upper)
     *
     * @param l
     * @param r
     * @param upper
     * @return int
     */
    int range_freq(int l, int r, T upper) const {
        int res = 0;
        for (int level = L - 1; level >= 0; --level) {
            bool f = ((upper >> level) & 1);
            if (f) res += this->matrix[level].rank(false, r) - this->matrix[level].rank(false, l);
            std::tie(l, r) = this->succ(f, l, r, level);
        }
        return res;
    }

    /**
     * @brief count i s.t. (l <= i < r) && (lower <= v[i] < upper)
     *
     * @param l
     * @param r
     * @param lower
     * @param upper
     * @return int
     */
    int range_freq(int l, int r, T lower, T upper) const {
        return this->range_freq(l, r, upper) - this->range_freq(l, r, lower);
    }

    /**
     * @brief max v[i] s.t. (l <= i < r) && (v[i] < upper)
     *
     * @param l
     * @param r
     * @param upper
     * @return T
     */
    T prev_value(int l, int r, T upper) const {
        int cnt = this->range_freq(l, r, upper);
        return cnt == 0 ? T(-1) : this->kth_smallest(l, r, cnt - 1);
    }

    /**
     * @brief min v[i] s.t. (l <= i < r) && (lower <= v[i])
     *
     * @param l
     * @param r
     * @param lower
     * @return T
     */
    T next_value(int l, int r, T lower) const {
        int cnt = this->range_freq(l, r, lower);
        return cnt == r - l ? T(-1) : this->kth_smallest(l, r, cnt);
    }

  private:
    int length;
    bit_vector matrix[L];
    int mid[L];

    std::pair<int, int> succ(bool f, int l, int r, int level) const {
        return {this->matrix[level].rank(f, l) + this->mid[level] * f,
                this->matrix[level].rank(f, r) + this->mid[level] * f};
    }
};
