#pragma once
#include <algorithm>
#include <bit>
#include <vector>

/// @brief merge-sort tree
template <class T>
struct merge_sort_tree {
    merge_sort_tree() = default;
    template <class U>
    explicit merge_sort_tree(const std::vector<U> &v) : _n(v.size()) {
        _size = std::bit_ceil<unsigned>(_n);
        _log = std::countr_zero<unsigned>(_size);
        data.resize(_size << 1);
        for (int i = 0; i < _n; ++i) data[_size + i].emplace_back(v[i]);
        for (int i = _size - 1; i >= 1; --i) {
            data[i] = data[2 * i];
            data[i].insert(data[i].end(), data[2 * i + 1].begin(), data[2 * i + 1].end());
            std::inplace_merge(data[i].begin(), data[i].begin() + data[2 * i].size(),
                               data[i].end());
        }
    }

    /// count i s.t. (0 <= i < r) && v[i] == x
    int rank(int r, T x) const { return rank(0, r, x); }

    /// count i s.t. (l <= i < r) && v[i] == x
    int rank(int l, int r, T x) const {
        int res = 0;
        for (l += _size, r += _size; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                auto it = std::lower_bound(data[l].begin(), data[l].end(), x);
                res += std::upper_bound(it, data[l].end(), x) - it;
                ++l;
            }
            if (r & 1) {
                --r;
                auto it = std::lower_bound(data[r].begin(), data[r].end(), x);
                res += std::upper_bound(it, data[r].end(), x) - it;
            }
        }
        return res;
    }

    /// count i s.t. (l <= i < r) && (v[i] < upper)
    int range_freq(int l, int r, T upper) const {
        int res = 0;
        for (l += _size, r += _size; l < r; l >>= 1, r >>= 1) {
            if (l & 1) {
                res += std::lower_bound(data[l].begin(), data[l].end(), upper) - data[l].begin();
                ++l;
            }
            if (r & 1) {
                --r;
                res += std::lower_bound(data[r].begin(), data[r].end(), upper) - data[r].begin();
            }
        }
        return res;
    }

    /// count i s.t. (l <= i < r) && (lower <= v[i] < upper)
    int range_freq(int l, int r, T lower, T upper) const {
        return range_freq(l, r, upper) - range_freq(l, r, lower);
    }

  private:
    int _n, _size, _log;
    std::vector<std::vector<T>> data;
};
