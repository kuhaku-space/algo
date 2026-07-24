#pragma once
#include <cassert>
#include <cstdint>
#include <numeric>
#include <vector>

/// @brief 累積和
/// @tparam RangeAdd true なら区間加算（差分配列）、false なら点更新として構築する。
template <class T = std::int64_t, bool RangeAdd = false>
struct PrefixSum {
    /// @brief 空の累積和を構築する
    /// @complexity $O(1)$
    PrefixSum() = default;

    /// @brief 長さnの0列を構築する
    /// @complexity $O(n)$
    PrefixSum(int _n) : n(_n), data(_n + 1) {}

    /// @brief 列から累積和を構築する
    /// @complexity $O(n)$
    template <class U>
    PrefixSum(const std::vector<U> &v) : n(v.size()), data(v.size() + 1) {
        std::inclusive_scan(v.rbegin(), v.rend(), data.rbegin() + 1);
    }

    /// @brief build前の値から累積和を構築する
    /// @complexity $O(n)$
    void build() {
        if constexpr (RangeAdd) {
            for (int i = 0; i < n; ++i) data[i + 1] += data[i];
        }
        for (int i = n - 1; i >= 0; --i) data[i] += data[i + 1];
    }

    /// @brief k番目の値を返す
    /// @complexity $O(1)$
    T get(int k) const {
        assert(0 <= k && k < n);
        return data[k] - data[k + 1];
    }

    /// @brief v[k] = x（build 前のみ有効）
    /// @complexity $O(1)$
    void set(int k, T x)
    requires(!RangeAdd)
    {
        data[k] = x;
    }
    /// @brief v[k] += x（build 前のみ有効）
    /// @complexity $O(1)$
    void add(int k, T x) {
        if constexpr (RangeAdd) add(k, k + 1, x);
        else data[k] += x;
    }
    /// @brief v[l ... r-1] += x（build 前のみ有効）
    /// @complexity $O(1)$
    void add(int l, int r, T x)
    requires RangeAdd
    {
        data[l] += x;
        data[r] -= x;
    }

    /// @brief 接頭辞 $[0,r)$ の総和を返す
    /// @complexity $O(1)$
    T sum(int r) const {
        assert(0 <= r && r <= n);
        return data[0] - data[r];
    }
    /// @brief 半開区間 $[l,r)$ の総和を返す
    /// @complexity $O(1)$
    T sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        return data[l] - data[r];
    }

    /// @brief 接頭辞和がx以上となる最初の位置を返す
    /// @complexity $O(\log n)$
    int lower_bound(T x) const { return lower_bound(0, x); }

    /// @brief lからの区間和がx以上となる最初の位置を返す
    /// @complexity $O(\log n)$
    int lower_bound(int l, T x) const {
        assert(0 <= l && l <= n);
        int left = l - 1, right = n + 1;
        while (right - left > 1) {
            int mid = std::midpoint(left, right);
            (data[l] - data[mid] >= x ? right : left) = mid;
        }
        return right;
    }

    /// @brief 接頭辞和がxより大きくなる最初の位置を返す
    /// @complexity $O(\log n)$
    int upper_bound(T x) const { return upper_bound(0, x); }

    /// @brief lからの区間和がxより大きくなる最初の位置を返す
    /// @complexity $O(\log n)$
    int upper_bound(int l, T x) const {
        assert(0 <= l && l <= n);
        int left = l - 1, right = n + 1;
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
