#pragma once
#include <concepts>
#include <utility>
#include <vector>

/// @file
/// @brief 素集合データ構造 (Union-Find)
/// @details 要素の集合を併合し、2 要素が同じ連結成分に属するかを管理する。経路圧縮とサイズ併合により、
///          各操作をならし $O(\alpha(n))$ で処理する。
/// @note 代表元は併合順に依存するため、特定の添字になるとは限らない。
/// @note `operator[]` は内部の親または負の集合サイズを直接参照する低レベル API。
///       通常は `root`・`size`・`same` を使う。
/// @note コールバック付きの `unite` は `rank()` の連結成分数を更新しない。
///       `rank()` を使う場合はコールバックなしの `unite(x, y)` を呼ぶ。
/// @note 併合を巻き戻す必要があれば `data_structure/undo_union_find.hpp` を使う。
/// @code
/// #include <iostream>
/// #include "data_structure/union_find.hpp"
///
/// int main() {
///     union_find uf(5);
///     uf.unite(0, 1);
///     uf.unite(1, 3);
///
///     std::cout << uf.same(0, 3) << '\n';  // 0 と 3 は同じ集合
///     std::cout << uf.size(0) << '\n';     // 0 が属する集合の要素数
///     std::cout << uf.rank() << '\n';      // 連結成分数
/// }
/// @endcode

/// @brief 素集合データ構造
/// @details Implement (union by size) + (path compression)
/// @complexity 構築は $O(n)$、代表・連結判定・サイズ取得・併合は償却 $O(\alpha(n))$
/// @see https://github.com/atcoder/ac-library/blob/master/atcoder/dsu.hpp
struct union_find {
    /// @brief 空の Union-Find を作る
    /// @complexity $O(1)$
    union_find() = default;
    /// @brief `n` 個の単集合を作る
    /// @complexity $O(n)$
    explicit union_find(int _n) : _rank(_n), data(_n, -1) {}

    /// @brief 頂点 `x` の内部表現を読み取り専用で返す
    /// @complexity $O(1)$
    const int &operator[](std::size_t x) const { return data[x]; }
    /// @brief 頂点 `x` の内部表現を返す
    /// @complexity $O(1)$
    int &operator[](std::size_t x) { return data[x]; }

    /// @brief `x` の代表を返し、経路圧縮する
    /// @complexity 償却 $O(\alpha(n))$
    int root(int x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
    /// @brief `root(x)` の別名
    /// @complexity 償却 $O(\alpha(n))$
    int get_root(int x) { return root(x); }

    /// @brief `x` が集合の代表なら true を返す
    /// @complexity $O(1)$
    bool is_root(int x) const { return data[x] < 0; }

    /// @brief `x`, `y` が同じ集合なら true を返す
    /// @complexity 償却 $O(\alpha(n))$
    bool same(int x, int y) { return root(x) == root(y); }
    /// @brief `same(x, y)` の別名
    /// @complexity 償却 $O(\alpha(n))$
    bool is_same(int x, int y) { return same(x, y); }

    /// @brief 現在の連結成分数を返す
    /// @complexity $O(1)$
    int rank() { return _rank; }

    /// @brief `x` が属する集合の要素数を返す
    /// @complexity 償却 $O(\alpha(n))$
    int size(int x) { return -(data[root(x)]); }
    /// @brief `size(x)` の別名
    /// @complexity 償却 $O(\alpha(n))$
    int get_size(int x) { return size(x); }

    /// @brief 全ての集合の代表を返す
    /// @complexity $O(n)$
    std::vector<int> leaders() {
        std::vector<int> res;
        for (int i = 0; i < (int)data.size(); ++i) {
            if (is_root(i)) res.emplace_back(i);
        }
        return res;
    }

    /// @brief `x`, `y` の集合を併合する
    /// @return 新たに併合したなら true
    /// @complexity 償却 $O(\alpha(n))$
    bool unite(int x, int y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        --_rank;
        if (data[x] > data[y]) std::swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    /// @brief `x`, `y` を併合し、代表と入れ替えの有無を `f(x, y, swapped)` に渡す
    /// @return 新たに併合したなら true
    /// @complexity 償却 $O(\alpha(n))$（`f` の実行時間を除く）
    template <class F>
    requires std::invocable<F, int, int, bool>
    bool unite(int x, int y, F f) {
        x = root(x), y = root(y);
        bool swapped = false;
        if (x != y) {
            if (data[x] > data[y]) std::swap(x, y), swapped = true;
            data[x] += data[y];
            data[y] = x;
        }
        f(x, y, swapped);
        return x != y;
    }

    /// @brief `x`, `y` を併合し、併合後の代表を `f(x, y)` に渡す
    /// @return 新たに併合したなら true
    /// @complexity 償却 $O(\alpha(n))$（`f` の実行時間を除く）
    template <class F>
    requires std::invocable<F, int, int>
    bool unite(int x, int y, F f) {
        x = root(x), y = root(y);
        if (x != y) {
            if (data[x] > data[y]) std::swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
        f(x, y);
        return x != y;
    }

  private:
    int _rank;
    std::vector<int> data;
};
