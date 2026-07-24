#pragma once
#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

/// @brief 過去の任意時刻を参照できる部分永続 Union-Find
/// @complexity 構築は $O(n)$、代表・連結判定・サイズ取得・併合は $O(\log n)$
struct partially_persistent_union_find {
    /// @brief `n` 個の単集合を時刻 0 の状態として作る
    /// @complexity $O(n)$
    partially_persistent_union_find(int _n) : _now(0), _data(_n, std::vector<std::pair<int, int>>(1, {0, -1})) {}

    /// @brief 現在時刻における `x` の代表を返す
    /// @complexity $O(\log n)$
    int root(int x) const { return root(x, _now); }
    /// @brief 時刻 `t` における `x` の代表を返す
    /// @complexity $O(\log n)$
    int root(int x, int t) const {
        auto p = _data[x].back();
        if (p.first > t || p.second < 0) return x;
        return root(p.second, t);
    }
    /// @brief `root(x, t)` の別名
    /// @complexity $O(\log n)$
    int get_root(int x, int t) const { return root(x, t); }

    /// @brief 時刻 `t` に `x` が集合の代表なら true を返す
    /// @complexity $O(1)$
    bool is_root(int x, int t) const { return _data[x].back().first > t || _data[x].back().second < 0; }

    /// @brief 現在時刻に `x`, `y` が同じ集合なら true を返す
    /// @complexity $O(\log n)$
    bool same(int x, int y) const { return same(x, y, _now); }
    /// @brief 時刻 `t` に `x`, `y` が同じ集合なら true を返す
    /// @complexity $O(\log n)$
    bool same(int x, int y, int t) const { return root(x, t) == root(y, t); }
    /// @brief `same(x, y, t)` の別名
    /// @complexity $O(\log n)$
    bool is_same(int x, int y, int t) const { return same(x, y, t); }

    /// @brief 現在時刻に `x` が属する集合の要素数を返す
    /// @complexity $O(\log n)$
    int size(int x) const { return size(x, _now); }
    /// @brief 時刻 `t` に `x` が属する集合の要素数を返す
    /// @complexity $O(\log n)$
    int size(int x, int t) const {
        x = root(x, t);
        return -std::prev(std::upper_bound(_data[x].begin(), _data[x].end(), std::pair<int, int>{t, _data.size()}))
                    ->second;
    }
    /// @brief `size(x, t)` の別名
    /// @complexity $O(\log n)$
    int get_size(int x, int t) const { return size(x, t); }

    /// @brief 時刻を 1 進めて `x`, `y` の集合を併合する
    /// @return 新たに併合したなら 1、既に同じ集合なら 0
    /// @complexity $O(\log n)$
    int unite(int x, int y) {
        ++_now;
        x = root(x, _now), y = root(y, _now);
        if (x == y) return false;
        auto p = _data[x].back(), q = _data[y].back();
        if (p.second > q.second) std::swap(x, y), std::swap(p, q);
        _data[x].emplace_back(_now, p.second + q.second);
        _data[y].emplace_back(_now, x);
        return true;
    }

  private:
    int _now;
    std::vector<std::vector<std::pair<int, int>>> _data;
};
