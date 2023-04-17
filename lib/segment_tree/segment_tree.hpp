#pragma once
#include "math/pow.hpp"
#include "segment_tree/monoid.hpp"
#include "template/template.hpp"

/**
 * @brief セグメント木
 * @see https://noshi91.hatenablog.com/entry/2020/04/22/212649
 *
 * @tparam M モノイド
 */
template <class M>
struct segment_tree {
  private:
    using T = typename M::value_type;

  public:
    segment_tree() : segment_tree(0) {}
    explicit segment_tree(int n, T e = M::id) : segment_tree(std::vector<T>(n, e)) {}
    template <class U>
    explicit segment_tree(const std::vector<U> &v) : _n(v.size()) {
        this->_log = ceil_pow2(this->_n);
        this->_size = 1 << this->_log;
        this->data = std::vector<T>(this->_size << 1, M::id);
        for (int i = 0; i < this->_n; ++i) this->data[this->_size + i] = T(v[i]);
        for (int i = this->_size - 1; i >= 1; --i) this->update(i);
    }

    const T &operator[](int k) const { return this->data[k + this->_size]; }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }

    void set(int k, T val) {
        assert(0 <= k && k < this->_n);
        k += this->_size;
        this->data[k] = val;
        for (int i = 1; i <= this->_log; ++i) this->update(k >> i);
    }
    void reset(int k) { this->set(k, M::id); }

    T all_prod() const { return this->data[1]; }
    T prod(int a, int b) const {
        assert(0 <= a && b <= this->_n);
        T l = M::id, r = M::id;
        for (a += this->_size, b += this->_size; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = M::op(l, this->data[a++]);
            if (b & 1) r = M::op(this->data[--b], r);
        }
        return M::op(l, r);
    }

    template <class F>
    int max_right(F f) const {
        return this->max_right(0, f);
    }

    template <class F>
    int max_right(int l, F f) const {
        assert(0 <= l && l <= this->_n);
        assert(f(M::id));
        if (l == this->_n) return this->_n;
        l += this->_size;
        T sm = M::id;
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(M::op(sm, this->data[l]))) {
                while (l < this->_size) {
                    l = (2 * l);
                    if (f(M::op(sm, this->data[l]))) {
                        sm = M::op(sm, this->data[l]);
                        l++;
                    }
                }
                return l - this->_size;
            }
            sm = M::op(sm, this->data[l]);
            l++;
        } while ((l & -l) != l);
        return this->_n;
    }

    int max_right(T x) const { return this->max_right(0, x); }

    int max_right(int l, T x) const {
        return this->max_right(l, [&x](auto y) {
            return !(y < x);
        });
    }

    template <class F>
    int min_left(F f) const {
        return this->min_left(this->_n, f);
    }

    template <class F>
    int min_left(int r, F f) const {
        assert(0 <= r && r <= this->_n);
        assert(f(M::id));
        if (r == 0) return 0;
        r += this->_size;
        T sm = M::id;
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(M::op(this->data[r], sm))) {
                while (r < this->_size) {
                    r = (2 * r + 1);
                    if (f(M::op(this->data[r], sm))) {
                        sm = M::op(this->data[r], sm);
                        r--;
                    }
                }
                return r + 1 - this->_size;
            }
            sm = M::op(this->data[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

    int min_left(T x) const { return this->min_left(this->_n, x); }

    int min_left(int r, T x) const {
        return this->min_left(r, [&x](auto y) {
            return !(y < x);
        });
    }

  private:
    int _n, _size, _log;
    std::vector<T> data;

    void update(int k) { this->data[k] = M::op(this->data[2 * k], this->data[2 * k + 1]); }
};
