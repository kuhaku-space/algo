#include "template/template.hpp"

/*
 * a * x + b * y = gcd(a, b) の答えを一つ求める
 * 戻り値は gcd(a, b)
 */
int64_t extGCD(const int64_t a, const int64_t b, int64_t &x, int64_t &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }

    int64_t d = extGCD(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

/*
 * 任意の i において、x % b_i = m_i となる x を求める
 * x = r + M * k (k in N) と表すことができる
 */
template <class T, class U>
pair<int64_t, int64_t> chinese_rem(const vector<T> &b, const vector<U> &m) {
    int64_t r = 0, M = 1;
    int64_t n = b.size();
    for (int64_t i = 0; i < n; ++i) {
        int64_t p, q;
        int64_t d = extGCD(M, m[i], p, q);
        if ((b[i] - r) % d != 0) return {0, -1};
        int64_t tmp = (b[i] - r) / d * p % (m[i] / d);
        r += M * tmp;
        M *= m[i] / d;
    }
    return {r >= 0 ? r % M : M - 1 - (-r - 1) % M, M};
}
