#include "_base.hpp"

/*
Usage:
    dual_segment_tree<ll> RAQ(n, LINF, [](ll a, ll x){return a + x;});
    dual_segment_tree<ll> RUQ(n, 0, [](ll a, ll x){return x;});
*/
template <class T>
struct dual_segment_tree {
    using F = function<T(T, T)>;
    int64_t N;
    T d;
    F f;
    vector<T> data;

    dual_segment_tree(int64_t _n, T _d, F _f) : f(_f), d(_d) { init(_n); }

    void init(int64_t n) {
        for (N = 1; N < n; N <<= 1)
            ;
        data.assign(N * 2, d);
    }

    void build(const vector<T> &v) {
        for (int64_t i = 0; i < v.size(); ++i) data[N + i] = v[i];
    }

    void update(int64_t a, T x) {
        int k = 0;
        while (a >> k > 1) ++k;
        for (; k > 0; --k) {
            int64_t t = a >> k;
            if (data[t] == d) continue;
            data[t * 2] = f(data[t * 2], data[t]);
            data[t * 2 + 1] = f(data[t * 2 + 1], data[t]);
            data[t] = d;
        }
        data[a] = f(data[a], x);
    }

    void query(int64_t a, T x) { query(a, a + 1, 1, 0, N, x); }
    void query(int64_t a, int64_t b, T x) {
        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {
            if (a & 1) update(a++, x);
            if (b & 1) update(--b, x);
        }
    }

    const T at(int64_t k) const {
        T res = d;
        for (k += N; k >= 1; k >>= 1) {
            if (data[k] != d) res = f(res, data[k]);
        }
        return res;
    }
};
