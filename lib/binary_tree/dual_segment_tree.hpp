#include "template/template.hpp"

/*
 * 双対セグメント木
 * Usage:
 * dual_segment_tree RAQ(n, INF, [](ll a, ll x){ return a + x; }; );
 * dual_segment_tree RUQ(n, 0, [](ll a, ll x){ return x; }; );
 */
template <class T, class F>
struct dual_segment_tree {
    int N;
    T e;
    F op;
    vector<T> data;

    dual_segment_tree(int _n, T _e, F _op) : e(_e), op(_op) { init(_n); }

    void init(int n) {
        for (N = 1; N < n; N <<= 1)
            ;
        data.assign(N << 1, e);
    }

    template <class U>
    void build(const vector<U> &v) {
        for (int i = 0; i < v.size(); ++i) data[N + i] = v[i];
        for (int i = N - 1; i >= 1; --i)
            data[i] = op(data[i * 2], data[i * 2 + 1]);
    }

    void update(int a, T x) {
        int k = 0;
        while (a >> k > 1) ++k;
        for (; k > 0; --k) {
            int t = a >> k;
            if (data[t] == e) continue;
            data[t * 2] = op(data[t * 2], data[t]);
            data[t * 2 + 1] = op(data[t * 2 + 1], data[t]);
            data[t] = e;
        }
        data[a] = op(data[a], x);
    }

    void query(int a, T x) { query(a, a + 1, 1, 0, N, x); }
    void query(int a, int b, T x) {
        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {
            if (a & 1) update(a++, x);
            if (b & 1) update(--b, x);
        }
    }

    const T at(int k) const {
        T res = e;
        for (k += N; k >= 1; k >>= 1) {
            if (data[k] != e) res = op(res, data[k]);
        }
        return res;
    }
};
