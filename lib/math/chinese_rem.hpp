#include <cstdint>
#include <utility>
#include <vector>

/**
 * @brief a * x + b * y = gcd(a, b) の答えを一つ求める
 *
 * @param a
 * @param b
 * @param x
 * @param y
 * @return std::int64_t gcd(a, b)
 */
std::int64_t extGCD(const std::int64_t a, const std::int64_t b, std::int64_t &x, std::int64_t &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }

    std::int64_t d = extGCD(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

/**
 * @brief 中国剰余定理
 * @details 任意の i において、$x % m_i = b_i$ となる x を求める
 *
 * @tparam T 配列bの型
 * @tparam U 配列mの型
 * @param b 余りの配列
 * @param m modの配列
 * @return std::pair<std::int64_t, std::int64_t> (r, M) ($x = r + M * k$ (kは整数))
 */
template <class T, class U>
std::pair<std::int64_t, std::int64_t> chinese_rem(const std::vector<T> &b,
                                                  const std::vector<U> &m) {
    std::int64_t r = 0, M = 1;
    int n = b.size();
    for (int i = 0; i < n; ++i) {
        std::int64_t p, q;
        std::int64_t d = extGCD(M, m[i], p, q);
        if ((b[i] - r) % d != 0) return {0, -1};
        std::int64_t tmp = (b[i] - r) / d * p % (m[i] / d);
        r += M * tmp;
        M *= m[i] / d;
    }
    return {r >= 0 ? r % M : M - 1 - (-r - 1) % M, M};
}
