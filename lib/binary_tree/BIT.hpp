#include "_base.hpp"

// 一転加算、区間総和
template <class T>
struct BIT {
    int64_t N;
    vector<T> data;

    BIT() {}

    BIT(int64_t n) {
        init(n);
    }

    const T &operator[](const int64_t i) const {
        return at(i);
    }

    T at(int64_t k) const { return sum(k + 1) - sum(k); }

    void init() {
        data.assign(N + 1, 0);
    }

    void init(int64_t n) {
        N = 1;
        while (N < n) N <<= 1;
        data.assign(N + 1, 0);
    }

    void build(vector<T> v) {
        init(N);
        for (int i = 0; i < v.size(); ++i) {
            add(i, v[i]);
        }
    }

    // v[k] += w
    void add(int64_t k, T w) {
        for (++k; k <= N; k += k & -k) {
            data[k] += w;
        }
    }

    // v[k] = x
    void update(int64_t k, T x) {
        add(k, x - at(k));
    }

    // v[0] + ... + v[k - 1]
    T sum(int64_t k) const {
        T res = 0;
        for (; k > 0; k -= k & -k) {
            res += data[k];
        }
        return res;
    }

    // v[a] + ... + v[b - 1]
    T sum(int64_t a, int64_t b) const { return sum(b) - sum(a); }

    int64_t lower_bound(T x) {
        if (x <= 0) return 0;
        int64_t res = 0;
        for (int64_t k = N; k > 0; k >>= 1) {
            if (res + k <= N && bit[res + k] < x) {
                x -= bit[res + k];
                res += k;
            }
        }
        return res;
    }
};
