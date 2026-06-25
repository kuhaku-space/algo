#include <cmath>
#include <cstdint>
#include <vector>

/// @brief n以下の素数を数える
/// @details O(n^(3/4)/log(n))
std::int64_t prime_counting(std::int64_t n) {
    std::int64_t sq = std::sqrt((long double)n);
    std::int64_t qs = n / sq;
    std::vector<std::int64_t> l(qs), r(sq);
    for (int i = 0; i < sq; ++i) r[i] = n / (i + 1) - 1;
    for (int i = 0; i < qs; ++i) l[i] = i;
    for (int i = 2; i <= sq; ++i) {
        if (l[i - 1] <= l[i - 2]) continue;
        std::int64_t pi = l[i - 2];
        for (int j = 1; j <= sq; ++j) {
            if (n / j < (std::int64_t)i * i) break;
            std::int64_t x = (n / i / j <= qs ? l[n / i / j - 1] : r[i * j - 1]) - pi;
            if (n / j <= qs) l[n / j - 1] -= x;
            else r[j - 1] -= x;
        }
        for (int j = qs - 1; j >= 1; --j) {
            if (j < (std::int64_t)i * i) break;
            l[j - 1] -= l[j / i - 1] - pi;
        }
    }
    return r[0];
}
