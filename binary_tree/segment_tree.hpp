#include "_base.hpp"

/*
 * 一点更新、区間取得
 * Usage:
 * segment_tree st(n, INF, [](ll a, ll b) { return min(a, b); });
 * segment_tree st(n, 0, [](ll a, ll b) { return max(a, b); });
 */
template <class T, class F>
struct segment_tree {
    int N;
    T e;
    F f;
    vector<T> data;

    segment_tree(int _n, T _e, F _f) : f(_f), e(_e) { init(_n); }

    const T &operator[](int i) const { return data[i + N]; }
    T &operator[](int i) { return data[i + N]; }

    T at(int k) const { return data[k + N]; }

    void init(int n) {
        for (N = 1; N < n; N <<= 1)
            ;
        data.assign(N * 2, e);
    }

    template <class U>
    void build(vector<U> v) {
        for (int i = 0; i < v.size(); ++i) data[N + i] = v[i];
        for (int i = N - 1; i >= 1; --i)
            data[i] = f(data[i * 2], data[i * 2 + 1]);
    }

    void update(int k, T x) {
        assert(k >= 0 && k < N);
        k += N;
        data[k] = x;
        while ((k >>= 1) >= 1) data[k] = f(data[k * 2], data[k * 2 + 1]);
    }

    void add(int k, T x) {
        assert(k >= 0 && k < N);
        k += N;
        data[k] += x;
        while ((k >>= 1) >= 1) data[k] = f(data[k * 2], data[k * 2 + 1]);
    }

    T query(int a, int b) {
        assert(a >= 0 && a <= N);
        assert(b >= 0 && b <= N);
        T res = e;
        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {
            if (a & 1) res = f(data[a++], res);
            if (b & 1) res = f(res, data[--b]);
        }
        return res;
    }
};
