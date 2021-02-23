#include "_base.hpp"
#include "binary_tree/BIT.hpp"

// 区間加算、区間取得
template <class T>
struct BIT_RSQ {
    BIT<T> p, q;

    BIT_RSQ(int n) { init(n); }

    void init(int n) {
        p.init(n + 1);
        q.init(n + 1);
    }

    const T &operator[](int i) const { return at(i); }

    // v[k]
    const T at(int k) const { return sum(k + 1) - sum(k); }

    template <class U>
    void build(const vector<U> &v) {
        for (int i = 0; i < v.size(); ++i) {
            p.add(i, v[i]);
            p.add(i + 1, -v[i]);
        }
    }

    void update(int k, cosnt T x) { add(k, k + 1, x - at(k)); }

    // v[k] += w
    void add(int k, T w) { add(k, k + 1, w); }
    // v[a ... b - 1] += w
    void add(int a, int b, T w) {
        p.add(a, -w * a);
        p.add(b, w * b);
        q.add(a, w);
        q.add(b, -w);
    }

    // v[0] + ... + v[k - 1]
    const T sum(int k) const { return p.sum(k) + q.sum(k) * k; }

    // v[a] + ... + v[b - 1]
    const T sum(int a, int b) const { return sum(b) - sum(a); }
};
