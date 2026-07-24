#pragma once
#include <algorithm>
#include <iterator>
#include <vector>

/// @brief Mex
struct minimum_excluded {
    /// @brief 空の列に対するMex管理器を構築する
    /// @complexity $O(1)$
    minimum_excluded() : n(), _size(), exists(64), v() {}

    /// @brief 現在のMexを返す
    /// @complexity $O(1)$
    constexpr int operator()() const noexcept { return n; }

    /// @brief 現在のMexを返す
    /// @complexity $O(1)$
    constexpr int get() const noexcept { return n; }

    /// @brief 値を1つ追加する
    /// @complexity 通常 $O(1)$、内部配列の拡張時は保留要素数を $q$ として $O(q)$
    void add(int x) {
        if (x < 0) return;
        ++_size;
        if (_size == (int)exists.size()) {
            exists.resize(_size << 1);
            std::erase_if(v, [&](int y) {
                if (y < (int)exists.size()) {
                    if (exists[y]) --_size;
                    else exists[y] = true;
                    return true;
                }
                return false;
            });
        }
        if (x < (int)exists.size()) {
            if (exists[x]) --_size;
            else exists[x] = true;
        } else {
            v.emplace_back(x);
        }
        while (exists[n]) ++n;
    }

  private:
    int n, _size;
    std::vector<bool> exists;
    std::vector<int> v;
};
