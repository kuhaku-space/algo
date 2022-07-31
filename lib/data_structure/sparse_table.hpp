#pragma once
#include "math/pow.hpp"
#include "segment_tree/monoid.hpp"
#include "template/template.hpp"

/**
 * @brief スパーステーブル
 *
 * @tparam M モノイド
 */
template <class M>
struct sparse_table {
  private:
    using T = typename M::value_type;

  public:
    sparse_table(const std::vector<T> &v) : _size(v.size()), lookup(v.size() + 1), data() {
        int b = std::max(1, ceil_pow2(this->_size));
        this->data.emplace_back(v);
        for (int i = 1; i < b; ++i) this->data.emplace_back(this->_size + 1 - (1 << i));
        for (int i = 1; i < b; ++i) {
            for (int j = 0; j + (1 << i) <= this->_size; ++j) {
                this->data[i][j] =
                    M::op(this->data[i - 1][j], this->data[i - 1][j + (1 << (i - 1))]);
            }
        }
        for (int i = 3; i <= this->_size; ++i) this->lookup[i] = this->lookup[(i + 1) >> 1] + 1;
    }

    T prod(int l, int r) const {
        assert(0 <= l && l < r && r <= this->_size);
        int b = this->lookup[r - l];
        return M::op(this->data[b][l], this->data[b][r - (1 << b)]);
    }

  private:
    int _size;
    std::vector<int> lookup;
    std::vector<std::vector<T>> data;
};
