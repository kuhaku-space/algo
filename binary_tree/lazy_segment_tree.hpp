#include "_base.hpp"

/*
 * Usage:
 * lazy_segment_tree RAQ_RmQ(n, INF, [](ll a, ll b){ return min(a, b); });
 * lazy_segment_tree RAQ_RMQ(n, 0, [](ll a, ll b){ return max(a, b); });
 */
template <class T, class F>
struct lazy_segment_tree {
    int64_t N;
    T e;
    F f;
    vector<T> data;
    vector<T> lazy;

    lazy_segment_tree(int64_t _n, T _e, F _f) : f(_f), e(_e) { init(_n); }

    void init(int64_t n) {
        for (N = 1; N < n; N <<= 1)
            ;
        data.assign(N * 2, e);
        lazy.assign(N * 2, 0);
    }

    template <class U>
    void build(const vector<U> &v) {
        for (int64_t i = 0; i < v.size(); ++i) data[N + i] = v[i];
        for (int64_t i = N - 1; i >= 1; --i)
            data[i] = f(data[i * 2], data[i * 2 + 1]);
    }

    void eval(int64_t k) {
        if (lazy[k] == 0) return;
        if (k < N) {
            lazy[k * 2] += lazy[k];
            lazy[k * 2 + 1] += lazy[k];
        }
        data[k] += lazy[k];
        lazy[k] = 0;
    }

    T add(int64_t a, T x) { return add(a, a + 1, x, 1, 0, N); }
    T add(int64_t a, int64_t b, T x) { return add(a, b, x, 1, 0, N); }
    T add(int64_t a, int64_t b, T x, int64_t k, int64_t l, int64_t r) {
        eval(k);
        if (r <= a || b <= l) return data[k];
        if (a <= l && r <= b) {
            lazy[k] += x;
            return data[k] + lazy[k];
        }
        int64_t m = (l + r) / 2;
        return data[k] =
                   f(add(a, b, x, k * 2, l, m), add(a, b, x, k * 2 + 1, m, r));
    }

    T query(int64_t a, int64_t b) { return query(a, b, 1, 0, N); }
    T query(int64_t a, int64_t b, int64_t k, int64_t l, int64_t r) {
        eval(k);
        if (r <= a || b <= l) return e;
        if (a <= l && r <= b) return data[k];
        int64_t m = (l + r) / 2;
        return f(query(a, b, k * 2, l, m), query(a, b, k * 2 + 1, m, r));
    }
};
