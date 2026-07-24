#pragma once
#include <deque>
#include <stack>
#include <utility>

/// @brief Undo可能両端キュー
template <class T>
struct undo_deque {
    /// @brief 先頭の値を返す
    /// @complexity $O(1)$
    T front() const { return data.front(); }

    /// @brief 末尾の値を返す
    /// @complexity $O(1)$
    T back() const { return data.back(); }

    /// @brief 空か返す
    /// @complexity $O(1)$
    bool empty() const { return data.empty(); }

    /// @brief 要素数を返す
    /// @complexity $O(1)$
    int size() const { return data.size(); }

    /// @brief 先頭へ値を追加する
    /// @complexity $O(1)$
    void emplace_front(T x) {
        history.emplace(0, x);
        data.emplace_front(x);
    }

    /// @brief 末尾へ値を追加する
    /// @complexity $O(1)$
    void emplace_back(T x) {
        history.emplace(1, x);
        data.emplace_back(x);
    }

    /// @brief 先頭の値を削除する
    /// @complexity $O(1)$
    void pop_front() {
        history.emplace(2, data.front());
        data.pop_front();
    }

    /// @brief 末尾の値を削除する
    /// @complexity $O(1)$
    void pop_back() {
        history.emplace(3, data.back());
        data.pop_back();
    }

    /// @brief 直前の更新を取り消す
    /// @complexity $O(1)$
    void undo() {
        auto [x, y] = history.top();
        history.pop();
        if (x == 0) data.pop_front();
        else if (x == 1) data.pop_back();
        else if (x == 2) data.emplace_front(y);
        else data.emplace_back(y);
    }

    /// @brief 現在の履歴位置を返す
    /// @complexity $O(1)$
    int snapshot() const { return history.size(); }

    /// @brief 指定した履歴位置まで巻き戻す
    /// @complexity 取り消す更新数を $k$ として $O(k)$
    void rollback(int x = 0) {
        while (x < (int)history.size()) undo();
    }

  private:
    std::deque<T> data;
    std::stack<std::pair<int, T>> history;
};
