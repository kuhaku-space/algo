#pragma once
#include "internal/internal_bit.hpp"
#include "segment_tree/monoid.hpp"
#include "template/template.hpp"

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
        this->data = std::vector<T>(2 * this->_size, S::id);
        this->lazy = std::vector<U>(this->_size, F::id);
        for (int i = 0; i < this->_n; i++) this->data[this->_size + i] = v[i];
        for (int i = this->_size - 1; i >= 1; --i) this->update(i);
    }

    void set(int p, T x) {
        assert(0 <= p && p < this->_n);
        p += this->_size;
        for (int i = this->_log; i >= 1; --i) this->push(p >> i);
        this->data[p] = x;
        for (int i = 1; i <= this->_log; ++i) this->update(p >> i);
    }

    T at(int p) { return this->get(p); }
    T get(int p) {
        assert(0 <= p && p < this->_n);
        p += this->_size;
        for (int i = this->_log; i >= 1; --i) this->push(p >> i);
        return this->data[p];
    }

    void apply(int p, U f) {
        assert(0 <= p && p < this->_n);
        p += this->_size;
        for (int i = this->_log; i >= 1; --i) this->push(p >> i);
        this->data[p] = F::f(f, this->data[p]);
        for (int i = 1; i <= this->_log; ++i) this->update(p >> i);
    }
    void apply(int l, int r, U f) {
        assert(0 <= l && l <= r && r <= this->_n);
        if (l == r) return;

        l += this->_size, r += this->_size;

        for (int i = this->_log; i >= 1; --i) {
            if (((l >> i) << i) != l) this->push(l >> i);
            if (((r >> i) << i) != r) this->push((r - 1) >> i);
        }

        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) this->all_apply(l++, f);
            if (r & 1) this->all_apply(--r, f);
            l >>= 1, r >>= 1;
        }
        l = l2, r = r2;

        for (int i = 1; i <= this->_log; i++) {
            if (((l >> i) << i) != l) this->update(l >> i);
            if (((r >> i) << i) != r) this->update((r - 1) >> i);
        }
    }

    T prod(int l, int r) {
        assert(0 <= l && l <= r && r <= this->_n);
        if (l == r) return S::id;

        l += this->_size, r += this->_size;

        for (int i = this->_log; i >= 1; --i) {
            if (((l >> i) << i) != l) this->push(l >> i);
            if (((r >> i) << i) != r) this->push((r - 1) >> i);
        }

        T sml = S::id, smr = S::id;
        while (l < r) {
            if (l & 1) sml = S::op(sml, this->data[l++]);
            if (r & 1) smr = S::op(this->data[--r], smr);
            l >>= 1, r >>= 1;
        }

        return S::op(sml, smr);
    }

    T all_prod() const { return this->data[1]; }

  private:
    int _n, _size, _log;
    std::vector<T> data;
    std::vector<U> lazy;

    void update(int k) { this->data[k] = S::op(this->data[2 * k], this->data[2 * k + 1]); }
    void all_apply(int k, U f) {
        this->data[k] = F::f(f, this->data[k]);
        if (k < _size) this->lazy[k] = F::op(f, this->lazy[k]);
    }
    void push(int k) {
        this->all_apply(2 * k, this->lazy[k]);
        this->all_apply(2 * k + 1, this->lazy[k]);
        this->lazy[k] = F::id;
    }
};
