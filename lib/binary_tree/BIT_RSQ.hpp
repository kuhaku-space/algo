#include "lib/template/template.hpp"
#include "binary_tree/BIT.hpp"

template <class T>
struct BIT_RSQ {
    BIT<T> p, q;

    BIT_RSQ(int n) : p(n), q(n) {}

    void init(int n) {
        p = BIT<T>(n);
        q = BIT<T>(n);
    }

    auto operator[](int i) const { return this->at(i); }

    // v[k]
    auto at(int k) const { return this->sum(k + 1) - this->sum(k); }

    template <class U>
    void build(const vector<U> &v) {
        int n = v.size();
        for (int i = 0; i < n; ++i) {
            p.add(i, v[i]);
            p.add(i + 1, -v[i]);
        }
    }

    void update(int k, T x) { this->add(k, k + 1, x - this->at(k)); }

    // v[k] += w
    void add(int k, T w) { this->add(k, k + 1, w); }
    // v[a ... b - 1] += w
    void add(int a, int b, T w) {
        p.add(a, -w * a);
        p.add(b, w * b);
        q.add(a, w);
        q.add(b, -w);
    }

    // v[0] + ... + v[k - 1]
    auto sum(int k) const { return p.sum(k) + q.sum(k) * k; }

    // v[a] + ... + v[b - 1]
    auto sum(int a, int b) const { return this->sum(b) - this->sum(a); }
};
