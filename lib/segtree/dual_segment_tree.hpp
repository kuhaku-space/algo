#pragma once
#include <bit>
#include <cassert>
#include <vector>
#include "segtree/monoid.hpp"

/// @brief 双対セグメント木
/// @complexity 構築は $O(n)$、点取得・区間作用は $O(\log n)$
template <monoid M>
struct DualSegmentTree {
  private:
    using T = typename M::value_type;

  public:
    /// @brief 空の木を構築する
    /// @complexity $O(1)$
    DualSegmentTree() : DualSegmentTree(0) {}

    /// @brief n要素をeで初期化する
    /// @complexity $O(n)$
    explicit DualSegmentTree(int _n, T e = M::id()) : DualSegmentTree(std::vector<T>(_n, e)) {}

    /// @brief 列vから構築する
    /// @complexity $O(n)$
    template <class U>
    explicit DualSegmentTree(const std::vector<U> &v) : n(v.size()) {
        size = std::bit_ceil<unsigned>(n);
        log = std::countr_zero<unsigned>(size);
        data = std::vector<T>(size << 1, M::id());
        for (int i = 0; i < n; ++i) data[size + i] = T(v[i]);
    }

    /// @brief k番目の値を返す
    /// @complexity $O(\log n)$
    T at(int k) { return get(k); }

    /// @brief k番目の値を返す
    /// @complexity $O(\log n)$
    T get(int k) {
        assert(0 <= k && k < n);
        k += size;
        for (int i = log; i >= 1; --i) push(k >> i);
        return data[k];
    }

    /// @brief a番目にvalを作用する
    /// @complexity $O(\log n)$
    void apply(int a, T val) { apply(a, a + 1, val); }

    /// @brief 半開区間[a,b)にvalを作用する
    /// @complexity $O(\log n)$
    void apply(int a, int b, T val) {
        assert(0 <= a && a <= n);
        assert(0 <= b && b <= n);
        a += size, b += size;
        for (int i = log; i >= 1; --i) {
            if (((a >> i) << i) != a) push(a >> i);
            if (((b >> i) << i) != b) push((b - 1) >> i);
        }

        for (; a < b; a >>= 1, b >>= 1) {
            if (a & 1) all_apply(a++, val);
            if (b & 1) all_apply(--b, val);
        }
    }

  private:
    int n, size, log;
    std::vector<T> data;

    void all_apply(int k, T val) { data[k] = M::op(val, data[k]); }
    void push(int k) {
        all_apply(2 * k, data[k]);
        all_apply(2 * k + 1, data[k]);
        data[k] = M::id();
    }
};
