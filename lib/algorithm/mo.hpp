#include "template/template.hpp"

/**
 * @brief Mo's algorithm
 * @see https://ei1333.hateblo.jp/entry/2017/09/11/211011
 * @see https://snuke.hatenablog.com/entry/2016/07/01/000000
 *
 * @tparam F
 * @tparam G
 */
template <class F, class G, class H = F, class I = G>
struct Mo {
    Mo(int n, F f, G g)
        : _left(), _right(), _order(), _size(n), _nl(0), _nr(0), _ptr(0), _addl(f), _addr(f),
          _dell(g), _delr(g) {}
    Mo(int n, F fl, H fr, G gl, I gr)
        : _left(), _right(), _order(), _size(n), _nl(0), _nr(0), _ptr(0), _addl(fl), _addr(fr),
          _dell(gl), _delr(gr) {}

    void input(int q, int bias = 1, int closed = 0) {
        for (int i = 0; i < q; ++i) {
            int l, r;
            std::cin >> l >> r;
            add(l - bias, r - bias + closed);
        }
    }

    void add(int l, int r) {
        _left.emplace_back(l);
        _right.emplace_back(r);
    }
    void emplace(int l, int r) { return add(l, r); }
    void insert(int l, int r) { return add(l, r); }

    void build() {
        int q = _left.size();
        int width = std::max(1, int(_size / std::sqrt(q)));
        _order.resize(q);
        std::iota(_order.begin(), _order.end(), 0);
        std::sort(_order.begin(), _order.end(), [&](int a, int b) -> bool {
            if (_left[a] / width != _left[b] / width) return _left[a] < _left[b];
            return (_left[a] / width % 2 == 0) ? (_right[a] < _right[b]) : (_right[b] < _right[a]);
        });
    }

    int process() {
        if (_ptr == (int)_order.size()) return -1;
        const auto id = _order[_ptr];
        while (_nl > _left[id]) _addl(--_nl);
        while (_nr < _right[id]) _addr(_nr++);
        while (_nl < _left[id]) _dell(_nl++);
        while (_nr > _right[id]) _delr(--_nr);
        return _order[_ptr++];
    }

  private:
    std::vector<int> _left, _right, _order;
    int _size, _nl, _nr, _ptr;
    F _addl;
    H _addr;
    G _dell;
    I _delr;
};
