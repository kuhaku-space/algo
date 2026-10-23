#pragma once
#include <bit>
#include <cassert>
#include <vector>
#include "segtree/monoid.hpp"

/// @brief 遅延評価セグメント木
/// @see https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp
/// @tparam S データのモノイド
/// @tparam F 作用素モノイド（op が作用素の合成、f が値への作用）
/// @complexity 構築は $O(n)$、更新・作用・区間積・境界探索は $O(\log n)$
template <class S, class F>
requires monoid<S> && monoid<F> && acts_on<F, typename S::value_type>
struct LazySegmentTree {
  private:
    using T = typename S::value_type;
    using U = typename F::value_type;

  public:
    /// @brief 空の木を構築する
    /// @complexity $O(1)$
    LazySegmentTree() : LazySegmentTree(0) {}

    /// @brief n要素をeで初期化する
    /// @complexity $O(n)$
    explicit LazySegmentTree(int _n, T e = S::id()) : LazySegmentTree(std::vector<T>(_n, e)) {}

    /// @brief 列vから構築する
    /// @complexity $O(n)$
    explicit LazySegmentTree(const std::vector<T> &v) : n(int(v.size())) {
        size = std::bit_ceil<unsigned>(n);
        log = std::countr_zero<unsigned>(size);
        data = std::vector<T>(2 * size, S::id());
        lazy = std::vector<U>(size, F::id());
        for (int i = 0; i < n; i++) data[size + i] = v[i];
        for (int i = size - 1; i >= 1; --i) update(i);
    }

    /// @brief k番目をvalへ変更する
    /// @complexity $O(\log n)$
    void set(int k, T val) {
        assert(0 <= k && k < n);
        k += size;
        for (int i = log; i >= 1; --i) push(k >> i);
        data[k] = val;
        for (int i = 1; i <= log; ++i) update(k >> i);
    }

    /// @brief k番目の値を返す
    /// @complexity $O(\log n)$
    T at(int k) { return get(k); }

    /// @brief k番目の値を返す
    /// @complexity $O(\log n)$
    T get(int k) {
        assert(0 <= k && k < n);
        k += size;
        for (int i = log; i >= 1; --i) push(k >> i);
        return data[k];
    }

    /// @brief k番目にfを作用する
    /// @complexity $O(\log n)$
    void apply(int k, U f) {
        assert(0 <= k && k < n);
        k += size;
        for (int i = log; i >= 1; --i) push(k >> i);
        data[k] = F::f(f, data[k]);
        for (int i = 1; i <= log; ++i) update(k >> i);
    }

    /// @brief 半開区間[a,b)にfを作用する
    /// @complexity $O(\log n)$
    void apply(int a, int b, U f) {
        assert(0 <= a && a <= b && b <= n);
        if (a == b) return;

        a += size, b += size;

        for (int i = log; i >= 1; --i) {
            if (((a >> i) << i) != a) push(a >> i);
            if (((b >> i) << i) != b) push((b - 1) >> i);
        }

        int a2 = a, b2 = b;
        while (a < b) {
            if (a & 1) all_apply(a++, f);
            if (b & 1) all_apply(--b, f);
            a >>= 1, b >>= 1;
        }
        a = a2, b = b2;

        for (int i = 1; i <= log; i++) {
            if (((a >> i) << i) != a) update(a >> i);
            if (((b >> i) << i) != b) update((b - 1) >> i);
        }
    }

    /// @brief 半開区間[a,b)の積を返す
    /// @complexity $O(\log n)$
    T prod(int a, int b) {
        assert(0 <= a && a <= b && b <= n);
        if (a == b) return S::id();

        a += size, b += size;

        for (int i = log; i >= 1; --i) {
            if (((a >> i) << i) != a) push(a >> i);
            if (((b >> i) << i) != b) push((b - 1) >> i);
        }

        T sml = S::id(), smr = S::id();
        while (a < b) {
            if (a & 1) sml = S::op(sml, data[a++]);
            if (b & 1) smr = S::op(data[--b], smr);
            a >>= 1, b >>= 1;
        }

        return S::op(sml, smr);
    }

    /// @brief 全要素の積を返す
    /// @complexity $O(1)$
    T all_prod() const { return data[1]; }

    /// @brief lから右へ積がval以下である最大境界を返す
    /// @complexity $O(\log n)$
    int max_right(int l, T val) {
        auto f = [&val](T v) { return !(val < v); };
        return max_right(l, f);
    }

    /// @brief lから右へ述語gが真である最大境界を返す
    /// @complexity $O(\log n)$
    template <class G>
    int max_right(int l, G g) {
        assert(0 <= l && l <= n);
        assert(g(S::id()));
        if (l == n) return n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        T sm = S::id();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(S::op(sm, data[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(S::op(sm, data[l]))) {
                        sm = S::op(sm, data[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = S::op(sm, data[l]);
            l++;
        } while ((l & -l) != l);
        return n;
    }

    /// @brief rから左へ積がval以下である最小境界を返す
    /// @complexity $O(\log n)$
    int min_left(int r, T val) {
        auto f = [&val](T v) { return !(val < v); };
        return min_left(r, f);
    }

    /// @brief rから左へ述語gが真である最小境界を返す
    /// @complexity $O(\log n)$
    template <class G>
    int min_left(int r, G g) {
        assert(0 <= r && r <= n);
        assert(g(S::id()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = S::id();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(S::op(data[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(S::op(data[r], sm))) {
                        sm = S::op(data[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = S::op(data[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int n, size, log;
    std::vector<T> data;
    std::vector<U> lazy;

    void update(int k) { data[k] = S::op(data[2 * k], data[2 * k + 1]); }
    void all_apply(int k, U f) {
        data[k] = F::f(f, data[k]);
        if (k < size) lazy[k] = F::op(f, lazy[k]);
    }
    void push(int k) {
        all_apply(2 * k, lazy[k]);
        all_apply(2 * k + 1, lazy[k]);
        lazy[k] = F::id();
    }
};
