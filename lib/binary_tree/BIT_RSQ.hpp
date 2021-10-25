#include "binary_tree/BIT.hpp"
#include "template/template.hpp"

template <class T>
struct BIT_RSQ {
    BIT_RSQ(int n) : p(n + 1), q(n + 1) {}

    void init(int n) {
        p = BIT<T>(n + 1);
        q = BIT<T>(n + 1);
    }

    auto operator[](int i) const { this->sum(i + 1) - this->sum(i); }
    auto at(int k) const { return this->operator[](k); }

    template <class U>
    void build(const vector<U> &v) {
        int n = v.size();
        for (int i = 0; i < n; ++i) {
            p.add(i, v[i]);
            p.add(i + 1, -v[i]);
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
        p.add(a, -val * a);
        p.add(b, val * b);
        q.add(a, val);
        q.add(b, -val);
    }

    /**
     * @brief v[0] + ... v[k - 1]
     *
     * @param k index of array
     * @return auto
     */
    auto sum(int k) const { return p.sum(k) + q.sum(k) * k; }
    /**
     * @brief v[a] + ... + v[b - 1]
     *
     * @param a first index of array
     * @param b last index of array
     * @return auto
     */
    auto sum(int a, int b) const { return this->sum(b) - this->sum(a); }

  private:
    BIT<T> p, q;
};
