#include "_base.hpp"

/*
Usage:
    lazy_segment_tree<ll> lst(n, LINF, [](ll a, ll b){return min(a, b);});
    lazy_segment_tree<ll> lst(n, 0, [](ll a, ll b){return max(a, b);});
*/
template <class T>
struct dual_segment_tree{
    using F = function<T(T, T)>;
    int64_t N;
    T d;
    F f;
    vector<T> data;
    vector<T> lazy;

    dual_segment_tree(int64_t _n, T _d, F _f) : f(_f), d(_d) {
        init(_n);
    }

    void init(int64_t n){
        N = 1;
        while(N < n) N <<= 1;
        data.assign(N * 2, d);
        lazy.assign(N * 2, 0);
    }

    void build(vector<T> v){
        for (int64_t i = 0; i < v.size(); ++i) data[N + i] = v[i];
        for (int64_t i = N - 1; i >= 1; --i) data[i] = f(data[i * 2], data[i * 2 + 1]);
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

    T add(int64_t a, T x) {
        return add(a, a + 1, x, 1, 0, N);
    }
    T add(int64_t a, int64_t b, T x) {
        return add(a, b, x, 1, 0, N);
    }
    T add(int64_t a, int64_t b, T x, int64_t k, int64_t l, int64_t r) {
        eval(k);
        if(r <= a || b <= l) return data[k];
        if(a <= l && r <= b){
            lazy[k] += x;
            return data[k] + lazy[k];
        }
        int64_t m = (l + r) / 2;
        return data[k] =
                   f(add(a, b, x, k * 2, l, m), add(a, b, x, k * 2 + 1, m, r));
    }

    T at(int64_t k) {
        eval(k);
        return data[k + N];
    }
};
