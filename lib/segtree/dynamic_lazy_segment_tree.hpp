#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>
#include "segtree/monoid.hpp"

/// @brief 動的遅延評価セグメント木
/// @tparam S データのモノイド
/// @tparam F 作用素モノイド（op が作用素の合成、f が値への作用）
/// @complexity 点更新・区間作用・区間積は領域長を $n$ として $O(\log n)$
template <class S, class F>
requires monoid<S> && monoid<F> && acts_on<F, typename S::value_type>
struct DynamicLazySegmentTree {
  private:
    using T = typename S::value_type;
    using U = typename F::value_type;

    struct Node {
        T value;
        U lazy;
        int left, right;

        constexpr Node() : value(), lazy(F::id()), left(-1), right(-1) {}
        constexpr Node(T _value) : value(_value), lazy(F::id()), left(-1), right(-1) {}
    };

  public:
    /// @brief 添字領域[0,n)の空の木を構築する
    /// @complexity $O(1)$
    DynamicLazySegmentTree(std::int64_t _n) : data(), n(_n) {}

    /// @brief k番目の値を返す
    /// @complexity $O(\log n)$
    T operator[](std::int64_t k) {
        assert(0 <= k && k < n);
        return prod(k, k + 1);
    }

    /// @brief k番目の値を返す
    /// @complexity $O(\log n)$
    T at(std::int64_t k) { return operator[](k); }

    /// @brief k番目の値を返す
    /// @complexity $O(\log n)$
    T get(std::int64_t k) { return operator[](k); }

    /// @brief k番目をvalへ変更する
    /// @complexity $O(\log n)$
    void set(std::int64_t k, T val) {
        assert(0 <= k && k < n);
        set(k, val, data.empty() ? -1 : 0, 0, n);
    }

    /// @brief k番目を単位元へ戻す
    /// @complexity $O(\log n)$
    void reset(std::int64_t k) { set(k, S::id()); }

    /// @brief 半開区間[a,b)にfを作用する
    /// @complexity $O(\log n)$
    void apply(std::int64_t a, std::int64_t b, U f) {
        assert(0 <= a && a <= b && b <= n);
        apply(a, b, f, data.empty() ? -1 : 0, 0, n);
    }

    /// @brief 全要素の積を返す
    /// @complexity $O(1)$
    T all_prod() const { return data.empty() ? S::id(n) : data[0].value; }

    /// @brief 半開区間[a,b)の積を返す
    /// @complexity $O(\log n)$
    T prod(std::int64_t a, std::int64_t b) {
        assert(0 <= a && a <= n);
        assert(0 <= b && b <= n);
        if (data.empty()) return S::id(n);
        return prod(a, b, 0, 0, n);
    }

  private:
    std::vector<Node> data;
    std::int64_t n;

    int set(std::int64_t k, T val, int idx, std::int64_t l, std::int64_t r) {
        if (l + 1 == r) {
            if (idx == -1) {
                idx = data.size();
                data.emplace_back(val);
            } else {
                data[idx].value = val;
            }
            return idx;
        }
        std::int64_t m = (l + r) >> 1;
        if (idx == -1) {
            idx = data.size();
            data.emplace_back(S::id(r - l));
        }
        push(idx, l, r);
        if (k < m) data[idx].left = set(k, val, data[idx].left, l, m);
        else data[idx].right = set(k, val, data[idx].right, m, r);
        return update(idx, l, r);
    }

    int apply(std::int64_t a, std::int64_t b, U f, int idx, std::int64_t l, std::int64_t r) {
        if (r <= a || b <= l) return idx;
        if (a <= l && r <= b) return all_apply(idx, f, l, r);
        if (idx == -1) {
            idx = data.size();
            data.emplace_back(S::id(r - l));
        }
        push(idx, l, r);
        std::int64_t m = (l + r) >> 1;
        data[idx].left = apply(a, b, f, data[idx].left, l, m);
        data[idx].right = apply(a, b, f, data[idx].right, m, r);
        return update(idx, l, r);
    }

    T prod(std::int64_t a, std::int64_t b, int idx, std::int64_t l, std::int64_t r) {
        if (idx == -1 || r <= a || b <= l) return S::id(r - l);
        if (a <= l && r <= b) return data[idx].value;
        push(idx, l, r);
        std::int64_t m = (l + r) >> 1;
        return S::op(prod(a, b, data[idx].left, l, m), prod(a, b, data[idx].right, m, r));
    }

    int update(int k, std::int64_t l, std::int64_t r) {
        std::int64_t m = (l + r) >> 1;
        data[k].value = S::op(data[k].left == -1 ? S::id(m - l) : data[data[k].left].value,
                              data[k].right == -1 ? S::id(r - m) : data[data[k].right].value);
        return k;
    }
    int all_apply(int k, U f, std::int64_t l, std::int64_t r) {
        if (k == -1) {
            k = data.size();
            data.emplace_back(S::id(r - l));
        }
        data[k].value = F::f(f, data[k].value);
        data[k].lazy = F::op(f, data[k].lazy);
        return k;
    }
    void push(int k, std::int64_t l, std::int64_t r) {
        std::int64_t m = (l + r) >> 1;
        data[k].left = all_apply(data[k].left, data[k].lazy, l, m);
        data[k].right = all_apply(data[k].right, data[k].lazy, m, r);
        data[k].lazy = F::id();
    }
};
