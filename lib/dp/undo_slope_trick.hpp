#pragma once
#include <algorithm>
#include <functional>
#include <stack>
#include <utility>
#include "heap/erasable_priority_queue.hpp"

/// @brief Undo 可能 slope trick
/// @details 以下では N を、これまでに行った add_x_minus_a / add_a_minus_x
///          （add_abs は内部で両方呼ぶため 2 回分）の呼び出し回数とする
template <class T>
struct UndoSlopeTrick {
    /// @brief $f(x)=0$ の状態を構築する
    /// @complexity $O(1)$
    UndoSlopeTrick() = default;

    /// @brief 最小値を取る x の 1 つを返す
    /// @complexity O(1)
    [[nodiscard]] T min_x() const { return l.top(); }
    /// @brief 関数の最小値を返す
    /// @complexity O(1)
    [[nodiscard]] T min_value() const { return min_f; }

    /// @brief Add f(x) = a
    /// @complexity O(1)
    void add_const(T a) {
        history.emplace(0, min_f);
        min_f += a;
    }

    /// @brief Add f(x) = max(0, x - a)
    /// @complexity O(log N)
    void add_x_minus_a(T a) {
        if (!l.empty()) {
            history.emplace(0, min_f);
            min_f += std::max(T(), l.top() - a);
        }
        history.emplace(1, a);
        l.insert(a);
        T x = l.top();
        history.emplace(2, x);
        l.erase(x);
        history.emplace(3, x);
        r.insert(x);
    }

    /// @brief Add f(x) = max(0, a - x)
    /// @complexity O(log N)
    void add_a_minus_x(T a) {
        if (!r.empty()) {
            history.emplace(0, min_f);
            min_f += std::max(T(), a - r.top());
        }
        history.emplace(3, a);
        r.insert(a);
        T x = r.top();
        history.emplace(4, x);
        r.erase(x);
        history.emplace(1, x);
        l.insert(x);
    }

    /// @brief Add f(x) = abs(x - a) = max(0, x - a) + max(0, a - x)
    /// @complexity O(log N)
    void add_abs(T a) {
        add_x_minus_a(a);
        add_a_minus_x(a);
    }

    /// @brief 直前の add_* 操作の内部履歴を 1 件取り消す
    /// @complexity O(log N)
    void undo() {
        auto [type, val] = history.top();
        history.pop();
        if (type == 0) min_f = val;
        else if (type == 1) l.erase(val);
        else if (type == 2) l.insert(val);
        else if (type == 3) r.erase(val);
        else r.insert(val);
    }

    /// @brief 現在の状態を表す履歴位置を返す
    /// @complexity O(1)
    [[nodiscard]] int snapshot() const { return history.size(); }

    /// @brief snapshot() で取得した時点まで巻き戻す
    /// @complexity O((現在の履歴サイズ - t) log N)
    void rollback(int t = 0) {
        while ((int)history.size() > t) undo();
    }

  private:
    T min_f{};
    erasable_priority_queue<T> l;
    erasable_priority_queue<T, std::greater<>> r;
    std::stack<std::pair<int, T>> history;
};
