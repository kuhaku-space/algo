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
    T e;
    F f;
    vector<T> data;

    segment_tree(int64_t _n, T _e, F _f) : f(_f), e(_e) { init(_n); }
    segment_tree(int64_t _n, string _s) {
        switch (_s) {
            case "min":
                e = LINF;
                f = [](int64_t a, int64_t b) { return min(a, b) };
                break;
            case "max":
                e = -LINF;
                f = [](int64_t a, int64_t b) { return max(a, b) };
            default:
                break;
        }
        init(_n);
    }

    const T &operator[](const int64_t i) const { return data[i + N]; }
    T &operator[](const int64_t i) { return data[i + N]; }

    T at(int64_t k) const { return data[k + N]; }

    void init(int64_t n) {
        N = 1;
        while (N < n) N <<= 1;
        data.assign(N * 2, e);
    }

    void build(vector<T> v) {
        for (int64_t i = 0; i < v.size(); ++i) data[N + i] = v[i];
        for (int64_t i = N - 1; i >= 1; --i)
            data[i] = f(data[i * 2], data[i * 2 + 1]);
    }

    void update(int64_t k, const T x) {
        assert(k >= 0 && k < N);
        k += N;
        data[k] = x;
        for (k >>= 1; k > 1; k >>= 1) data[k] = f(data[k * 2], data[k * 2 + 1]);
    }

    void add(int64_t k, const T x) {
        assert(k >= 0 && k < N);
        k += N;
        data[k] += x;
        for (k >>= 1; k > 1; k >>= 1) data[k] = f(data[k * 2], data[k * 2 + 1]);
    }

    T query(int64_t a, int64_t b) {
        assert(a >= 0 && a < N);
        assert(b >= 0 && b < N);
        T res = e;
        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {
            if (a & 1) res = f(data[a++], res);
            if (b & 1) res = f(res, data[--b]);
        }
        return res;
    }
};
