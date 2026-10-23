#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>
#include "segtree/monoid.hpp"

/// @brief 動的セグメント木
/// @complexity 点更新・区間積は領域長を $n$ として $O(\log n)$
template <monoid M>
struct DynamicSegmentTree {
  private:
    using T = typename M::value_type;

    struct Node {
        std::int64_t index;
        int left, right;
        T value, product;

        constexpr Node() = default;
        constexpr Node(std::int64_t _index, T _value)
            : index(_index), left(-1), right(-1), value(_value), product(_value) {}
    };

  public:
    /// @brief 添字領域[0,n)の空の木を構築する
    /// @complexity $O(1)$
    DynamicSegmentTree(std::int64_t _n) : data(), n(_n) {}

    /// @brief k番目の値を返す
    /// @complexity $O(\log n)$
    T operator[](std::int64_t k) const {
        assert(0 <= k && k < n);
        if (data.empty()) return M::id();
        int idx = 0;
        std::int64_t l = 0, r = n;
        while (idx != -1) {
            if (k == data[idx].index) return data[idx].value;
            std::int64_t m = (l + r) >> 1;
            if (k < m) r = m, idx = data[idx].left;
            else l = m, idx = data[idx].right;
        }
        return M::id();
    }

    /// @brief k番目の値を返す
    /// @complexity $O(\log n)$
    T at(std::int64_t k) const { return operator[](k); }

    /// @brief k番目の値を返す
    /// @complexity $O(\log n)$
    T get(std::int64_t k) const { return operator[](k); }

    /// @brief k番目をvalへ変更する
    /// @complexity $O(\log n)$
    void set(std::int64_t k, T val) {
        assert(0 <= k && k < n);
        if (data.empty()) {
            data.emplace_back(k, val);
            return;
        }
        int idx = 0;
        std::vector<int> nodes;
        std::int64_t l = 0, r = n;
        while (true) {
            nodes.emplace_back(idx);
            if (k == data[idx].index) {
                data[idx].value = val;
                break;
            }
            std::int64_t m = (l + r) >> 1;
            if (k < m) {
                if (data[idx].index < k) std::swap(k, data[idx].index), std::swap(val, data[idx].value);
                if (data[idx].left == -1) {
                    data[idx].left = data.size();
                    data.emplace_back(k, val);
                    break;
                }
                r = m, idx = data[idx].left;
            } else {
                if (k < data[idx].index) std::swap(k, data[idx].index), std::swap(val, data[idx].value);
                if (data[idx].right == -1) {
                    data[idx].right = data.size();
                    data.emplace_back(k, val);
                    break;
                }
                l = m, idx = data[idx].right;
            }
        }

        std::reverse(nodes.begin(), nodes.end());
        for (auto idx : nodes) {
            data[idx].product =
                M::op(M::op(data[idx].left != -1 ? data[data[idx].left].product : M::id(), data[idx].value),
                      data[idx].right != -1 ? data[data[idx].right].product : M::id());
        }
    }

    /// @brief k番目を単位元へ戻す
    /// @complexity $O(\log n)$
    void reset(std::int64_t k) { set(k, M::id()); }

    /// @brief 全要素の積を返す
    /// @complexity $O(1)$
    T all_prod() const { return !data.empty() ? data.front().product : M::id(); }

    /// @brief 半開区間[a,b)の積を返す
    /// @complexity $O(\log n)$
    T prod(std::int64_t a, std::int64_t b) const {
        assert(0 <= a && a <= n);
        assert(0 <= b && b <= n);
        if (data.empty()) return M::id();
        return prod(a, b, 0, 0, n);
    }

  private:
    std::vector<Node> data;
    std::int64_t n;

    T prod(std::int64_t a, std::int64_t b, int idx, std::int64_t l, std::int64_t r) const {
        if (idx == -1 || r <= a || b <= l) return M::id();
        if (a <= l && r <= b) return data[idx].product;

        return M::op(M::op(prod(a, b, data[idx].left, l, (l + r) >> 1),
                           a <= data[idx].index && data[idx].index < b ? data[idx].value : M::id()),
                     prod(a, b, data[idx].right, (l + r) >> 1, r));
    }
};
