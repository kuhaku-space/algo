#include "_base.hpp"

// 一点加算、区間総和
template <class T>
struct BIT {
    int N;
    vector<T> data;

    BIT() {}
    BIT(int n) { init(n); }
    BIT(const vector<T> &v) { build(v); }

    const T &operator[](int i) const { return at(i); }

    const T at(int k) const { return sum(k + 1) - sum(k); }

    void init() { data = vector<T>(N + 1); }

    void init(int n) {
        for (N = 1; N < n; N <<= 1)
            ;
        data = vector<T>(N + 1);
    }

    template <class U>
    void build(const vector<U> &v) {
        int n = v.size();
        init(n);
        for (int i = 0; i < n; ++i) add(i, v[i]);
    }

    // v[k] += w
    void add(int k, T w) {
        for (++k; k <= N; k += k & -k) data[k] += w;
    }

    // v[k] = x
    void update(int k, T x) { add(k, x - at(k)); }

    // v[0] + ... + v[k - 1]
    T sum(int k) const {
        T res = 0;
        for (; k > 0; k -= k & -k) res += data[k];
        return res;
    }

    // v[a] + ... + v[b - 1]
    T sum(int a, int b) const { return sum(b) - sum(a); }

    int lower_bound(T x) const {
        if (x <= 0) return 0;
        int res = 0;
        for (int k = N; k > 0; k >>= 1) {
            if (res + k <= N && data[res + k] < x) x -= data[res += k];
        }
        return res;
    }
};
