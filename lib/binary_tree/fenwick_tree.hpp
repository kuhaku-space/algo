#pragma once
#include <cassert>
#include <vector>

/// @brief フェニック木
/// @see http://hos.ac/slides/20140319_bit.pdf
template <class T>
struct fenwick_tree {
    fenwick_tree() : _size(), data() {}
    fenwick_tree(int n) : _size(n + 1), data(n + 1) {}
    template <class U>
    fenwick_tree(const std::vector<U> &v) : _size((int)v.size() + 1), data((int)v.size() + 1) {
        build(v);
    }

    T operator[](int i) const { return sum(i, i + 1); }
    T at(int k) const { return operator[](k); }
    T get(int k) const { return operator[](k); }

    template <class U>
    void build(const std::vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) data[i + 1] = v[i];
        for (int i = 1; i < _size; ++i) {
            if (i + (i & -i) < _size) data[i + (i & -i)] += data[i];
        }
    }

    /// @brief v[k] = val
    void set(int k, T val) { add(k, val - at(k)); }
    /// @brief v[k] += val
    void add(int k, T val) {
        assert(0 <= k && k < _size - 1);
        for (++k; k < _size; k += k & -k) data[k] += val;
    }
    /// @brief chmax(v[k], val)
    bool chmax(int k, T val) {
        if (at(k) >= val) return false;
        set(k, val);
        return true;
    }
    /// @brief chmin(v[k], val)
    bool chmin(int k, T val) {
        if (at(k) <= val) return false;
        set(k, val);
        return true;
    }

    /// @brief v[0] + ... + v[n - 1]
    T all_prod() const { return prod(_size - 1); }
    /// @brief v[0] + ... + v[k - 1]
    T prod(int k) const { return sum(k); }
    /// @brief v[a] + ... + v[b - 1]
    T prod(int a, int b) const { return sum(a, b); }
    /// @brief v[0] + ... + v[n - 1]
    T all_sum() const { return sum(_size - 1); }
    /// @brief v[0] + ... + v[k - 1]
    T sum(int k) const {
        assert(0 <= k && k < _size);
        T res = 0;
        for (; k > 0; k -= k & -k) res += data[k];
        return res;
    }
    /// @brief v[a] + ... + v[b - 1]
    T sum(int a, int b) const {
        assert(0 <= a && a <= b && b < _size);
        T res = T();
        while (a != b) {
            if (a < b) {
                res += data[b];
                b -= b & -b;
            } else {
                res -= data[a];
                a -= a & -a;
            }
        }
        return res;
    }

    int lower_bound(T val) const {
        if (val <= 0) return 0;
        int k = 1;
        while (k < _size) k <<= 1;
        int res = 0;
        for (; k > 0; k >>= 1) {
            if (res + k < _size && data[res + k] < val) val -= data[res += k];
        }
        return res;
    }

  private:
    int _size;
    std::vector<T> data;
};
