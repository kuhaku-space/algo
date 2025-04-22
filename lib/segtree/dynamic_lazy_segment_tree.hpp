#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>
#include "segtree/monoid.hpp"

/// @brief 動的遅延評価セグメント木
template <class S, class F>
struct dynamic_lazy_segment_tree {
  private:
    using T = typename S::value_type;
    using U = typename F::value_type;

    struct _node {
        T value;
        U lazy;
        int left, right;

        constexpr _node() : value(), lazy(F::id()), left(-1), right(-1) {}
        constexpr _node(T _value) : value(_value), lazy(F::id()), left(-1), right(-1) {}
    };

  public:
    dynamic_lazy_segment_tree(std::int64_t n) : data(), _size(n) {}

    T operator[](std::int64_t k) {
        assert(0 <= k && k < _size);
        return prod(k, k + 1);
    }
    T at(std::int64_t k) { return operator[](k); }
    T get(std::int64_t k) { return operator[](k); }

    void set(std::int64_t k, T x) {
        assert(0 <= k && k < _size);
        set(k, x, data.empty() ? -1 : 0, 0, _size);
    }
    void reset(std::int64_t k) { set(k, S::id()); }

    void apply(std::int64_t a, std::int64_t b, U f) {
        assert(0 <= a && a <= b && b <= _size);
        apply(a, b, f, data.empty() ? -1 : 0, 0, _size);
    }

    T all_prod() const { return data.empty() ? S::id(_size) : data[0].value; }
    T prod(std::int64_t a, std::int64_t b) {
        assert(0 <= a && a <= _size);
        assert(0 <= b && b <= _size);
        if (data.empty()) return S::id(_size);
        return prod(a, b, 0, 0, _size);
    }

  private:
    std::vector<_node> data;
    std::int64_t _size;

    int set(std::int64_t k, T x, int idx, std::int64_t l, std::int64_t r) {
        if (l + 1 == r) {
            if (idx == -1) {
                idx = data.size();
                data.emplace_back(x);
            } else {
                data[idx].value = x;
            }
            return idx;
        }
        std::int64_t m = (l + r) >> 1;
        if (idx == -1) {
            idx = data.size();
            data.emplace_back(S::id(r - l));
        }
        push(idx, l, r);
        if (k < m) data[idx].left = set(k, x, data[idx].left, k, x, l, m);
        else data[idx].right = set(k, x, data[idx].right, m, r);
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
