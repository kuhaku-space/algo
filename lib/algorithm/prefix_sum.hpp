#pragma once
#include <cassert>
#include <cstdint>
#include <numeric>
#include <vector>

/// @brief 累積和
template <class T = std::int64_t>
struct prefix_sum {
    prefix_sum(int _n) : n(_n), data(_n + 1) {}
    template <class U>
    prefix_sum(const std::vector<U> &v) : n(v.size()), data(v.size() + 1) {
        std::inclusive_scan(v.rbegin(), v.rend(), data.rbegin() + 1);
    }

    void build() {
        for (int i = n - 1; i >= 0; --i) data[i] += data[i + 1];
    }

    T get(int k) const {
        assert(0 <= k && k < n);
        return data[k] - data[k + 1];
    }

    void set(int k, int x) { data[k] = x; }
    void add(int k, int x) { data[k] += x; }

    T sum(int r) const {
        assert(0 <= r && r <= n);
        return data[0] - data[r];
    }
    T sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        return data[l] - data[r];
    }

    int min_left(T x) const { return min_left(0, x); }
    int min_left(int l, T x) const {
        assert(0 <= l && l <= n);
        int left = l, right = n + 1;
        while (right - left > 1) {
            int mid = (left + right) / 2;
            (data[l] - data[mid] >= x ? right : left) = mid;
        }
        return right;
    }

    int max_right(T x) const { return max_right(n, x); }
    int max_right(int r, T x) const {
        assert(0 <= r && r <= n);
        int left = -1, right = r;
        while (right - left > 1) {
            int mid = (left + right) / 2;
            (data[mid] - data[r] >= x ? left : right) = mid;
        }
        return left;
    }

  private:
    int n;
    std::vector<T> data;
};
