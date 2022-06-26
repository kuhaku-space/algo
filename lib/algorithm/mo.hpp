#include "template/template.hpp"

/**
 * @brief Mo's algorithm
 * @see https://ei1333.hateblo.jp/entry/2017/09/11/211011
 * @see https://snuke.hatenablog.com/entry/2016/07/01/000000
 *
 * @tparam F
 * @tparam G
 */
template <class F, class G>
struct Mo {
    Mo(int n, const F &f, const G &g)
        : _left(), _right(), _order(), _size(n), _nl(0), _nr(0), _ptr(0), _add(f), _del(g) {}

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
            return (this->_left[a] / width % 2) != (this->_right[a] < this->_right[b]);
        });
    }

    int process() {
        if (this->_ptr == (int)this->_order.size()) return -1;
        const auto id = this->_order[this->_ptr];
        while (this->_nl > this->_left[id]) this->_add(--this->_nl);
        while (this->_nr < this->_right[id]) this->_add(this->_nr++);
        while (this->_nl < this->_left[id]) this->_del(this->_nl++);
        while (this->_nr > this->_right[id]) this->_del(--this->_nr);
        return this->_order[this->_ptr++];
    }

  private:
    std::vector<int> _left, _right, _order;
    int _size, _nl, _nr, _ptr;
    const F &_add;
    const G &_del;
};
