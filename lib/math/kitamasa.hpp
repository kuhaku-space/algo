#pragma once
#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>
#include <vector>

/// @brief きたまさ法
template <class T>
T kitamasa(const std::vector<T> &a, const std::vector<T> &d, std::int64_t n) {
    assert(a.size() == d.size());
    const int k = d.size();
    if (n < k) return a[n];
    std::vector<int> bits;
    while (n > k * 2) {
        bits.emplace_back(n & 1);
        n >>= 1;
    }
    std::vector<T> x = d, y(k);
    for (int i = k; i < n; ++i) {
        std::swap(x, y);
        for (int i = 0; i < k; ++i) x[i] = d[i] * y[k - 1];
        for (int i = 0; i + 1 < k; ++i) x[i + 1] += y[i];
    }
    std::reverse(std::begin(bits), std::end(bits));
    std::vector<std::vector<T>> v(k, std::vector<T>(k));
    for (auto &&bit : bits) {
        v[0] = x;
        for (int i = 0; i + 1 < k; ++i) {
            for (int j = 0; j < k; ++j) v[i + 1][j] = d[j] * v[i][k - 1];
            for (int j = 0; j + 1 < k; ++j) v[i + 1][j + 1] += v[i][j];
        }
        std::fill(std::begin(x), std::end(x), T());
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) x[j] += v[0][i] * v[i][j];
        }
        if (bit) {
            std::swap(x, y);
            for (int i = 0; i < k; ++i) x[i] = d[i] * y[k - 1];
            for (int i = 0; i + 1 < k; ++i) x[i + 1] += y[i];
        }
    }
    T res{};
    for (int i = 0; i < k; ++i) res += x[i] * a[i];
    return res;
}
