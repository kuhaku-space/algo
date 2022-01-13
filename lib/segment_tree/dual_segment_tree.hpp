#include "math/pow.hpp"
#include "segment_tree/monoid.hpp"
#include "template/template.hpp"

/**
 * @brief 双対セグメント木
 *
 * @tparam M
 */
template <class M>
struct dual_segment_tree {
    using T = typename M::value_type;

    dual_segment_tree(int _n, T _e = M::id) { this->init(_n, _e); }

    void init(int n, T e) {
        this->_log = ceil_pow2(n);
        this->_size = 1 << this->_log;
        this->data.assign(this->_size << 1, e);
    }

    T at(int k) { return this->get(k); }
    T get(int k) {
        assert(0 <= k && k < this->_size);
        k += this->_size;
        for (int i = this->_log; i >= 1; --i) this->push(k >> i);
        return this->data[k];
    }

    void apply(int a, T val) { this->apply(a, a + 1, val); }
    void apply(int a, int b, T val) {
        assert(0 <= a && a <= this->_size);
        assert(0 <= b && b <= this->_size);
        a += this->_size, b += this->_size;
        for (int i = _log; i >= 1; --i) {
            if (((a >> i) << i) != a) this->push(a >> i);
            if (((b >> i) << i) != b) this->push((b - 1) >> i);
        }

        for (; a < b; a >>= 1, b >>= 1) {
            if (a & 1) this->all_apply(a++, val);
            if (b & 1) this->all_apply(--b, val);
        }
    }

  private:
    int _size, _log;
    vector<T> data;

    void all_apply(int k, T val) { this->data[k] = M::op(val, this->data[k]); }
    void push(int k) {
        this->all_apply(2 * k, this->data[k]);
        this->all_apply(2 * k + 1, this->data[k]);
        this->data[k] = M::id;
    }
};
