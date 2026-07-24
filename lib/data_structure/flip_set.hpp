#pragma once
#include <set>
#include <utility>

/// @brief 要素の有無を反転できる集合
/// @tparam T 要素型。std::set のキーとして比較可能であること。
template <class T>
struct flip_set {
    /// @brief 空の集合を構築する
    /// @complexity $O(1)$
    flip_set() : data() {}

    /// @brief 先頭要素を指すイテレータを返す
    /// @complexity $O(1)$
    const auto begin() const { return data.begin(); }
    /// @brief 先頭要素を指すイテレータを返す
    /// @complexity $O(1)$
    auto begin() { return data.begin(); }
    /// @brief 終端を指すイテレータを返す
    /// @complexity $O(1)$
    const auto end() const { return data.end(); }
    /// @brief 終端を指すイテレータを返す
    /// @complexity $O(1)$
    auto end() { return data.end(); }

    /// @brief 集合が空なら true を返す
    /// @complexity $O(1)$
    bool empty() const { return data.empty(); }
    /// @brief 要素数を返す
    /// @complexity $O(1)$
    int size() const { return data.size(); }

    /// @brief x が集合に含まれていれば true を返す
    /// @param x 検索する要素
    /// @complexity $O(\log n)$
    bool contains(const T &x) const { return data.count(x); }
    /// @brief x が集合に含まれていれば true を返す
    /// @param x 検索する要素
    /// @complexity $O(\log n)$
    bool contains(T &&x) const { return data.count(std::move(x)); }

    /// @brief x があれば削除し、なければ挿入する。操作後に含まれていれば true を返す
    /// @param x 反転する要素
    /// @complexity $O(\log n)$
    bool flip(const T &x) {
        if (data.count(x)) return data.erase(x), false;
        else return data.emplace(x), true;
    }
    /// @brief x があれば削除し、なければ挿入する。操作後に含まれていれば true を返す
    /// @param x 反転する要素
    /// @complexity $O(\log n)$
    bool flip(T &&x) {
        if (data.count(x)) return data.erase(std::move(x)), false;
        else return data.emplace(x), true;
    }

  private:
    std::set<T> data;
};
