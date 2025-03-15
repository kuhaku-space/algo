#pragma once
#include <bit>
#include <cassert>
#include <vector>
#include "segtree/monoid.hpp"

/// @brief セグメント木
/// @see https://noshi91.hatenablog.com/entry/2020/04/22/212649
template <class M>
struct segment_tree {
  private:
    using T = typename M::value_type;

    struct _segment_tree_reference {
      private:
        segment_tree<M> &self;
        int k;

      public:
        _segment_tree_reference(segment_tree<M> &self, int k) : self(self), k(k) {}
        _segment_tree_reference &operator=(const T &x) {
            self.set(k, x);
            return *this;
        }
        _segment_tree_reference &operator=(T &&x) {
            self.set(k, std::move(x));
            return *this;
        }
        operator T() const { return self.get(k); }
    };

  public:
    segment_tree() : segment_tree(0) {}
    explicit segment_tree(int n, T e = M::id()) : segment_tree(std::vector<T>(n, e)) {}
    template <class U>
    explicit segment_tree(const std::vector<U> &v) : _n(v.size()) {
        _size = std::bit_ceil<unsigned>(_n);
        _log = std::countr_zero<unsigned>(_size);
        data = std::vector<T>(_size << 1, M::id());
        for (int i = 0; i < _n; ++i) data[_size + i] = T(v[i]);
        for (int i = _size - 1; i >= 1; --i) update(i);
    }

    const T &operator[](int k) const { return data[k + _size]; }
    _segment_tree_reference operator[](int k) { return _segment_tree_reference(*this, k); }
    T at(int k) const { return data[k + _size]; }
    T get(int k) const { return data[k + _size]; }

    void set(int k, T val) {
        assert(0 <= k && k < _n);
        k += _size;
        data[k] = val;
        for (int i = 1; i <= _log; ++i) update(k >> i);
    }
    void reset(int k) { set(k, M::id()); }

    T all_prod() const { return data[1]; }
    T prod(int a, int b) const {
        assert(0 <= a && b <= _n);
        T l = M::id(), r = M::id();
        for (a += _size, b += _size; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = M::op(l, data[a++]);
            if (b & 1) r = M::op(data[--b], r);
        }
        return M::op(l, r);
    }

    template <class F>
    int max_right(F f) const {
        return max_right(0, f);
    }

    template <class F>
    int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(M::id()));
        if (l == _n) return _n;
        l += _size;
        T sm = M::id();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(M::op(sm, data[l]))) {
                while (l < _size) {
                    l = (2 * l);
                    if (f(M::op(sm, data[l]))) {
                        sm = M::op(sm, data[l]);
                        l++;
                    }
                }
                return l - _size;
            }
            sm = M::op(sm, data[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <class F>
    int min_left(F f) const {
        return min_left(_n, f);
    }

    template <class F>
    int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(M::id()));
        if (r == 0) return 0;
        r += _size;
        T sm = M::id();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(M::op(data[r], sm))) {
                while (r < _size) {
                    r = (2 * r + 1);
                    if (f(M::op(data[r], sm))) {
                        sm = M::op(data[r], sm);
                        r--;
                    }
                }
                return r + 1 - _size;
            }
            sm = M::op(data[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, _size, _log;
    std::vector<T> data;

    void update(int k) { data[k] = M::op(data[2 * k], data[2 * k + 1]); }
};
