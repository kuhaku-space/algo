#include "template/template.hpp"

/**
 * @brief セグメント木
 *
 * @tparam T 要素の型
 * @tparam F 関数の型
 */
template <class T>
struct segment_tree {
    int N;
    const T e;
    vector<T> data;

    segment_tree() {}
    segment_tree(int _n, T _e) : e(_e) { this->init(_n, _e); }

    const T &operator[](int i) const { return this->data[i + this->N]; }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }

    void init(int n, const T val) {
        for (this->N = 1; this->N < n; this->N <<= 1) {}
        this->data.assign(this->N << 1, val);
    }

    template <class U>
    void build(const vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) this->data[this->N + i] = T(v[i]);
        for (int i = this->N - 1; i >= 1; --i)
            this->data[i] = this->op(this->data[i * 2], this->data[i * 2 + 1]);
    }

    void apply(int k, T val) {
        assert(0 <= k && k < this->N);
        k += this->N;
        this->data[k] = f(val, this->data[k]);
        while ((k >>= 1) >= 1) this->data[k] = this->op(this->data[k * 2], this->data[k * 2 + 1]);
    }

    T all_prod() const { return this->data[1]; }
    T prod(int a, int b) const {
        assert(0 <= a && b <= this->N);
        T l = e, r = e;
        for (a += this->N, b += this->N; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = this->op(l, this->data[a++]);
            if (b & 1) r = this->op(this->data[--b], r);
        }
        return this->op(l, r);
    }

  protected:
    virtual T op(T a, T b) const = 0;
    virtual T f(T val, T x) const = 0;
};
