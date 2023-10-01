#pragma once
#include <cassert>
#include <vector>

/**
 * @brief フェニック木
 * @see http://hos.ac/slides/20140319_bit.pdf
 *
 * @tparam T
 */
template <class T>
struct fenwick_tree {
    fenwick_tree() : _size(), data() {}
    fenwick_tree(int n) : _size(n + 1), data(n + 1) {}
    fenwick_tree(const std::vector<T> &v) : _size((int)v.size() + 1), data((int)v.size() + 1) {
        this->build(v);
    }
    template <class U>
    fenwick_tree(const std::vector<U> &v) : _size((int)v.size() + 1), data((int)v.size() + 1) {
        this->build(v);
    }

    T operator[](int i) const { return this->sum(i + 1) - this->sum(i); }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }

    template <class U>
    void build(const std::vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) this->add(i, v[i]);
    }

    /**
     * @brief v[k] = val
     *
     * @param k index of array
     * @param val new value
     * @return void
     */
    void update(int k, T val) { this->add(k, val - this->at(k)); }
    /**
     * @brief v[k] += val
     *
     * @param k index of array
     * @param val new value
     * @return void
     */
    void add(int k, T val) {
        assert(0 <= k && k < this->_size);
        for (++k; k < this->_size; k += k & -k) this->data[k] += val;
    }
    /**
     * @brief chmax(v[k], val)
     *
     * @param k index of array
     * @param val new value
     * @return bool
     */
    bool chmax(int k, T val) {
        if (this->at(k) >= val) return false;
        this->update(k, val);
        return true;
    }
    /**
     * @brief chmin(v[k], val)
     *
     * @param k index of value
     * @param val new value
     * @return bool
     */
    bool chmin(int k, T val) {
        if (this->at(k) <= val) return false;
        this->update(k, val);
        return true;
    }

    /**
     * @brief v[0] + ... + v[n - 1]
     *
     * @return T
     */
    T all_sum() const { return this->sum(this->_size); }
    /**
     * @brief v[0] + ... + v[k - 1]
     *
     * @param k index of array
     * @return T
     */
    T sum(int k) const {
        assert(0 <= k && k <= this->_size);
        T res = 0;
        for (; k > 0; k -= k & -k) res += this->data[k];
        return res;
    }
    /**
     * @brief v[a] + ... + v[b - 1]
     *
     * @param a first index of array
     * @param b last index of array
     * @return T
     */
    T sum(int a, int b) const { return a < b ? this->sum(b) - this->sum(a) : 0; }

    /**
     * @brief binary search on fenwick_tree
     *
     * @param val target value
     * @return int
     */
    int lower_bound(T val) const {
        if (val <= 0) return 0;
        int k = 1;
        while (k < this->_size) k <<= 1;
        int res = 0;
        for (; k > 0; k >>= 1) {
            if (res + k < this->_size && this->data[res + k] < val) val -= this->data[res += k];
        }
        return res;
    }

  private:
    int _size;
    std::vector<T> data;
};
