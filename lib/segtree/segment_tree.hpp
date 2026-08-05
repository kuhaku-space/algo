#pragma once
#include <algorithm>
#include <bit>
#include <cassert>
#include <utility>
#include <vector>
#include "segtree/monoid.hpp"

/// @brief セグメント木
/// @see https://noshi91.hatenablog.com/entry/2020/04/22/212649
/// @complexity 構築は $O(n)$、更新・区間積・境界探索は $O(\log n)$
template <monoid M>
struct segment_tree {
  private:
    using T = typename M::value_type;

  public:
    /// @brief k番目の要素として振る舞うproxy。値への変換・代入・`chmax` / `chmin` ができる
    /// @complexity 値の取得は $O(1)$、代入は $O(\log n)$
    struct Reference {
      private:
        segment_tree<M> &self;
        int k;

      public:
        Reference(segment_tree<M> &self, int k) : self(self), k(k) {}
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
    segment_tree() : segment_tree(0) {}

    /// @brief n要素をeで初期化する
    /// @complexity $O(n)$
    explicit segment_tree(int n, T e = M::id()) : segment_tree(std::vector<T>(n, e)) {}

    /// @brief 列vから構築する
    /// @complexity $O(n)$
    template <class U>
    explicit segment_tree(const std::vector<U> &v) : _n(v.size()) {
        _size = std::bit_ceil<unsigned>(_n);
        _log = std::countr_zero<unsigned>(_size);
        data = std::vector<T>(_size << 1, M::id());
        for (int i = 0; i < _n; ++i) data[_size + i] = T(v[i]);
        for (int i = _size - 1; i >= 1; --i) update(i);
    }

    /// @brief 確保済み領域を保ったままn要素をeで埋め直す
    /// @complexity $O(n)$
    void assign(int n, T e = M::id()) {
        assert(n <= _size);
        _n = n;
        std::fill(data.begin(), data.end(), M::id());
        if (e != M::id()) {
            std::fill(data.begin() + _size, data.begin() + _size + _n, e);
            for (int i = _size - 1; i >= 1; --i) update(i);
        }
    }

    /// @brief k番目の値をconst参照で返す
    /// @complexity $O(1)$
    const T &operator[](int k) const { return data[k + _size]; }

    /// @brief k番目を参照・代入できるproxyを返す
    /// @complexity 取得は $O(1)$、代入は $O(\log n)$
    Reference operator[](int k) { return Reference(*this, k); }

    /// @brief k番目の値を返す
    /// @complexity $O(1)$
    T at(int k) const { return data[k + _size]; }

    /// @brief k番目の値を返す
    /// @complexity $O(1)$
    T get(int k) const { return data[k + _size]; }

    /// @brief k番目をvalへ変更する
    /// @complexity $O(\log n)$
    void set(int k, T val) {
        assert(0 <= k && k < _n);
        k += _size;
        data[k] = std::move(val);
        for (int i = 1; i <= _log; ++i) update(k >> i);
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
        assert(0 <= a && b <= _n);
        T l = M::id(), r = M::id();
        for (a += _size, b += _size; a < b; a >>= 1, b >>= 1) {
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
        assert(0 <= l && l <= _n);
        assert(f(M::id()));
        if (l == _n) return _n;
        l += _size;
        T sm = M::id();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(M::op(sm, data[l]))) {
                while (l < _size) {
                    l = (2 * l);
                    if (f(M::op(sm, data[l]))) {
                        sm = M::op(sm, data[l]);
                        l++;
                    }
                }
                return l - _size;
            }
            sm = M::op(sm, data[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    /// @brief nから左へ述語fが真である最小境界を返す
    /// @complexity $O(\log n)$
    template <class F>
    int min_left(F f) const {
        return min_left(_n, f);
    }

    /// @brief rから左へ述語fが真である最小境界を返す
    /// @complexity $O(\log n)$
    template <class F>
    int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(M::id()));
        if (r == 0) return 0;
        r += _size;
        T sm = M::id();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(M::op(data[r], sm))) {
                while (r < _size) {
                    r = (2 * r + 1);
                    if (f(M::op(data[r], sm))) {
                        sm = M::op(data[r], sm);
                        r--;
                    }
                }
                return r + 1 - _size;
            }
            sm = M::op(data[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, _size, _log;
    std::vector<T> data;

    void update(int k) { data[k] = M::op(data[2 * k], data[2 * k + 1]); }
};
