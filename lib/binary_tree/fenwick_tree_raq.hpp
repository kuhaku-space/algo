#include "binary_tree/fenwick_tree.hpp"

/**
 * @brief フェニック木（区間加算、区間総和）
 *
 * @tparam T
 */
template <class T>
struct fenwick_tree_raq {
    fenwick_tree_raq() = default;
    fenwick_tree_raq(int _n) : n(_n), p(n + 1), q(n + 1) {}

    auto operator[](int i) const { return sum(i + 1) - sum(i); }
    auto at(int k) const { return operator[](k); }

    template <class U>
    void build(const std::vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) add(i, v[i]);
    }

    /**
     * @brief v[k] = val
     *
     * @param k index of array
     * @param val new value
     */
    void update(int k, T val) { add(k, k + 1, val - at(k)); }

    /**
     * @brief v[k] += val
     *
     * @param k index of array
     * @param val
     */
    void add(int k, T val) { add(k, k + 1, val); }
    /**
     * @brief v[a ... b-1] += val
     *
     * @param a first index of array
     * @param b last index of array
     * @param val
     */
    void add(int a, int b, T val) {
        assert(0 <= a && a <= b && b <= n);
        p.add(a, -val * a);
        p.add(b, val * b);
        q.add(a, val);
        q.add(b, -val);
    }

    /**
     * @brief v[0] + ... v[k - 1]
     *
     * @param k index of array
     * @return T
     */
    T sum(int k) const {
        assert(0 <= k && k <= n);
        return p.sum(k) + q.sum(k) * k;
    }
    /**
     * @brief v[a] + ... + v[b - 1]
     *
     * @param a first index of array
     * @param b last index of array
     * @return T
     */
    T sum(int a, int b) const { return sum(b) - sum(a); }

  private:
    int n;
    fenwick_tree<T> p, q;
};
