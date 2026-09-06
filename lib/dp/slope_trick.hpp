#pragma once

#include <algorithm>
#include <concepts>
#include <functional>
#include <queue>
#include <vector>

/// @brief slope trick
template <class T>
struct slope_trick {
    /// @brief 定数 $0$ の凸関数を構築する
    /// @complexity $O(1)$
    slope_trick() = default;

    /// @brief 最小値を取る $x$ の 1 つを返す
    /// @complexity $O(1)$
    [[nodiscard]] T min_x() const { return l.top(); }

    /// @brief 関数の最小値を返す
    /// @complexity $O(1)$
    [[nodiscard]] T min_value() const { return min_f; }

    /// @brief $f(x) \gets f(x) + a$
    /// @complexity $O(1)$
    void add_const(T a) { min_f += a; }

    /// @brief $f(x) \gets f(x) + \max(0, x - a)$
    /// @complexity $O(\log n)$
    void add_x_minus_a(T a) {
        if (!l.empty() && l.top() > a) { min_f += l.top() - a; }
        l.push(a);
        r.push(l.top());
        l.pop();
    }

    /// @brief $f(x) \gets f(x) + \max(0, a - x)$
    /// @complexity $O(\log n)$
    void add_a_minus_x(T a) {
        if (!r.empty() && a > r.top()) { min_f += a - r.top(); }
        r.push(a);
        l.push(r.top());
        r.pop();
    }

    /// @brief $f(x) \gets f(x) + |x - a| = f(x) + \max(0, x - a) + \max(0, a - x)$
    /// @complexity $O(\log n)$
    void add_abs(T a) {
        add_x_minus_a(a);
        add_a_minus_x(a);
    }

    /// @brief $f(x) \gets \min_{y \le x} f(y)$
    /// @complexity $O(1)$
    void clear_right() { r = decltype(r)(); }

    /// @brief $f(x) \gets \min_{y \ge x} f(y)$
    /// @complexity $O(1)$
    void clear_left() { l = decltype(l)(); }

  private:
    T min_f{};
    std::priority_queue<T> l;
    std::priority_queue<T, std::vector<T>, std::greater<T>> r;
};
