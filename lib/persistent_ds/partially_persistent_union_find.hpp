#pragma once
#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

/// @brief 部分永続Union-Find
struct partially_persistent_union_find {
    partially_persistent_union_find(int _n) : _now(0), _data(_n, std::vector<std::pair<int, int>>(1, {0, -1})) {}

    int root(int x) const { return root(x, _now); }
    int root(int x, int t) const {
        auto p = _data[x].back();
        if (p.first > t || p.second < 0) return x;
        return root(p.second, t);
    }
    int get_root(int x, int t) const { return root(x, t); }

    bool is_root(int x, int t) const { return _data[x].back().first > t || _data[x].back().second < 0; }

    bool same(int x, int y) const { return same(x, y, _now); }
    bool same(int x, int y, int t) const { return root(x, t) == root(y, t); }
    bool is_same(int x, int y, int t) const { return same(x, y, t); }

    int size(int x) const { return size(x, _now); }
    int size(int x, int t) const {
        x = root(x, t);
        return -std::prev(std::upper_bound(_data[x].begin(), _data[x].end(), std::pair<int, int>{t, _data.size()}))
                    ->second;
    }
    int get_size(int x, int t) const { return size(x, t); }

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
