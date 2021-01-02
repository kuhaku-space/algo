#include "_base.hpp"

/*
一点更新、区間取得
Usage:
    segment_tree<ll> st(n, LINF, [](ll a, ll b) { return min(a, b); });
    segment_tree<ll> st(n, 0, [](ll a, ll b) { return max(a, b); });
*/
template <class T>
struct segment_tree {
    using F = function<T(T, T)>;
    int64_t N;
    T d;
    F f;
    vector<T> data;

    segment_tree(int64_t _n, T _d, F _f) : f(_f), d(_d) {
        init(_n);
    }

    const T &operator[](const int64_t i) const {
        return data[i + N];
    }
    T &operator[](const int64_t i) {
        return data[i + N];
    }

    T at(int64_t k) const {
        return data[k + N];
    }

    void init(int64_t n) {
        N = 1;
        while (N < n) N <<= 1;
        data.assign(N * 2, d);
    }

    void build(vector<T> v) {
        for (int64_t i = 0; i < v.size(); ++i) data[N + i] = v[i];
        for (int64_t i = N - 1; i >= 1; --i) data[i] = f(data[i * 2], data[i * 2 + 1]);
    }

    void update(int64_t k, const T x) {
        k += N;
        data[k] = x;
        while (k > 1) {
            k >>= 1;
            data[k] = f(data[k * 2], data[k * 2 + 1]);
        }
    }

    void add(int64_t k, const T x) {
        k += N;
        data[k] += x;
        while (k > 1) {
            k >>= 1;
            data[k] = f(data[k * 2], data[k * 2 + 1]);
        }
    }

    T query(int64_t a, int64_t b) {
        T res = d;
        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {
            if (a & 1) res = f(res, data[a++]);
            if (b & 1) res = f(res, data[--b]);
        }
        return res;
    }
};
