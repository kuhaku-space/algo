#pragma once
#include <algorithm>
#include <iterator>
#include <vector>

/// @brief Mex
struct Mex {
    /// @brief 空の列に対するMex管理器を構築する
    /// @complexity $O(1)$
    Mex() : mex(), distinct_count(), exists(64), pending() {}

    /// @brief 現在のMexを返す
    /// @complexity $O(1)$
    constexpr int operator()() const noexcept { return mex; }

    /// @brief 現在のMexを返す
    /// @complexity $O(1)$
    constexpr int get() const noexcept { return mex; }

    /// @brief 値を1つ追加する
    /// @complexity 通常 $O(1)$、内部配列の拡張時は保留要素数を $q$ として $O(q)$
    void add(int x) {
        if (x < 0) return;
        ++distinct_count;
        if (distinct_count == (int)exists.size()) {
            exists.resize(distinct_count << 1);
            std::erase_if(pending, [&](int y) {
                if (y < (int)exists.size()) {
                    if (exists[y]) --distinct_count;
                    else exists[y] = true;
                    return true;
                }
                return false;
            });
        }
        if (x < (int)exists.size()) {
            if (exists[x]) --distinct_count;
            else exists[x] = true;
        } else {
            pending.emplace_back(x);
        }
        while (exists[mex]) ++mex;
    }

  private:
    int mex, distinct_count;
    std::vector<bool> exists;
    // exists の範囲外の値。exists を広げたときにまとめて取り込む。
    std::vector<int> pending;
};
