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
            this->add(l - bias, r - bias + closed);
        }
    }

    void add(int l, int r) {
        this->_left.emplace_back(l);
        this->_right.emplace_back(r);
    }
    void emplace(int l, int r) { return this->add(l, r); }
    void insert(int l, int r) { return this->add(l, r); }

    void build() {
        int q = this->_left.size();
        int width = std::max(1, int(this->_size / sqrt(q)));
        this->_order.resize(q);
        std::iota(this->_order.begin(), this->_order.end(), 0);
        std::sort(this->_order.begin(), this->_order.end(), [&](int a, int b) -> bool {
            if (this->_left[a] / width != this->_left[b] / width)
                return this->_left[a] < this->_left[b];
            return (this->_left[a] / width % 2 == 0) ? (this->_right[a] < this->_right[b])
                                                     : (this->_right[b] < this->_right[a]);
        });
    }

    int process() {
        if (this->_ptr == (int)this->_order.size()) return -1;
        const auto id = this->_order[this->_ptr];
        while (this->_nl > this->_left[id]) this->_addl(--this->_nl);
        while (this->_nr < this->_right[id]) this->_addr(this->_nr++);
        while (this->_nl < this->_left[id]) this->_dell(this->_nl++);
        while (this->_nr > this->_right[id]) this->_delr(--this->_nr);
        return this->_order[this->_ptr++];
    }

  private:
    std::vector<int> _left, _right, _order;
    int _size, _nl, _nr, _ptr;
    F _addl;
    H _addr;
    G _dell;
    I _delr;
};
