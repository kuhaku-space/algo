#include "template/template.hpp"

// 一点加算、区間総和
template <class T>
struct BIT {
    int N;
    vector<T> data;

    BIT() {}
    BIT(int n, T e = T(0)) : N(n + 1), data(n + 1, e) {}
    BIT(const vector<T> &v) : N(v.size() + 1), data(v.size() + 1) {
        this->build(v);
    }

    const T &operator[](int i) const { return this->at(i); }
    const T at(int k) const { return this->sum(k + 1) - this->sum(k); }
    const T get(int k) const { return this->sum(k + 1) - this->sum(k); }

    template <class U>
    void build(const vector<U> &v) {
        int n = v.size();
        for (int i = 0; i < n; ++i) this->add(i, v[i]);
    }

    // v[k] = x
    void update(int k, T x) { this->add(k, x - this->at(k)); }
    // v[k] += x
    void add(int k, T x) {
        assert(0 <= k && k < N);
        for (++k; k < N; k += k & -k) data[k] += x;
    }
    // chmax(v[k], x)
    bool chmax(int k, T x) {
        if (this->at(k) >= x) return false;
        this->update(k, x);
        return true;
    }
    // chmin(v[k], x)
    bool chmin(int k, T x) {
        if (this->at(k) <= x) return false;
        this->update(k, x);
        return true;
    }

    // v[0] + ... + v[k - 1]
    T sum(int k) const {
        assert(0 <= k && k <= N);
        T res = 0;
        for (; k > 0; k -= k & -k) res += data[k];
        return res;
    }
    // v[a] + ... + v[b - 1]
    T sum(int a, int b) const { return this->sum(b) - this->sum(a); }

    int lower_bound(T x) const {
        if (x <= 0) return 0;
        int k = 0;
        while (k < N) k <<= 1;
        int res = 0;
        for (; k > 0; k >>= 1) {
            if (res + k < N && data[res + k] < x) x -= data[res += k];
        }
        return res;
    }
};
