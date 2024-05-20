#include <cstdint>
#include <vector>
#include "graph/matrix_graph.hpp"

/**
 * @brief 彩色数を求める
 * @details $O(2^N)$
 *
 * @param G グラフ
 * @return int 彩色数
 */
int chromatic_number(const matrix_graph<void> &G) {
    constexpr std::int64_t _MOD = (1LL << 31) - 1;
    int n = G.size();
    std::vector<int> neighbor(n, 0);
    for (int i = 0; i < n; ++i) {
        int s = 1 << i;
        for (int j = 0; j < n; ++j) {
            if (G[i][j]) s |= 1 << j;
        }
        neighbor[i] = s;
    }

    std::vector<int> v(1 << n);
    v[0] = 1;
    for (int s = 1; s < 1 << n; ++s) {
        int c = __builtin_ctz(s);
        v[s] = v[s & ~(1 << c)] + v[s & ~neighbor[c]];
    }

    auto _mod = [](std::int64_t a) -> std::int64_t {
        a = (a & _MOD) + (a >> 31);
        return a >= _MOD ? a - _MOD : a;
    };
    auto _pow = [](auto f, std::int64_t a, int n) {
        std::int64_t res = 1;
        for (; n > 0; n >>= 1) {
            if (n & 1) res = f(res * a);
            a = f(a * a);
        }
        return res;
    };

    int low = 0, high = n;
    while (high - low > 1) {
        int mid = (low + high) >> 1;
        std::int64_t g = 0;
        for (int s = 0; s < 1 << n; ++s) {
            if ((n - __builtin_popcount(s)) & 1) g = _mod(g + _MOD - _pow(_mod, v[s], mid));
            else g = _mod(g + _pow(_mod, v[s], mid));
        }
        if (g != 0) high = mid;
        else low = mid;
    }
    return high;
}
