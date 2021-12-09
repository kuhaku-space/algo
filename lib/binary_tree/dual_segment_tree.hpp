#include "template/template.hpp"

/**
 * @brief 双対セグメント木
 *
 * @details Usage: @n
 * dual_segment_tree RAQ(n, INF, [](ll a, ll x){ return a + x; } ); @n
 * dual_segment_tree RUQ(n, 0, [](ll a, ll x){ return x; } );
 *
 * @tparam T 要素の型
 * @tparam F 関数の型
 */
template <class T, class F>
struct dual_segment_tree {
    int N;
    T e;
    F op;
    vector<T> data;

    dual_segment_tree(int _n, T _e, const F &_op) : e(_e), op(_op) { this->init(_n); }
    dual_segment_tree(int _n, T _e, F &&_op) : e(_e), op(_op) { this->init(_n); }

    void init(int n) {
        for (this->N = 1; this->N < n; this->N <<= 1) {}
        this->data.assign(this->N << 1, e);
    }

    template <class U>
    void build(const vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) this->data[this->N + i] = v[i];
        for (int i = this->N - 1; i >= 1; --i)
            this->data[i] = this->op(this->data[i * 2], this->data[i * 2 + 1]);
    }

    void update(int k, T x) {
        assert(0 <= k && k < this->N);
        int l = 0;
        while (k >> l > 1) ++l;
        for (; l > 0; --l) {
            int t = k >> l;
            if (this->data[t] == e) continue;
            this->data[t * 2] = this->op(this->data[t * 2], this->data[t]);
            this->data[t * 2 + 1] = this->op(this->data[t * 2 + 1], this->data[t]);
            this->data[t] = e;
        }
        this->data[k] = this->op(this->data[k], x);
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
            if (this->data[k] != e) res = this->op(res, this->data[k]);
        }
        return res;
    }
    T get(int k) const { return this->at(k); }
};
