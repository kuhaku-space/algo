#pragma once
#include <cassert>
#include <vector>
#include "internal/internal_bit.hpp"
#include "segment_tree/monoid.hpp"

/**
 * @brief 遅延評価セグメント木
 * @see https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp
 *
 * @tparam S モノイド
 * @tparam F モノイド
 */
template <class S, class F>
struct lazy_segment_tree {
  private:
    using T = typename S::value_type;
    using U = typename F::value_type;

  public:
    lazy_segment_tree() : lazy_segment_tree(0) {}
    explicit lazy_segment_tree(int n, T e = S::id) : lazy_segment_tree(std::vector<T>(n, e)) {}
    explicit lazy_segment_tree(const std::vector<T> &v) : _n(int(v.size())) {
        _size = internal::bit_ceil(_n);
        _log = internal::countr_zero(_size);
        data = std::vector<T>(2 * _size, S::id);
        lazy = std::vector<U>(_size, F::id);
        for (int i = 0; i < _n; i++) data[_size + i] = v[i];
        for (int i = _size - 1; i >= 1; --i) update(i);
    }

    void set(int p, T x) {
        assert(0 <= p && p < _n);
        p += _size;
        for (int i = _log; i >= 1; --i) push(p >> i);
        data[p] = x;
        for (int i = 1; i <= _log; ++i) update(p >> i);
    }

    T at(int p) { return get(p); }
    T get(int p) {
        assert(0 <= p && p < _n);
        p += _size;
        for (int i = _log; i >= 1; --i) push(p >> i);
        return data[p];
    }

    void apply(int p, U f) {
        assert(0 <= p && p < _n);
        p += _size;
        for (int i = _log; i >= 1; --i) push(p >> i);
        data[p] = F::f(f, data[p]);
        for (int i = 1; i <= _log; ++i) update(p >> i);
    }
    void apply(int l, int r, U f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += _size, r += _size;

        for (int i = _log; i >= 1; --i) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) all_apply(l++, f);
            if (r & 1) all_apply(--r, f);
            l >>= 1, r >>= 1;
        }
        l = l2, r = r2;

        for (int i = 1; i <= _log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    T prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return S::id;

        l += _size, r += _size;

        for (int i = _log; i >= 1; --i) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        T sml = S::id, smr = S::id;
        while (l < r) {
            if (l & 1) sml = S::op(sml, data[l++]);
            if (r & 1) smr = S::op(data[--r], smr);
            l >>= 1, r >>= 1;
        }

        return S::op(sml, smr);
    }

    T all_prod() const { return data[1]; }

  private:
    int _n, _size, _log;
    std::vector<T> data;
    std::vector<U> lazy;

    void update(int k) { data[k] = S::op(data[2 * k], data[2 * k + 1]); }
    void all_apply(int k, U f) {
        data[k] = F::f(f, data[k]);
        if (k < _size) lazy[k] = F::op(f, lazy[k]);
    }
    void push(int k) {
        all_apply(2 * k, lazy[k]);
        all_apply(2 * k + 1, lazy[k]);
        lazy[k] = F::id;
    }
};
