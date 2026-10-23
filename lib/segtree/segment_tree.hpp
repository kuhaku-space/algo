#pragma once
#include <algorithm>
#include <bit>
#include <cassert>
#include <utility>
#include <vector>
#include "segtree/monoid.hpp"

/// @file
/// @brief セグメント木 (SegmentTree)
/// @details モノイドで表せる区間積と点更新を $O(\log n)$ で処理する。和・最小値・最大値に加え、
///          行列積や関数合成のような非可換演算にも利用できる。
/// @details `max_right` / `min_left` により、「区間積が条件を満たす境界」を二分探索なしで求められる。
/// @note `M::op` は結合的で、`M::id()` は左右の単位元であること。可換性は不要。
/// @note 空区間の `prod(l, l)` は `M::id()` を返す。
/// @note `max_right` / `min_left` では `f(M::id()) == true` が必要で、区間を伸ばしたとき
///       `f` が真から偽へ一度だけ変わる単調性を仮定する。
/// @note 非 const の `operator[]` は `Reference` プロキシを返す。`seg[i] = seg[j]` は参照の
///       張り替えではなく値の代入（`std::vector<bool>::reference` と同じ）。
/// @note `Reference` は `chmax` / `chmin` を hidden friend に持つので `chmax(seg[k], val)` と書ける。
///       比較には `operator<` のみを使い、値が変わらないときは `set` を呼ばないので $O(1)$ で済む。
/// @code
/// #include <iostream>
/// #include <vector>
/// #include "segtree/segment_tree.hpp"
///
/// int main() {
///     std::vector<long long> a = {2, 1, 4, 3};
///     SegmentTree<Add<long long>> seg(a);
///     std::cout << seg.prod(1, 4) << '\n';  // 1 + 4 + 3
///
///     seg.set(2, 10);
///     seg[0] = 5;                           // set(0, 5) と同じ
///     std::cout << seg.all_prod() << '\n';
///
///     SegmentTree<Max<long long>> mx(4, 0);
///     chmax(mx[1], 5);                      // v[1] = max(v[1], 5)
///     std::cout << mx.prod(0, 4) << '\n';
/// }
/// @endcode

/// @brief セグメント木
/// @see https://noshi91.hatenablog.com/entry/2020/04/22/212649
/// @complexity 構築は $O(n)$、更新・区間積・境界探索は $O(\log n)$
template <monoid M>
struct SegmentTree {
  private:
    using T = typename M::value_type;

  public:
    /// @brief k番目の要素として振る舞うproxy。値への変換・代入・`chmax` / `chmin` ができる
    /// @complexity 値の取得は $O(1)$、代入は $O(\log n)$
    struct Reference {
      private:
        SegmentTree<M> &self;
        int k;

      public:
        Reference(SegmentTree<M> &self, int k) : self(self), k(k) {}
        Reference(const Reference &) = default;
        // 参照の張り替えではなく値の代入(std::vector<bool>::referenceと同じ)
        Reference &operator=(const Reference &x) { return *this = T(x); }
        Reference &operator=(T x) {
            self.set(k, std::move(x));
            return *this;
        }
        operator T() const { return self.get(k); }
        // chmax(seg[k], x) / chmin(seg[k], x) をADLで解決する
        // (proxyは右辺値なのでchmax(T &, const U &)には束縛できない)
        friend bool chmax(Reference ref, const T &x) {
            if (!(ref.self.get(ref.k) < x)) return false;
            ref.self.set(ref.k, x);
            return true;
        }
        friend bool chmin(Reference ref, const T &x) {
            if (!(x < ref.self.get(ref.k))) return false;
            ref.self.set(ref.k, x);
            return true;
        }
    };

  public:
    /// @brief 空の木を構築する
    /// @complexity $O(1)$
    SegmentTree() : SegmentTree(0) {}

    /// @brief n要素をeで初期化する
    /// @complexity $O(n)$
    explicit SegmentTree(int _n, T e = M::id()) : SegmentTree(std::vector<T>(_n, e)) {}

    /// @brief 列vから構築する
    /// @complexity $O(n)$
    template <class U>
    explicit SegmentTree(const std::vector<U> &v) : n(v.size()) {
        size = std::bit_ceil<unsigned>(n);
        log = std::countr_zero<unsigned>(size);
        data = std::vector<T>(size << 1, M::id());
        for (int i = 0; i < n; ++i) data[size + i] = T(v[i]);
        for (int i = size - 1; i >= 1; --i) update(i);
    }

    /// @brief 確保済み領域を保ったままn要素をeで埋め直す
    /// @complexity $O(n)$
    void assign(int _n, T e = M::id()) {
        assert(_n <= size);
        n = _n;
        std::fill(data.begin(), data.end(), M::id());
        if (e != M::id()) {
            std::fill(data.begin() + size, data.begin() + size + n, e);
            for (int i = size - 1; i >= 1; --i) update(i);
        }
    }

    /// @brief k番目の値をconst参照で返す
    /// @complexity $O(1)$
    const T &operator[](int k) const { return data[k + size]; }

    /// @brief k番目を参照・代入できるproxyを返す
    /// @complexity 取得は $O(1)$、代入は $O(\log n)$
    Reference operator[](int k) { return Reference(*this, k); }

    /// @brief k番目の値を返す
    /// @complexity $O(1)$
    T at(int k) const { return data[k + size]; }

    /// @brief k番目の値を返す
    /// @complexity $O(1)$
    T get(int k) const { return data[k + size]; }

    /// @brief k番目をvalへ変更する
    /// @complexity $O(\log n)$
    void set(int k, T val) {
        assert(0 <= k && k < n);
        k += size;
        data[k] = std::move(val);
        for (int i = 1; i <= log; ++i) update(k >> i);
    }

    /// @brief k番目を単位元へ戻す
    /// @complexity $O(\log n)$
    void reset(int k) { set(k, M::id()); }

    /// @brief 全要素の積を返す
    /// @complexity $O(1)$
    T all_prod() const { return data[1]; }

    /// @brief 半開区間[a,b)の積を返す
    /// @complexity $O(\log n)$
    T prod(int a, int b) const {
        assert(0 <= a && b <= n);
        T l = M::id(), r = M::id();
        for (a += size, b += size; a < b; a >>= 1, b >>= 1) {
            if (a & 1) l = M::op(l, data[a++]);
            if (b & 1) r = M::op(data[--b], r);
        }
        return M::op(l, r);
    }

    /// @brief 0から右へ述語fが真である最大境界を返す
    /// @complexity $O(\log n)$
    template <class F>
    int max_right(F f) const {
        return max_right(0, f);
    }

    /// @brief lから右へ述語fが真である最大境界を返す
    /// @complexity $O(\log n)$
    template <class F>
    int max_right(int l, F f) const {
        assert(0 <= l && l <= n);
        assert(f(M::id()));
        if (l == n) return n;
        l += size;
        T sm = M::id();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(M::op(sm, data[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(M::op(sm, data[l]))) {
                        sm = M::op(sm, data[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = M::op(sm, data[l]);
            l++;
        } while ((l & -l) != l);
        return n;
    }

    /// @brief nから左へ述語fが真である最小境界を返す
    /// @complexity $O(\log n)$
    template <class F>
    int min_left(F f) const {
        return min_left(n, f);
    }

    /// @brief rから左へ述語fが真である最小境界を返す
    /// @complexity $O(\log n)$
    template <class F>
    int min_left(int r, F f) const {
        assert(0 <= r && r <= n);
        assert(f(M::id()));
        if (r == 0) return 0;
        r += size;
        T sm = M::id();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(M::op(data[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(M::op(data[r], sm))) {
                        sm = M::op(data[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = M::op(data[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int n, size, log;
    std::vector<T> data;

    void update(int k) { data[k] = M::op(data[2 * k], data[2 * k + 1]); }
};
