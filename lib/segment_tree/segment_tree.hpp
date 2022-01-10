#include "math/pow.hpp"
#include "template/template.hpp"

/**
 * @brief セグメント木
 * @details [参考](https://noshi91.hatenablog.com/entry/2020/04/22/212649)
 *
 * @tparam M
 * @tparam F
 */
template <class M, class F>
struct segment_tree {
    using T = typename M::value_type;

    segment_tree() {}
    segment_tree(int n) { this->init(n, M::id); }
    segment_tree(int n, T e) { this->init(n, e); }

    const T &operator[](int i) const { return this->data[i + this->_size]; }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }

    void init(int n, const T val) {
        this->_size = ceil_pow2(n);
        this->data.assign(this->_size << 1, val);
    }

    template <class U>
    void build(const vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) this->data[this->_size + i] = T(v[i]);
        for (int i = this->_size - 1; i >= 1; --i)
            this->data[i] = M::op(this->data[i * 2], this->data[i * 2 + 1]);
    }

    template <class U>
    void apply(int k, U val) {
        assert(0 <= k && k < this->_size);
        k += this->_size;
        this->data[k] = F::f(val, this->data[k]);
        while ((k >>= 1) >= 1) this->data[k] = M::op(this->data[k * 2], this->data[k * 2 + 1]);
    }

    void set(int k, T val) {
        assert(0 <= k && k < this->_size);
        k += this->_size;
        this->data[k] = val;
        while ((k >>= 1) >= 1) this->data[k] = M::op(this->data[k * 2], this->data[k * 2 + 1]);
    }

    T all_prod() const { return this->data[1]; }
    T prod(int a, int b) const {
        assert(0 <= a && b <= this->_size);
        T l = M::id, r = M::id;
        for (a += this->_size, b += this->_size; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = M::op(l, this->data[a++]);
            if (b & 1) r = M::op(this->data[--b], r);
        }
        return M::op(l, r);
    }

  private:
    int _size;
    vector<T> data;
};

template <class T>
struct Sum {
    using value_type = T;
    static constexpr T id = 0;
    static T op(T l, T r) { return l + r; }
};

template <class T>
struct Min {
    using value_type = T;
    static constexpr T id = numeric_limits<T>::max();
    static T op(T l, T r) { return min(l, r); }
};

template <class T>
struct Max {
    using value_type = T;
    static constexpr T id = numeric_limits<T>::min();
    static T op(T l, T r) { return max(l, r); }
};

struct Add {
    template <class T, class U>
    static T f(U val, T x) {
        return val + x;
    }
};

struct Update {
    template <class T, class U>
    static T f(U val, T x) {
        return val;
    }
};

struct Chmin {
    template <class T, class U>
    static T f(U val, T x) {
        return min((T)val, x);
    }
};

struct Chmax {
    template <class T, class U>
    static T f(U val, T x) {
        return max((T)val, x);
    }
};
