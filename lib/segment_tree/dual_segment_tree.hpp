#include "math/pow.hpp"
#include "segment_tree/monoid.hpp"
#include "template/template.hpp"

/**
 * @brief 双対セグメント木
 *
 * @tparam M モノイド
 */
template <class M>
struct dual_segment_tree {
  private:
    using T = typename M::value_type;

  public:
    dual_segment_tree(int _n, T _e = M::id) { init(_n, _e); }

    void init(int n, T e) {
        _log = ceil_pow2(n);
        _size = 1 << _log;
        data.assign(_size << 1, e);
    }

    T at(int k) { return get(k); }
    T get(int k) {
        assert(0 <= k && k < _size);
        k += _size;
        for (int i = _log; i >= 1; --i) push(k >> i);
        return data[k];
    }

    void apply(int a, T val) { apply(a, a + 1, val); }
    void apply(int a, int b, T val) {
        assert(0 <= a && a <= _size);
        assert(0 <= b && b <= _size);
        a += _size, b += _size;
        for (int i = _log; i >= 1; --i) {
            if (((a >> i) << i) != a) push(a >> i);
            if (((b >> i) << i) != b) push((b - 1) >> i);
        }

        for (; a < b; a >>= 1, b >>= 1) {
            if (a & 1) all_apply(a++, val);
            if (b & 1) all_apply(--b, val);
        }
    }

  private:
    int _size, _log;
    std::vector<T> data;

    void all_apply(int k, T val) { data[k] = M::op(val, data[k]); }
    void push(int k) {
        all_apply(2 * k, data[k]);
        all_apply(2 * k + 1, data[k]);
        data[k] = M::id;
    }
};
