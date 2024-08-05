#pragma once
#include <array>
#include <cassert>
#include <cstdint>
#include <vector>
#include "data_structure/sparse_table.hpp"

namespace internal {

template <class T, int N>
struct fixed_stack {
    constexpr fixed_stack() : _size(), _data() {}

    constexpr T top() const { return _data[_size - 1]; }
    constexpr bool empty() const { return _size == 0; }
    constexpr int size() const { return _size; }
    constexpr void emplace(const T &e) { _data[_size++] = e; }
    constexpr void emplace(T &&e) { _data[_size++] = e; }
    constexpr void pop() { --_size; }
    constexpr void clear() { _size = 0; }

  private:
    int _size;
    std::array<T, N> _data;
};

}  // namespace internal

/**
 * @brief 線形 Sparse Table
 *
 * @tparam M
 */
template <class M>
struct linear_sparse_table {
  private:
    using T = M::value_type;
    static constexpr int W = 64;

  public:
    linear_sparse_table(const std::vector<T> &v) : _size(v.size()), data(v) {
        int n = v.size();
        int b = n / W;
        internal::fixed_stack<int, W + 1> st;
        std::vector<T> u(b);
        word_data.resize(b + (n > b * W));
        for (int i = 0; i < b; ++i) {
            T m = M::id();
            std::uint64_t bit = 0;
            std::vector<std::uint64_t> bits(W);
            for (int j = 0; j < W; ++j) {
                m = M::op(m, v[i * W + j]);
                while (!st.empty() && v[i * W + st.top()] >= v[i * W + j]) {
                    bit ^= 1ul << st.top();
                    st.pop();
                }
                bits[j] = bit;
                bit |= 1ul << j;
                st.emplace(j);
            }
            u[i] = m;
            word_data[i] = bits;
            st.clear();
        }
        if (n > b * W) {
            std::uint64_t bit = 0;
            std::vector<std::uint64_t> bits(n - b * W);
            for (int j = 0; j < n - b * W; ++j) {
                while (!st.empty() && v[b * W + st.top()] >= v[b * W + j]) {
                    bit ^= 1 << st.top();
                    st.pop();
                }
                bits[j] = bit;
                bit |= 1ul << j;
                st.emplace(j);
            }
            word_data[b] = bits;
        }
        block_data = sparse_table<M>(u);
    }

    T prod(int l, int r) {
        assert(0 <= l && l < r && r <= _size);
        int lb = (l + W - 1) / W, rb = r / W;
        if (lb > rb) return word_prod(l, r);
        int res = (lb == rb ? M::id() : block_data.prod(lb, rb));
        if (l < lb * W) res = M::op(res, word_prod(l, lb * W));
        if (rb * W < r) res = M::op(res, word_prod(rb * W, r));
        return res;
    }

    T word_prod(int l, int r) {
        if (l == r) return M::id();
        int b = l / W;
        int lw = l - b * W, rw = r - b * W;
        if ((word_data[b][rw - 1] >> lw) == 0ul) return data[r - 1];
        return data[l + __builtin_ctzl(word_data[b][rw - 1] >> lw)];
    }

  private:
    int _size;
    std::vector<T> data;
    sparse_table<M> block_data;
    std::vector<std::vector<std::uint64_t>> word_data;
};
