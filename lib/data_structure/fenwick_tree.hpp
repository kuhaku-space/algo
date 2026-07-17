#pragma once
#include <cassert>
#include <type_traits>
#include <variant>
#include <vector>

/// @brief フェニック木
/// @see http://hos.ac/slides/20140319_bit.pdf
/// @tparam RangeAdd true なら区間加算・区間総和（内部で BIT を 2 本保持）。
///                  false なら点更新・区間総和（BIT 1 本、`lower_bound`/`upper_bound` あり）。
template <class T, bool RangeAdd = false>
struct FenwickTree {
    FenwickTree() : _size() {}
    FenwickTree(int n) : _size(n + 1), data(RangeAdd ? _size + 1 : _size) {
        if constexpr (RangeAdd) data2.assign(_size + 1, T());
    }
    template <class U>
    FenwickTree(const std::vector<U> &v) : FenwickTree((int)v.size()) {
        build(v);
    }

    T operator[](int i) const { return sum(i, i + 1); }
    T at(int k) const { return operator[](k); }
    T get(int k) const { return operator[](k); }

    template <class U>
    void build(const std::vector<U> &v) {
        if constexpr (RangeAdd) {
            for (int i = 0, n = v.size(); i < n; ++i) add(i, v[i]);
        } else {
            for (int i = 0, n = v.size(); i < n; ++i) data[i + 1] = v[i];
            for (int i = 1; i < _size; ++i) {
                if (i + (i & -i) < _size) data[i + (i & -i)] += data[i];
            }
        }
    }

    /// @brief v[k] = val
    void set(int k, T val) { add(k, val - at(k)); }
    /// @brief v[k] += val
    void add(int k, T val) {
        if constexpr (RangeAdd) {
            add(k, k + 1, val);
        } else {
            assert(0 <= k && k < _size - 1);
            for (++k; k < _size; k += k & -k) data[k] += val;
        }
    }
    /// @brief v[a] ... v[b - 1] += val
    void add(int a, int b, T val)
    requires RangeAdd
    {
        assert(0 <= a && a <= b && b < _size);
        add_raw(data, a, -val * a);
        add_raw(data, b, val * b);
        add_raw(data2, a, val);
        add_raw(data2, b, -val);
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
        if constexpr (RangeAdd) {
            return sum_raw(data, k) + sum_raw(data2, k) * k;
        } else {
            T res = T();
            for (; k > 0; k -= k & -k) res += data[k];
            return res;
        }
    }
    /// @brief v[a] + ... + v[b - 1]
    T sum(int a, int b) const {
        assert(0 <= a && a <= b && b < _size);
        if constexpr (RangeAdd) {
            return sum(b) - sum(a);
        } else {
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
    }

    int lower_bound(T val) const
    requires(!RangeAdd)
    {
        assert(val >= 0);
        if (val == 0) return 0;
        int k = 1;
        while (k < _size) k <<= 1;
        int res = 0;
        for (; k > 0; k >>= 1) {
            if (res + k < _size && data[res + k] < val) val -= data[res += k];
        }
        return res;
    }
    int lower_bound(int k, T val) const
    requires(!RangeAdd)
    {
        assert(val >= 0);
        return lower_bound(val + sum(k));
    }

    int upper_bound(T val) const
    requires(!RangeAdd)
    {
        assert(val >= 0);
        int k = 1;
        while (k < _size) k <<= 1;
        int res = 0;
        for (; k > 0; k >>= 1) {
            if (res + k < _size && !(val < data[res + k])) val -= data[res += k];
        }
        return res;
    }
    int upper_bound(int k, T val) const
    requires(!RangeAdd)
    {
        assert(val >= 0);
        return upper_bound(val + sum(k));
    }

  private:
    static void add_raw(std::vector<T> &d, int k, T val) {
        for (++k; k < (int)d.size(); k += k & -k) d[k] += val;
    }
    static T sum_raw(const std::vector<T> &d, int k) {
        T res = T();
        for (; k > 0; k -= k & -k) res += d[k];
        return res;
    }

    int _size;
    std::vector<T> data;
    [[no_unique_address]] std::conditional_t<RangeAdd, std::vector<T>, std::monostate> data2;
};
