#include "math/pow.hpp"
#include "segment_tree/monoid.hpp"
#include "template/template.hpp"

/**
 * @brief セグメント木
 * @details [参考](https://noshi91.hatenablog.com/entry/2020/04/22/212649)
 *
 * @tparam M モノイド
 */
template <class M>
struct segment_tree {
    using T = typename M::value_type;

    segment_tree() {}
    segment_tree(int n, T e = M::id) { this->init(n, e); }

    const T &operator[](int i) const { return this->data[i + this->_size]; }
    T at(int k) const { return this->operator[](k); }
    T get(int k) const { return this->operator[](k); }

    void init(int n, T val) {
        this->_log = ceil_pow2(n);
        this->_size = 1 << this->_log;
        this->data.assign(this->_size << 1, val);
    }

    template <class U>
    void build(const vector<U> &v) {
        for (int i = 0, n = v.size(); i < n; ++i) this->data[this->_size + i] = T(v[i]);
        for (int i = this->_size - 1; i >= 1; --i) this->update(i);
    }

    void set(int k, T val) {
        assert(0 <= k && k < this->_size);
        k += this->_size;
        this->data[k] = val;
        for (int i = 1; i <= this->_log; i++) this->update(k >> i);
    }
    void reset(int k) { this->set(k, M::id); }

    T all_prod() const { return this->data[1]; }
    T prod(int a, int b) const {
        assert(0 <= a && b <= this->_size);
        T l = M::id, r = M::id;
        for (a += this->_size, b += this->_size; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = M::op(l, this->data[a++]);
            if (b & 1) r = M::op(this->data[--b], r);
        }
        return M::op(l, r);
    }

  private:
    int _size, _log;
    std::vector<T> data;

    void update(int k) { this->data[k] = M::op(this->data[2 * k], this->data[2 * k + 1]); }
};
