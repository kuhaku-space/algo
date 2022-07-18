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
    sparse_table(const std::vector<T> &v) : _size(v.size()), lookup(v.size() + 1) {
        int s = v.size();
        int b = floor_pow2(s) + 1;
        this->data = std::vector<std::vector<T>>(b, std::vector<T>(1 << b));
        for (int i = 0; i < s; ++i) this->data[0][i] = v[i];

        for (int i = 1; i < b; ++i) {
            for (int j = 0; j + (1 << i) <= (1 << b); j++) {
                this->data[i][j] =
                    M::op(this->data[i - 1][j], this->data[i - 1][j + (1 << (i - 1))]);
            }
        }

        for (int i = 2; i < s + 1; ++i) this->lookup[i] = this->lookup[i >> 1] + 1;
    }

    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= this->_size);
        int b = this->lookup[r - l];
        return M::op(this->data[b][l], this->data[b][r - (1 << b)]);
    }

  private:
    int _size;
    std::vector<int> lookup;
    std::vector<std::vector<T>> data;
};
