#include "template/template.hpp"

template <class T, class U, class F, class G, class H>
struct lazy_segment_tree {
    int N, logN;
    const T e;
    const U id;
    const F op;    // (T, T) -> T
    const G mapp;  // (U, T) -> T
    const H comp;  // (U, U) -> U
    vector<T> data;
    vector<U> lazy;

    lazy_segment_tree(int _n, T _e, U _id, F &&_op, G &&_mapp, H &&_comp)
        : e(_e), id(_id), op(_op), mapp(_mapp), comp(_comp) {
        init(_n);
    }
    lazy_segment_tree(int _n, T _e, U _id, const F &_op, const G &_mapp, const H &_comp)
        : e(_e), id(_id), op(_op), mapp(_mapp), comp(_comp) {
        init(_n);
    }

    void init(int n) {
        for (N = 1, logN = 0; N < n; N <<= 1, ++logN) {}
        data.assign(N << 1, e);
        lazy.assign(N << 1, id);
    }

    template <class V>
    void build(const vector<V> &v) {
        for (int i = 0; i < v.size(); ++i) data[N + i] = v[i];
        for (int i = N - 1; i >= 1; --i) data[i] = op(data[i * 2], data[i * 2 + 1]);
    }

    void apply(int k, const U &x) {
        assert(0 < k && k < N << 1);
        lazy[k] = comp(x, lazy[k]);

        if ((k >>= 1) >= 1) {
            data[k] = op(mapp(lazy[k * 2], data[k * 2]), mapp(lazy[k * 2 + 1], data[k * 2 + 1]));
        }
    }

    T eval(int k) {
        assert(0 < k && k < N << 1);
        if (lazy[k] == id) return data[k];
        if (k < N) {
            lazy[k * 2] = comp(lazy[k], lazy[k * 2]);
            lazy[k * 2 + 1] = comp(lazy[k], lazy[k * 2 + 1]);
        }
        data[k] = mapp(lazy[k], data[k]);
        lazy[k] = id;
        return data[k];
    }

    void update(int a, const U &x) { return add(a, a + 1, x); }
    void update(int a, int b, const U &x) {
        assert(0 <= a && a <= N);
        assert(0 <= b && b <= N);
        int l = a + N, r = b + N - 1;
        for (int i = logN; i >= 0; --i) eval(l >> i), eval(r >> i);
        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {
            if (a & 1) eval(a), apply(a++, x);
            if (b & 1) eval(--b), apply(b, x);
        }
        for (int i = 0; i <= logN; ++i) apply(l >> i, id), apply(r >> i, id);
    }

    T query(int a, int b) {
        assert(0 <= a && a <= N);
        assert(0 <= b && b <= N);
        a += N, b += N;
        for (int i = logN; i >= 0; --i) eval(a >> i), eval((b - 1) >> i);
        T l = e, r = e;
        for (; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = op(l, eval(a++));
            if (b & 1) r = op(eval(--b), r);
        }
        return op(l, r);
    }
};
