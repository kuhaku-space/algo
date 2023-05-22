#include "template/template.hpp"

/**
 * @brief Mo's algorithm (rollback)
 * @see https://ei1333.hateblo.jp/entry/2017/09/11/211011
 * @see https://snuke.hatenablog.com/entry/2016/07/01/000000
 */
struct rollback_mo {
    rollback_mo(int n) : _left(), _right(), _order(), _size(n) {}

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

    template <class F, class G, class H, class I>
    void solve(F rem, G save, H load, I add) const {
        return solve(rem, save, load, add, add);
    }
    template <class F, class G, class H, class I, class J>
    void solve(F rem, G save, H load, I addl, J addr) const {
        int q = this->_left.size();
        int width = std::max(1, int(this->_size / std::sqrt(q)));
        this->_order.resize(q);
        std::iota(this->_order.begin(), this->_order.end(), 0);
        std::sort(this->_order.begin(), this->_order.end(), [&](int a, int b) -> bool {
            if (this->_left[a] / width != this->_left[b] / width)
                return this->_left[a] < this->_left[b];
            return this->_right[a] < this->_right[b];
        });

        auto reset = save();
        for (auto idx : this->_order) {
            if (this->_right[idx] - this->_left[idx] < width) {
                for (int i = this->_left[idx]; i < this->_right[idx]; i++) addr(i);
                rem(idx);
                load(reset);
            }
        }

        int right = 0, last_block = -1;
        for (auto idx : this->_order) {
            if (this->_right[idx] - this->_left[idx] < width) continue;
            int block = this->_left[idx] / width;
            if (block != last_block) {
                load(reset);
                last_block = block;
                right = (block + 1) * width;
            }
            while (right < this->_right[idx]) addr(right++);
            auto snapshot = save();
            for (int j = (block + 1) * width - 1; j >= this->_left[idx]; --j) addl(j);
            rem(idx);
            load(snapshot);
        }
    }

  private:
    std::vector<int> _left, _right, _order;
    int _size;
};
