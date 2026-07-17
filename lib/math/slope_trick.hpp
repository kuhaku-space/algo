#pragma once

#include <algorithm>
#include <concepts>
#include <functional>
#include <queue>
#include <vector>

/// @brief slope trick
template <class T>
struct slope_trick {
    slope_trick() = default;

    [[nodiscard]] T min_x() const { return l.top(); }
    [[nodiscard]] T min_value() const { return min_f; }

    /// @brief Add f(x) = a
    void add_const(T a) { min_f += a; }

    /// @brief Add f(x) = max(0, x - a)
    void add_x_minus_a(T a) {
        if (!l.empty() && l.top() > a) {
            min_f += l.top() - a;
        }
        l.push(a);
        r.push(l.top());
        l.pop();
    }

    /// @brief Add f(x) = max(0, a - x)
    void add_a_minus_x(T a) {
        if (!r.empty() && a > r.top()) {
            min_f += a - r.top();
        }
        r.push(a);
        l.push(r.top());
        r.pop();
    }

    /// @brief Add f(x) = abs(x - a) = max(0, x - a) + max(0, a - x)
    void add_abs(T a) {
        add_x_minus_a(a);
        add_a_minus_x(a);
    }

    /// @brief f(x) <- min_{y <= x} f(y)
    void clear_right() { r = decltype(r)(); }

    /// @brief f(x) <- min_{y >= x} f(y)
    void clear_left() { l = decltype(l)(); }

  private:
    T min_f{};
    std::priority_queue<T> l;
    std::priority_queue<T, std::vector<T>, std::greater<T>> r;
};
