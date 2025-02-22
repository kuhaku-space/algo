#pragma once
#include <bit>
#include <cassert>
#include <vector>

/// @brief スパーステーブル
template <class M>
struct sparse_table {
  private:
    using T = typename M::value_type;

  public:
    sparse_table() = default;
    sparse_table(const std::vector<T> &v) : _size(v.size()), data() {
        int b = std::max(1, std::countr_zero(std::bit_ceil<unsigned>(_size)));
        data.emplace_back(v);
        for (int i = 1; i < b; ++i) data.emplace_back(_size + 1 - (1 << i));
        for (int i = 1; i < b; ++i) {
            for (int j = 0; j + (1 << i) <= _size; ++j) {
                data[i][j] = M::op(data[i - 1][j], data[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _size);
        if (l == r) return M::id();
        if (l + 1 == r) return data[0][l];
        int b = 31 - std::countl_zero<unsigned>(r - l - 1);
        return M::op(data[b][l], data[b][r - (1 << b)]);
    }

  private:
    int _size;
    std::vector<std::vector<T>> data;
};
