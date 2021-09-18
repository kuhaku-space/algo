#include "lib/template/template.hpp"
#include "graph/graph_matrix.hpp"

// 彩色数を求める
// O(2^N)
int chromatic_number(const Graph<bool> &G) {
    constexpr int64_t _MOD = (1LL << 31) - 1;
    int n = G.size();
    vector<int> neighbor(n, 0);
    for (int i = 0; i < n; ++i) {
        int s = 1 << i;
        for (int j = 0; j < n; ++j) {
            if (G[i][j]) s |= 1 << j;
        }
        neighbor[i] = s;
    }

    vector<int> v(1 << n);
    v[0] = 1;
    for (int s = 1; s < 1 << n; ++s) {
        int c = __builtin_ctz(s);
        v[s] = v[s & ~(1 << c)] + v[s & ~neighbor[c]];
    }

    auto _mod = [](int64_t a) -> int64_t {
        a = (a & _MOD) + (a >> 31);
        return a >= _MOD ? a - _MOD : a;
    };
    auto _pow = [](auto f, int64_t a, int n) {
        int64_t res = 1;
        for (; n > 0; n >>= 1) {
            if (n & 1) res = f(res * a);
            a = f(a * a);
        }
        return res;
    };

    int low = 0, high = n;
    while (high - low > 1) {
        int mid = (low + high) >> 1;
        int64_t g = 0;
        for (int s = 0; s < 1 << n; ++s) {
            if ((n - __builtin_popcount(s)) & 1)
                g = _mod(g + _MOD - _pow(_mod, v[s], mid));
            else
                g = _mod(g + _pow(_mod, v[s], mid));
        }
        if (g != 0)
            high = mid;
        else
            low = mid;
    }
    return high;
}
