#pragma once
#include <cassert>
#include <functional>
#include <utility>
#include "heap/erasable_priority_queue.hpp"

/// @brief 多重集合の小さい方または大きい方からk個の総和を管理する
/// @details `minimum_sum<T>` は最小k個、`maximum_sum<T>` は最大k個を管理する。
/// @complexity `insert`・`erase` は $O(\log n)$、`query`・`sum` は $O(1)$。
/// `set_k` は $O((1+|\Delta k|)\log n)$
template <typename T, class Comp, class RComp>
struct priority_k_sum {
    /// @brief 集約対象の要素数を `k` として空の多重集合を作る
    /// @complexity $O(1)$
    priority_k_sum(int k) : _k(k), _sum() { assert(_k >= 0); }

    /// @brief 多重集合の全要素数を返す
    /// @complexity $O(1)$
    int size() const { return in.size() + out.size(); }

    /// @brief 比較順で先頭の `k` 個の総和を返す
    /// @complexity $O(1)$
    T query() const { return _sum; }
    /// @brief `query()` の別名
    /// @complexity $O(1)$
    T sum() const { return _sum; }

    /// @brief 現在の `k` を返す
    /// @complexity $O(1)$
    int get_k() const { return _k; }

    /// @brief 集約対象の要素数を `x` に変更する
    /// @complexity $O((1+|x-k|)\log n)$
    void set_k(int x) {
        assert(x >= 0);
        _k = x;
        modify();
    }

    /// @brief 要素 `x` を追加する
    /// @complexity $O(\log n)$
    void insert(const T &x) {
        _sum += x, in.emplace(x);
        modify();
    }
    /// @brief 要素 `x` をムーブして追加する
    /// @complexity $O(\log n)$
    void insert(T &&x) {
        _sum += x, in.emplace(std::move(x));
        modify();
    }

    /// @brief 要素 `x` を 1 個削除する
    /// @complexity $O(\log n)$
    void erase(const T &x) {
        assert(size());
        if (!in.empty() && !Comp()(in.top(), x)) _sum -= x, in.erase(x);
        else out.erase(x);
        modify();
    }
    /// @brief 要素 `x` を 1 個削除する
    /// @complexity $O(\log n)$
    void erase(T &&x) {
        assert(size());
        if (!in.empty() && !Comp()(in.top(), x)) _sum -= x, in.erase(std::move(x));
        else out.erase(std::move(x));
        modify();
    }

    /// @brief 集約対象側の境界要素を返す
    /// @complexity $O(1)$
    T last_in() const { return in.top(); }
    /// @brief 集約対象外側の境界要素を返す
    /// @complexity $O(1)$
    T last_out() const { return out.top(); }

  private:
    int _k;
    T _sum;
    erasable_priority_queue<T, Comp> in;
    erasable_priority_queue<T, RComp> out;
    void modify() {
        while (in.size() < _k && !out.empty()) {
            auto p = out.top();
            _sum += p, in.emplace(p);
            out.pop();
        }
        while (in.size() > _k) {
            auto p = in.top();
            _sum -= p, out.emplace(p);
            in.pop();
        }
    }
};

/// @brief 多重集合の最大 `k` 要素の総和を管理する型
/// @complexity 型エイリアスのため実行時コストなし
template <typename T>
using maximum_sum = priority_k_sum<T, std::greater<T>, std::less<T>>;
/// @brief 多重集合の最小 `k` 要素の総和を管理する型
/// @complexity 型エイリアスのため実行時コストなし
template <typename T>
using minimum_sum = priority_k_sum<T, std::less<T>, std::greater<T>>;
