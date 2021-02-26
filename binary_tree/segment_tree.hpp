#include "_base.hpp"

/*
 * セグメント木
 * Usage:
 * segment_tree st(n, INF, [](ll a, ll b) { return min(a, b); });
 * segment_tree st(n, 0, [](ll a, ll b) { return max(a, b); });
 */
template <class T, class F>
struct segment_tree {
    int N;
    const T e;
    const F op;
    vector<T> data;

    segment_tree(int _n, const T &_e, const F &_op) : e(_e), op(_op) {
        init(_n);
    }

    const T &operator[](int i) const { return data[i + N]; }
    T &operator[](int i) { return data[i + N]; }

    T at(int k) const { return data[k + N]; }

    void init(int n) {
        for (N = 1; N < n; N <<= 1)
            ;
        data.assign(N << 1, e);
    }

    template <class U>
    void build(const vector<U> &v) {
        for (int i = 0; i < v.size(); ++i) data[N + i] = T(v[i]);
        for (int i = N - 1; i >= 1; --i)
            data[i] = op(data[i * 2], data[i * 2 + 1]);
    }

    void update(int k, const T &x) {
        assert(k >= 0 && k < N);
        data[k += N] = x;
        while ((k >>= 1) >= 1) data[k] = op(data[k * 2], data[k * 2 + 1]);
    }

    void add(int k, const T &x) {
        assert(k >= 0 && k < N);
        data[k += N] += x;
        while ((k >>= 1) >= 1) data[k] = op(data[k * 2], data[k * 2 + 1]);
    }

    T query(int a, int b) {
        assert(a >= 0 && a <= N);
        assert(b >= 0 && b <= N);
        T l = e, r = e;
        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = op(l, data[a++]);
            if (b & 1) r = op(data[--b], r);
        }
        return op(l, r);
    }
};
