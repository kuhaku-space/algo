#pragma once
#include <utility>
#include "persistent_ds/persistent_array.hpp"

/// @brief 各バージョンを保持する完全永続 Union-Find
/// @details 併合は元の状態を変更せず、新しい Union-Find を返す。
/// @complexity 代表・連結判定・サイズ取得・併合は $O(\log^2 n)$
struct persistent_union_find {
    /// @brief 空の Union-Find を作る
    /// @complexity $O(1)$
    constexpr persistent_union_find() : data() {}
    /// @brief 永続配列 `_data` を内部状態とする Union-Find を作る
    /// @complexity $O(1)$
    persistent_union_find(const persistent_array<int> &_data) : data(_data) {}
    /// @brief `n` 個の単集合を作る
    /// @complexity $O(n\log n)$
    persistent_union_find(int n) : data(n, -1) {}

    /// @brief `x` の代表を返す
    /// @complexity $O(\log^2 n)$
    int root(int x) const {
        int y = data[x];
        return y < 0 ? x : root(y);
    }
    /// @brief `root(x)` の別名
    /// @complexity $O(\log^2 n)$
    int get_root(int x) const { return root(x); }

    /// @brief `x` が集合の代表なら true を返す
    /// @complexity $O(\log n)$
    bool is_root(int x) const { return data[x] < 0; }

    /// @brief `x`, `y` を併合した新しいバージョンを返す
    /// @complexity $O(\log^2 n)$
    persistent_union_find unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return *this;
        int a = data[x], b = data[y];
        if (a > b) std::swap(x, y);
        return persistent_union_find(data.set(x, a + b).set(y, x));
    }

    /// @brief `x` が属する集合の要素数を返す
    /// @complexity $O(\log^2 n)$
    int size(int x) const { return -(data[root(x)]); }
    /// @brief `size(x)` の別名
    /// @complexity $O(\log^2 n)$
    int get_size(int x) const { return size(x); }

    /// @brief `x`, `y` が同じ集合なら true を返す
    /// @complexity $O(\log^2 n)$
    bool same(int x, int y) const { return root(x) == root(y); }
    /// @brief `same(x, y)` の別名
    /// @complexity $O(\log^2 n)$
    bool is_same(int x, int y) const { return same(x, y); }

  private:
    persistent_array<int> data;
};
