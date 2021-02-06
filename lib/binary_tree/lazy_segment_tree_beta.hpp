#include "_base.hpp"

/*
Usage:
    lazy_segment_tree RAQ_RmQ(n, INF, [](ll a, ll b){ return min(a, b); });
    lazy_segment_tree RAQ_RMQ(n, 0, [](ll a, ll b){ return max(a, b); });
*/
template <class T, class F>
struct lazy_segment_tree {
    int64_t N, logN;
    T e;
    F f;
    vector<T> data;
    vector<T> lazy;

    lazy_segment_tree(int64_t _n, T _e, F _f) : f(_f), e(_e) { init(_n); }

    void init(int64_t n) {
        for (N = 1, logN = 0; N < n; N <<= 1, ++logN)
            ;
        data.assign(N * 2, e);
        lazy.assign(N * 2, 0);
    }

    void build(const vector<T> &v) {
        for (int64_t i = 0; i < v.size(); ++i) data[N + i] = v[i];
        for (int64_t i = N - 1; i >= 1; --i)
            data[i] = f(data[i * 2], data[i * 2 + 1]);
    }

    void update(int64_t k, T x) {
        lazy[k] += x;

        while ((k >>= 1) >= 1) {
            data[k] =
                f(data[k * 2] + lazy[k * 2], data[k * 2 + 1] + lazy[k * 2 + 1]);
        }
    }

    T eval(int64_t k) {
        if (lazy[k] == 0) return data[k];
        if (k < N) {
            lazy[k * 2] += lazy[k];
            lazy[k * 2 + 1] += lazy[k];
        }
        data[k] += lazy[k];
        lazy[k] = 0;
        return data[k];
    }

    void add(int64_t a, T x) { return add(a, a + 1, x); }
    void add(int64_t a, int64_t b, T x) {
        assert(a >= 0 && a <= N);
        assert(b >= 0 && b <= N);
        a += N, b += N;
        for (int64_t i = logN; i >= 0; --i) eval(a >> i), eval(b >> i);
        for (; a < b; a >>= 1, b >>= 1) {
            if (a & 1) eval(a), update(a++, x);
            if (b & 1) eval(--b), update(b, x);
        }
    }

    T query(int64_t a, int64_t b) {
        assert(a >= 0 && a <= N);
        assert(b >= 0 && b <= N);
        a += N, b += N;
        for (int64_t i = logN; i >= 0; --i) eval(a >> i), eval(b >> i);
        T res = e;
        for (; a < b; a >>= 1, b >>= 1) {
            if (a & 1) res = f(eval(a++), res);
            if (b & 1) res = f(res, eval(--b));
        }
        return res;
    }
};
