#include "template/template.hpp"

/*
 * セグメント木
 * Usage:
 * segment_tree st(n, Inf, [](auto a, auto b) { return min(a, b); });
 * segment_tree st(n, 0, [](auto a, auto b) { return max(a, b); });
 */
template <class T, class F>
struct segment_tree {
    int N;
    const T e;
    const F op;
    vector<T> data;

    segment_tree() {}
    segment_tree(int _n, T _e, F &&_op) : e(_e), op(_op) { init(_n); }

    const T &operator[](int i) const { return this->data[i + N]; }
    T at(int k) const {
        assert(0 <= k && k < N);
        return this->data[k + N];
    }
    T get(int k) const { return this->at(k); }

    void init(int n) {
        for (N = 1; N < n; N <<= 1)
            ;
        this->data.assign(N << 1, e);
    }

    template <class U>
    void build(const vector<U> &v) {
        int n = v.size();
        for (int i = 0; i < n; ++i) this->data[N + i] = T(v[i]);
        for (int i = N - 1; i >= 1; --i)
            this->data[i] = this->op(data[i * 2], this->data[i * 2 + 1]);
    }

    void update(int k, T x) {
        assert(0 <= k && k < N);
        this->data[k += N] = x;
        while ((k >>= 1) >= 1)
            this->data[k] = this->op(this->data[k * 2], this->data[k * 2 + 1]);
    }
    void add(int k, T x) { this->update(k, x - this->at(k)); }

    bool chmax(int k, T x) {
        if (this->at(k) >= x) return false;
        this->update(k, x);
        return true;
    }
    bool chmin(int k, T x) {
        if (this->at(k) <= x) return false;
        this->update(k, x);
        return true;
    }

    T query() const { return this->data[1]; }
    T query(int a, int b) const {
        assert(0 <= a && a <= N);
        assert(0 <= b && b <= N);
        T l = e, r = e;
        for (a += N, b += N; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = this->op(l, this->data[a++]);
            if (b & 1) r = this->op(this->data[--b], r);
        }
        return this->op(l, r);
    }
};
