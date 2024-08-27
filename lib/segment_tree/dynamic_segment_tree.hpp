#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>
#include "segment_tree/monoid.hpp"

/**
 * @brief 動的セグメント木
 *
 * @tparam M モノイド
 */
template <class M>
struct dynamic_segment_tree {
  private:
    using T = typename M::value_type;

    struct _node {
        std::int64_t index;
        int left, right;
        T value, product;

        constexpr _node() = default;
        constexpr _node(std::int64_t _index, T _value)
            : index(_index), left(-1), right(-1), value(_value), product(_value) {}
    };

  public:
    dynamic_segment_tree(std::int64_t n) : data(), _size(n) {}

    T operator[](std::int64_t k) const {
        assert(0 <= k && k < _size);
        if (data.empty()) return M::id();
        int idx = 0;
        std::int64_t l = 0, r = _size;
        while (idx != -1) {
            if (k == data[idx].index) return data[idx].value;
            std::int64_t m = (l + r) >> 1;
            if (k < m) r = m, idx = data[idx].left;
            else l = m, idx = data[idx].right;
        }
        return M::id();
    }
    T at(std::int64_t k) const { return operator[](k); }
    T get(std::int64_t k) const { return operator[](k); }

    void set(std::int64_t k, T x) {
        assert(0 <= k && k < _size);
        if (data.empty()) {
            data.emplace_back(k, x);
            return;
        }
        int idx = 0;
        std::vector<int> nodes;
        std::int64_t l = 0, r = _size;
        while (true) {
            nodes.emplace_back(idx);
            if (k == data[idx].index) {
                data[idx].value = x;
                break;
            }
            std::int64_t m = (l + r) >> 1;
            if (k < m) {
                if (data[idx].index < k)
                    std::swap(k, data[idx].index), std::swap(x, data[idx].value);
                if (data[idx].left == -1) {
                    data[idx].left = data.size();
                    data.emplace_back(k, x);
                    break;
                }
                r = m, idx = data[idx].left;
            } else {
                if (k < data[idx].index)
                    std::swap(k, data[idx].index), std::swap(x, data[idx].value);
                if (data[idx].right == -1) {
                    data[idx].right = data.size();
                    data.emplace_back(k, x);
                    break;
                }
                l = m, idx = data[idx].right;
            }
        }

        std::reverse(nodes.begin(), nodes.end());
        for (auto idx : nodes) {
            data[idx].product =
                M::op(M::op(data[idx].left != -1 ? data[data[idx].left].product : M::id(),
                            data[idx].value),
                      data[idx].right != -1 ? data[data[idx].right].product : M::id());
        }
    }
    void reset(std::int64_t k) { set(k, M::id()); }

    T all_prod() const { return !data.empty() ? data.front().product : M::id(); }
    T prod(std::int64_t a, std::int64_t b) const {
        assert(0 <= a && a <= _size);
        assert(0 <= b && b <= _size);
        if (data.empty()) return M::id();
        return prod(a, b, 0, 0, _size);
    }

  private:
    std::vector<_node> data;
    std::int64_t _size;

    T prod(std::int64_t a, std::int64_t b, int idx, std::int64_t l, std::int64_t r) const {
        if (idx == -1 || r <= a || b <= l) return M::id();
        if (a <= l && r <= b) return data[idx].product;

        return M::op(M::op(prod(a, b, data[idx].left, l, (l + r) >> 1),
                           a <= data[idx].index && data[idx].index < b ? data[idx].value : M::id()),
                     prod(a, b, data[idx].right, (l + r) >> 1, r));
    }
};
