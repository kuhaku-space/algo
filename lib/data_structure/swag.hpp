#pragma once
#include <stack>
#include "segtree/monoid.hpp"

/// @brief Sliding Window Aggregation
template <monoid M>
struct sliding_window_aggregation {
  private:
    using T = typename M::value_type;

  public:
    /// @brief 空のSWAGを構築する
    /// @complexity $O(1)$
    sliding_window_aggregation() : back_total(M::id()), front(), back() { front.emplace(M::id()); }

    /// @brief 空か返す
    /// @complexity $O(1)$
    bool empty() const { return front.empty() && back.empty(); }

    /// @brief 要素数を返す
    /// @complexity $O(1)$
    int size() const { return front.size() + back.size() - 1; }

    /// @brief 全要素のモノイド積を返す
    /// @complexity $O(1)$
    T fold() const { return M::op(back_total, front.top()); }

    /// @brief 末尾へ値を追加する
    /// @complexity $O(1)$
    void emplace(T val) {
        back.emplace(val);
        back_total = M::op(val, back_total);
    }
    /// @brief 末尾へ値を追加する
    /// @complexity $O(1)$
    void push(T val) { emplace(val); }

    /// @brief 先頭の値を削除する
    /// @complexity 償却 $O(1)$
    void pop() {
        if (front.size() == 1) {
            while (!back.empty()) {
                front.emplace(M::op(front.top(), back.top()));
                back.pop();
            }
            back_total = M::id();
        }
        front.pop();
    }

  private:
    T back_total;
    std::stack<T> front, back;
};
