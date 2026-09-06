#pragma once
#include <bit>
#include <cassert>
#include <vector>
#include "segtree/monoid.hpp"

/// @file
/// @brief スパーステーブル (Sparse Table)
/// @details 更新のない列に対する冪等な区間演算を、$O(n\log n)$ の前計算後に $O(1)$ で求める。
///          Range Minimum Query、Range Maximum Query、GCD などに適する。
/// @note クエリでは区間を同じ長さの 2 区間で重ねて覆うため、演算が冪等である必要がある。
/// @note 和や積のような非冪等演算には `data_structure/disjoint_sparse_table.hpp`、
///       更新が必要なら `segtree/segment_tree.hpp` を使う。
/// @note 空区間 `prod(l, l)` は `M::id()` を返す。構築後の要素更新はできない。
/// @code
/// #include <iostream>
/// #include <vector>
/// #include "data_structure/sparse_table.hpp"
///
/// int main() {
///     std::vector<int> a = {5, 2, 7, 1, 3};
///     sparse_table<Min<int>> table(a);
///     std::cout << table.prod(1, 4) << '\n';  // min(2, 7, 1)
/// }
/// @endcode

/// @brief スパーステーブル
/// @details 冪等なモノイドを仮定する。
/// @complexity 構築は $O(n\log n)$、区間積は $O(1)$
template <monoid M>
struct sparse_table {
  private:
    using T = typename M::value_type;

  public:
    /// @brief 空のtableを構築する
    /// @complexity $O(1)$
    sparse_table() = default;

    /// @brief 列vから構築する
    /// @complexity $O(n\log n)$
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

    /// @brief 半開区間[l,r)の積を返す
    /// @complexity $O(1)$
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
