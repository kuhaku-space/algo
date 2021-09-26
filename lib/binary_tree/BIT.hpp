#include "template/template.hpp"

/**
 * @brief Binary Indexed Tree
 */
template <class T>
struct BIT {
    int N;
    vector<T> data;

    BIT() : N(), data() {}
    BIT(int n, T e = T(0)) : N(n + 1), data(n + 1, e) {}
    BIT(const vector<T> &v) : N(v.size() + 1), data(v.size() + 1) { this->build(v); }

    const T &operator[](int i) const { return this->at(i); }
    const T at(int k) const { return this->sum(k + 1) - this->sum(k); }
    const T get(int k) const { return this->sum(k + 1) - this->sum(k); }

    template <class U>
    void build(const vector<U> &v) {
        int n = v.size();
        for (int i = 0; i < n; ++i) this->add(i, v[i]);
    }

    /**
     * @brief v[k] = x
     *
     * @param k index
     * @param x data
     * @return void
     */
    void update(int k, T x) { this->add(k, x - this->at(k)); }
    /**
     * @brief v[k] += x
     *
     * @param k index
     * @param x data
     * @return void
     */
    void add(int k, T x) {
        assert(0 <= k && k < this->N);
        for (++k; k < N; k += k & -k) this->data[k] += x;
    }
    /**
     * @brief chmax(v[k], x)
     *
     * @param k index
     * @param x data
     * @return bool
     */
    bool chmax(int k, T x) {
        if (this->at(k) >= x) return false;
        this->update(k, x);
        return true;
    }
    /**
     * @brief chmin(v[k], x)
     *
     * @param k index
     * @param x data
     * @return bool
     */
    bool chmin(int k, T x) {
        if (this->at(k) <= x) return false;
        this->update(k, x);
        return true;
    }

    /**
     * @brief v[0] + ... + v[n - 1]
     *
     * @return T
     */
    T sum() const { return this->sum(this->N); }
    /**
     * @brief v[0] + ... + v[k - 1]
     *
     * @param k index
     * @return T
     */
    T sum(int k) const {
        assert(0 <= k && k <= this->N);
        T res = 0;
        for (; k > 0; k -= k & -k) res += this->data[k];
        return res;
    }
    /**
     * @brief v[a] + ... + v[b - 1]
     *
     * @param a first index
     * @param b last index
     * @return T
     */
    T sum(int a, int b) const { return this->sum(b) - this->sum(a); }

    /**
     * @brief BIT上で二分探索
     *
     * @param x data
     * @return int
     */
    int lower_bound(T x) const {
        if (x <= 0) return 0;
        int k = 1;
        while (k < this->N) k <<= 1;
        int res = 0;
        for (; k > 0; k >>= 1) {
            if (res + k < N && this->data[res + k] < x) x -= this->data[res += k];
        }
        return res;
    }
};
