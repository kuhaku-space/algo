#pragma once
#include <bit>
#include <cstdint>
#include <vector>
#include "graph/matrix_graph.hpp"

/// @brief 彩色数
int chromatic_number(const matrix_graph<void> &g) {
    constexpr std::uint64_t _MOD = (1ull << 31) - 1;
    int n = g.size();
    std::vector<int> neighbor(n, 0);
    for (int i = 0; i < n; ++i) {
        int s = 1 << i;
        for (int j = 0; j < n; ++j) {
            if (g[i][j]) s |= 1 << j;
        }
        neighbor[i] = s;
    }

    std::vector<int> v(1 << n);
    v[0] = 1;
    for (int s = 1; s < 1 << n; ++s) {
        int c = std::countr_zero<unsigned>(s);
        v[s] = v[s & ~(1 << c)] + v[s & ~neighbor[c]];
    }

    auto _mod = [](std::uint64_t a) -> std::uint64_t {
        a = (a & _MOD) + (a >> 31);
        return a >= _MOD ? a - _MOD : a;
    };
    auto _pow = [](auto f, std::uint64_t a, int n) {
        std::uint64_t res = 1;
        for (; n > 0; n >>= 1) {
            if (n & 1) res = f(res * a);
            a = f(a * a);
        }
        return res;
    };

    int low = 0, high = n;
    while (high - low > 1) {
        int mid = (low + high) >> 1;
        std::uint64_t h = 0;
        for (int s = 0; s < 1 << n; ++s) {
            if ((n - std::popcount<unsigned>(s)) & 1) h = _mod(h + _MOD - _pow(_mod, v[s], mid));
            else h = _mod(h + _pow(_mod, v[s], mid));
        }
        if (h != 0) high = mid;
        else low = mid;
    }
    return high;
}
