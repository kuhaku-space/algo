#pragma once
#include <functional>
#include <queue>
#include <utility>

/// @brief 削除可能優先度付きキュー
template <class T, class Comp = std::less<>>
struct erasable_priority_queue {
    /// @brief 空か返す
    /// @complexity $O(1)$
    bool empty() const { return a.empty(); }

    /// @brief 論理的な要素数を返す
    /// @complexity $O(1)$
    int size() const { return a.size() - b.size(); }

    /// @brief 最上位の値を返す
    /// @complexity $O(1)$
    T top() const { return a.top(); }

    /// @brief 値を追加する
    /// @complexity $O(\log n)$
    void insert(const T &x) { a.push(x); }

    /// @brief 値をムーブして追加する
    /// @complexity $O(\log n)$
    void insert(T &&x) { a.push(std::move(x)); }

    /// @brief 値を追加する
    /// @complexity $O(\log n)$
    void push(const T &x) { a.push(x); }

    /// @brief 値をムーブして追加する
    /// @complexity $O(\log n)$
    void push(T &&x) { a.push(std::move(x)); }

    /// @brief 値を直接構築して追加する
    /// @complexity $O(\log n)$
    template <typename... Args>
    void emplace(Args &&...args) {
        a.emplace(std::forward<Args>(args)...);
    }

    /// @brief 最上位の値を削除する
    /// @complexity 償却 $O(\log n)$
    void pop() { erase(a.top()); }

    /// @brief 指定した値を1つ遅延削除する
    /// @complexity 償却 $O(\log n)$
    void erase(const T &x) {
        b.push(x);
        while (!b.empty() && a.top() == b.top()) { a.pop(), b.pop(); }
    }
    /// @brief 指定した値を1つ遅延削除する
    /// @complexity 償却 $O(\log n)$
    void erase(T &&x) {
        b.push(std::move(x));
        while (!b.empty() && a.top() == b.top()) { a.pop(), b.pop(); }
    }

  private:
    std::priority_queue<T, std::vector<T>, Comp> a, b;
};
