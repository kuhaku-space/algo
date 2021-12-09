#include "template/template.hpp"

/**
 * @brief 双対セグメント木
 *
 * @details Usage: @n
 * dual_segment_tree RAQ(n, Inf, [](auto a, auto x){ return a + x; } ); @n
 * dual_segment_tree RUQ(n, Inf, [](auto a, auto x){ return a; } );
 *
 * @tparam T 要素の型
 * @tparam F 関数の型
 */
template <class T, class F>
struct dual_segment_tree {
    int N;
    T e;
    F f;
    vector<T> data;

    dual_segment_tree(int _n, T _e, const F &_f) : e(_e), f(_f) { this->init(_n); }
    dual_segment_tree(int _n, T _e, F &&_f) : e(_e), f(_f) { this->init(_n); }

    void init(int n) {
        for (this->N = 1; this->N < n; this->N <<= 1) {}
        this->data.assign(this->N << 1, e);
    }

    template <class U>
    void build(const vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) this->data[this->N + i] = v[i];
    }

    void update(int k, T x) {
        int l = 0;
        while (k >> l > 1) ++l;
        for (; l > 0; --l) {
            int t = k >> l;
            if (this->data[t] == e) continue;
            this->data[t * 2] = this->f(this->data[t], this->data[t * 2]);
            this->data[t * 2 + 1] = this->f(this->data[t], this->data[t * 2 + 1]);
            this->data[t] = e;
        }
        this->data[k] = this->f(x, this->data[k]);
    }
    void set(int k, T x) { this->update(k, x); }

    void appry(int k, T x) { this->query(k, k + 1, x); }
    void appry(int a, int b, T x) {
        assert(0 <= a && a <= this->N);
        assert(0 <= b && b <= this->N);
        for (a += this->N, b += this->N; a < b; a >>= 1, b >>= 1) {
            if (a & 1) this->update(a++, x);
            if (b & 1) this->update(--b, x);
        }
    }

    T at(int k) const {
        assert(0 <= k && k < this->N);
        T res = e;
        for (k += this->N; k >= 1; k >>= 1) {
            if (this->data[k] != e) res = this->f(this->data[k], res);
        }
        return res;
    }
    T get(int k) const { return this->at(k); }
};
