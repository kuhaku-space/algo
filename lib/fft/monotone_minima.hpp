#pragma once
#include <functional>
#include <limits>
#include <vector>

template <class T, class Comp = std::less<>, class F>
std::vector<int> monotone_minima(int h, int w, F f) {
    Comp comp;
    std::vector<int> dp(h);
    auto dfs = [&](auto self, int top, int bottom, int left, int right) -> void {
        if (top > bottom) return;
        if (left == right) {
            for (int i = top; i <= bottom; ++i) dp[i] = left;
            return;
        }
        int line = (top + bottom) / 2;
        T min_val = f(line, left);
        int idx = left;
        for (int i = left + 1; i <= right; i++) {
            T val = f(line, i);
            if (comp(val, min_val)) min_val = val, idx = i;
        }
        dp[line] = idx;
        self(self, top, line - 1, left, idx);
        self(self, line + 1, bottom, idx, right);
    };
    dfs(dfs, 0, h - 1, 0, w - 1);
    return dp;
}

template <class T, class Comp = std::less<>, class F>
std::vector<T> monotone_minima_value(int h, int w, F f) {
    Comp comp;
    std::vector<T> dp(h);
    auto dfs = [&](auto self, int top, int bottom, int left, int right) -> void {
        if (top > bottom) return;
        if (left == right) {
            for (int i = top; i <= bottom; ++i) dp[i] = f(i, left);
            return;
        }
        int line = (top + bottom) / 2;
        T min_val = f(line, left);
        int idx = left;
        for (int i = left + 1; i <= right; i++) {
            T val = f(line, i);
            if (comp(val, min_val)) min_val = val, idx = i;
        }
        dp[line] = min_val;
        self(self, top, line - 1, left, idx);
        self(self, line + 1, bottom, idx, right);
    };
    dfs(dfs, 0, h - 1, 0, w - 1);
    return dp;
}

/// @brief min-plus convolution
/// @param b 下に凸
template <class T>
std::vector<T> min_plus_convolution(const std::vector<T> &a, const std::vector<T> &b) {
    int n = a.size(), m = b.size();
    auto f = [&](int i, int j) {
        if (i < j or i - j >= m) return std::numeric_limits<T>::max();
        return a[j] + b[i - j];
    };
    return monotone_minima_value<T>(n + m - 1, n, f);
}

template <class T>
std::vector<T> max_plus_convolution(const std::vector<T> &a, const std::vector<T> &b) {
    int n = a.size(), m = b.size();
    auto f = [&](int i, int j) {
        if (i < j or i - j >= m) return std::numeric_limits<T>::lowest();
        return a[j] + b[i - j];
    };
    return monotone_minima_value<T, std::greater<>>(n + m - 1, n, f);
}
