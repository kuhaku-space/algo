#pragma once
#include <cassert>
#include <cstdint>
#include <numeric>
#include <vector>

/// @brief 累積和
template <class T = std::int64_t>
struct imos {
    imos() = default;
    imos(int _n) : n(_n), data(_n + 1) {}

    void build() {
        for (int i = 0; i < n; ++i) data[i + 1] += data[i];
        for (int i = n - 1; i >= 0; --i) data[i] += data[i + 1];
    }

    T get(int k) const {
        assert(0 <= k && k < n);
        return data[k] - data[k + 1];
    }

    void add(int l, int r, T x) {
        data[l] += x;
        data[r] -= x;
    }
    void add(int k, T x) { add(k, k + 1, x); }

    T sum(int r) const {
        assert(0 <= r && r <= n);
        return data[0] - data[r];
    }
    T sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        return data[l] - data[r];
    }

    int lower_bound(T x) const { return lower_bound(0, x); }
    int lower_bound(int l, T x) const {
        assert(0 <= l && l <= n);
        int left = l, right = n + 1;
        while (right - left > 1) {
            int mid = std::midpoint(left, right);
            (data[l] - data[mid] >= x ? right : left) = mid;
        }
        return right;
    }

    int upper_bound(T x) const { return upper_bound(0, x); }
    int upper_bound(int l, T x) const {
        assert(0 <= l && l <= n);
        int left = l, right = n + 1;
        while (right - left > 1) {
            int mid = std::midpoint(left, right);
            (data[l] - data[mid] > x ? right : left) = mid;
        }
        return right;
    }

  private:
    int n;
    std::vector<T> data;
};
