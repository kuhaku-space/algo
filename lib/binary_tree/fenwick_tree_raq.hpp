#include "binary_tree/fenwick_tree.hpp"
#include "template/template.hpp"

/**
 * @brief フェニック木（区間加算、区間総和）
 *
 * @tparam T
 */
template <class T>
struct fenwick_tree_raq {
    fenwick_tree_raq() = default;
    fenwick_tree_raq(int n) : p(n + 1), q(n + 1) {}

    auto operator[](int i) const { return this->sum(i + 1) - this->sum(i); }
    auto at(int k) const { return this->operator[](k); }

    template <class U>
    void build(const vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) {
            this->add(i, v[i]);
        }
    }

    /**
     * @brief v[k] = val
     *
     * @param k index of array
     * @param val new value
     */
    void update(int k, T val) { this->add(k, k + 1, val - this->at(k)); }

    /**
     * @brief v[k] += val
     *
     * @param k index of array
     * @param val
     */
    void add(int k, T val) { this->add(k, k + 1, val); }
    /**
     * @brief v[a ... b-1] += val
     *
     * @param a first index of array
     * @param b last index of array
     * @param val
     */
    void add(int a, int b, T val) {
        this->p.add(a, -val * a);
        this->p.add(b, val * b);
        this->q.add(a, val);
        this->q.add(b, -val);
    }

    /**
     * @brief v[0] + ... v[k - 1]
     *
     * @param k index of array
     * @return T
     */
    T sum(int k) const { return this->p.sum(k) + this->q.sum(k) * k; }
    /**
     * @brief v[a] + ... + v[b - 1]
     *
     * @param a first index of array
     * @param b last index of array
     * @return T
     */
    T sum(int a, int b) const { return this->sum(b) - this->sum(a); }

  private:
    fenwick_tree<T> p, q;
};
