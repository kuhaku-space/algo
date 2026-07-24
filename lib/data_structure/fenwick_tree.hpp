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
    /// @brief 空のFenwick Treeを構築する
    /// @complexity $O(1)$
    FenwickTree() : _size() {}

    /// @brief 長さnの0列を構築する
    /// @complexity $O(n)$
    FenwickTree(int n) : _size(n + 1), data(RangeAdd ? _size + 1 : _size) {
        if constexpr (RangeAdd) data2.assign(_size + 1, T());
    }
    /// @brief 列からFenwick Treeを構築する
    /// @complexity RangeAddがfalseなら $O(n)$、trueなら $O(n\log n)$
    template <class U>
    FenwickTree(const std::vector<U> &v) : FenwickTree((int)v.size()) {
        build(v);
    }

    /// @brief i番目の値を返す
    /// @complexity $O(\log n)$
    T operator[](int i) const { return sum(i, i + 1); }

    /// @brief k番目の値を返す
    /// @complexity $O(\log n)$
    T at(int k) const { return operator[](k); }

    /// @brief k番目の値を返す
    /// @complexity $O(\log n)$
    T get(int k) const { return operator[](k); }

    /// @brief 列の値を構築する
    /// @complexity RangeAddがfalseなら $O(n)$、trueなら $O(n\log n)$
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
    /// @complexity $O(\log n)$
    void set(int k, T val) { add(k, val - at(k)); }
    /// @brief v[k] += val
    /// @complexity $O(\log n)$
    void add(int k, T val) {
        if constexpr (RangeAdd) {
            add(k, k + 1, val);
        } else {
            assert(0 <= k && k < _size - 1);
            for (++k; k < _size; k += k & -k) data[k] += val;
        }
    }
    /// @brief v[a] ... v[b - 1] += val
    /// @complexity $O(\log n)$
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
    /// @complexity $O(\log n)$
    bool chmax(int k, T val) {
        if (at(k) >= val) return false;
        set(k, val);
        return true;
    }
    /// @brief chmin(v[k], val)
    /// @complexity $O(\log n)$
    bool chmin(int k, T val) {
        if (at(k) <= val) return false;
        set(k, val);
        return true;
    }

    /// @brief v[0] + ... + v[n - 1]
    /// @complexity $O(\log n)$
    T all_prod() const { return prod(_size - 1); }
    /// @brief v[0] + ... + v[k - 1]
    /// @complexity $O(\log n)$
    T prod(int k) const { return sum(k); }
    /// @brief v[a] + ... + v[b - 1]
    /// @complexity $O(\log n)$
    T prod(int a, int b) const { return sum(a, b); }
    /// @brief v[0] + ... + v[n - 1]
    /// @complexity $O(\log n)$
    T all_sum() const { return sum(_size - 1); }
    /// @brief v[0] + ... + v[k - 1]
    /// @complexity $O(\log n)$
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
    /// @complexity $O(\log n)$
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

    /// @brief 接頭辞和がval以上となる最初の位置を返す
    /// @complexity $O(\log n)$
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
    /// @brief kからの区間和がval以上となる最初の位置を返す
    /// @complexity $O(\log n)$
    int lower_bound(int k, T val) const
    requires(!RangeAdd)
    {
        assert(val >= 0);
        return lower_bound(val + sum(k));
    }

    /// @brief 接頭辞和がvalより大きくなる最初の位置を返す
    /// @complexity $O(\log n)$
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
    /// @brief kからの区間和がvalより大きくなる最初の位置を返す
    /// @complexity $O(\log n)$
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
