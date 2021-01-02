#include "_base.hpp"

/*
区間代入、一点取得
Usage:
    segment_tree<ll> st(n, LINF);
    segment_tree<ll> st(n, 0);
*/
template <class T>
struct segment_tree {
    int64_t N;
    T d;
    vector<T> data;

    segment_tree(int64_t _n, T _d) : d(_d) {
        init(_n);
    }

    void init(int64_t n) {
        N = 1;
        while(N < n) N <<= 1;
        data.assign(N * 2, d);
    }

    void build(vector<T> v) {
        for (int64_t i = 0; i < v.size(); ++i) data[N + i] = v[i];
    }

    void update(int64_t a, T x) {
        update(a, a + 1, 1, 0, N, x);
    }
    void update(int64_t a, int64_t b, T x) {
        update(a, b, 1, 0, N, x);
    }
    void update(int64_t a, int64_t b, int64_t k, int64_t l, int64_t r, T x) {
        if (a <= l && r <= b) {
            data[k] = x;
            return;
        }
        if (r <= a || b <= l) return;
        ll m = (l + r) / 2;
        if (data[k] != d) {
            data[k * 2] = data[k];
            data[k * 2 + 1] = data[k];
            data[k] = d;
        }
        udpate(a, b, k * 2, l, m, x);
        update(a, b, k * 2 + 1, m, r, x));
    }

    T at(int64_t k) {
        k += N;
        T res = data[k];
        while (k > 1) {
            k >>= 1;
            if (data[k] != d) res = data[k];
        }
        return res;
    }
};
