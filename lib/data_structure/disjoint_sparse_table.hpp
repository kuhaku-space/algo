#include <bit>
#include <cassert>
#include <vector>
#include "internal/internal_bit.hpp"

/**
 * @brief Disjoint Sparse Table
 * @see https://noshi91.hatenablog.com/entry/2018/05/08/183946
 * @see https://ei1333.github.io/library/structure/others/disjoint-sparse-table.hpp.html
 *
 * @tparam M
 */
template <class M>
struct disjoint_sparse_table {
  private:
    using T = typename M::value_type;

  public:
    template <class U>
    disjoint_sparse_table(const std::vector<U> &v) {
        int b = 1;
        while (1 << b < (int)v.size()) ++b;
        data.resize(b, std::vector<T>(v.size(), M::id));
        for (int i = 0; i < (int)v.size(); i++) data[0][i] = v[i];
        for (int i = 1; i < b; i++) {
            int shift = 1 << i;
            for (int j = 0; j < (int)v.size(); j += shift << 1) {
                int t = std::min(j + shift, (int)v.size());
                data[i][t - 1] = v[t - 1];
                for (int k = t - 2; k >= j; k--) data[i][k] = M::op(v[k], data[i][k + 1]);
                if ((int)v.size() <= t) break;
                data[i][t] = v[t];
                int r = std::min(t + shift, (int)v.size());
                for (int k = t + 1; k < r; k++) data[i][k] = M::op(data[i][k - 1], v[k]);
            }
        }
    }

    T prod(int l, int r) const {
        assert(l <= r);
        if (l == r) return M::id;
        if (l == --r) return data[0][l];
        int p = 31 - internal::countl_zero(unsigned(l ^ r));
        return M::op(data[p][l], data[p][r]);
    }

  private:
    std::vector<std::vector<T>> data;
};
