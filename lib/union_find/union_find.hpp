#pragma once
#include <concepts>
#include <utility>
#include <vector>

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
