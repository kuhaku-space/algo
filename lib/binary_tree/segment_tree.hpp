#include "template/template.hpp"

/**
 * @brief セグメント木
 *
 * @tparam T 要素の型
 * @tparam F 関数の型
 */
template <class T, class F>
struct segment_tree {
    int N;
    const T e;
    const F op;
    vector<T> data;

    segment_tree() {}
    /**
     * @brief Construct a new segment tree object
     *
     * @param _n length of array
     * @param _e identity element
     * @param _op binary operation
     */
    segment_tree(int _n, T _e, F &&_op) : e(_e), op(_op) { this->init(_n, _e); }
    /**
     * @brief Construct a new segment tree object
     *
     * @param _n length of array
     * @param _e identity element
     * @param _op binary operation
     */
    segment_tree(int _n, T _e, const F &_op) : e(_e), op(_op) { this->init(_n, _e); }

    const T &operator[](int i) const { return this->data[i + this->N]; }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }

    void init(int n, const T val) {
        for (this->N = 1; this->N < n; this->N <<= 1) {}
        this->data.assign(this->N << 1, val);
    }

    template <class U>
    void build(const vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) this->data[this->N + i] = T(v[i]);
        for (int i = this->N - 1; i >= 1; --i)
            this->data[i] = this->op(this->data[i * 2], this->data[i * 2 + 1]);
    }

    void update(int k, T val) {
        assert(0 <= k && k < this->N);
        this->data[k += this->N] = val;
        while ((k >>= 1) >= 1) this->data[k] = this->op(this->data[k * 2], this->data[k * 2 + 1]);
    }
    void add(int k, T val) { this->update(k, val - this->at(k)); }

    bool chmax(int k, T val) {
        if (this->at(k) >= val) return false;
        this->update(k, val);
        return true;
    }
    bool chmin(int k, T val) {
        if (this->at(k) <= val) return false;
        this->update(k, val);
        return true;
    }

    T all_prod() const { return this->data[1]; }
    T prod(int a, int b) const {
        assert(0 <= a && b <= this->N);
        T l = e, r = e;
        for (a += this->N, b += this->N; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = this->op(l, this->data[a++]);
            if (b & 1) r = this->op(this->data[--b], r);
        }
        return this->op(l, r);
    }
};
