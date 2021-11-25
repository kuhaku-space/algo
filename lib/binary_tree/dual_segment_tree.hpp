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
        for (int i = 0; i < v.size(); ++i) this->data[this->N + i] = v[i];
        for (int i = N - 1; i >= 1; --i)
            this->data[i] = this->op(this->data[i * 2], this->data[i * 2 + 1]);
    }

    void update(int a, T x) {
        int k = 0;
        while (a >> k > 1) ++k;
        for (; k > 0; --k) {
            int t = a >> k;
            if (this->data[t] == e) continue;
            this->data[t * 2] = this->op(this->data[t * 2], this->data[t]);
            this->data[t * 2 + 1] = this->op(this->data[t * 2 + 1], this->data[t]);
            this->data[t] = e;
        }
        this->data[a] = this->op(this->data[a], x);
    }

    void query(int a, T x) { query(a, a + 1, x); }
    void query(int a, int b, T x) {
        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {
            if (a & 1) update(a++, x);
            if (b & 1) update(--b, x);
        }
    }

    T at(int k) const {
        T res = e;
        for (k += N; k >= 1; k >>= 1) {
            if (this->data[k] != e) res = this->op(res, this->data[k]);
        }
        return res;
    }
    T get(int k) const { return this->at(k); }
};
