#pragma once
#include "template/template.hpp"

namespace internal {

// @param m `1 <= m`
// @return x mod m
constexpr std::int64_t safe_mod(std::int64_t x, std::int64_t m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

// Fast modular multiplication by barrett reduction
// Reference: https://en.wikipedia.org/wiki/Barrett_reduction
// NOTE: reconsider after Ice Lake
struct barrett {
    unsigned int _m;
    std::uint64_t im;

    // @param m `1 <= m`
    explicit barrett(unsigned int m) : _m(m), im((std::uint64_t)(-1) / m + 1) {}

    // @return m
    unsigned int umod() const { return _m; }

    // @param a `0 <= a < m`
    // @param b `0 <= b < m`
    // @return `a * b % m`
    unsigned int mul(unsigned int a, unsigned int b) const {
        std::uint64_t z = a;
        z *= b;
        std::uint64_t x = (std::uint64_t)(((__uint128_t)(z)*im) >> 64);
        std::uint64_t y = x * _m;
        return (unsigned int)(z - y + (z < y ? _m : 0));
    }
};

struct montgomery {
    std::uint64_t _m;
    std::uint64_t im;
    std::uint64_t r2;

    // @param m `1 <= m`
    explicit constexpr montgomery(std::uint64_t m) : _m(m), im(m), r2(-__uint128_t(m) % m) {
        for (int i = 0; i < 5; ++i) im = im * (2 - _m * im);
        im = -im;
    }

    // @return m
    constexpr std::uint64_t umod() const { return _m; }

    // @param a `0 <= a < m`
    // @param b `0 <= b < m`
    // @return `a * b % m`
    constexpr std::uint64_t mul(std::uint64_t a, std::uint64_t b) const { return mr(mr(a, b), r2); }

    constexpr std::uint64_t exp(std::uint64_t a, std::uint64_t b) const {
        std::uint64_t res = 1, p = mr(a, r2);
        while (b) {
            if (b & 1) res = mr(res, p);
            p = mr(p, p);
            b >>= 1;
        }
        return res;
    }

    constexpr bool same_pow(std::uint64_t x, int s, std::uint64_t n) const {
        x = mr(x, r2), n = mr(n, r2);
        for (int r = 0; r < s; r++) {
            if (x == n) return true;
            x = mr(x, x);
        }
        return false;
    }

  private:
    constexpr std::uint64_t mr(std::uint64_t x) const {
        return ((__uint128_t)(x * im) * _m + x) >> 64;
    }
    constexpr std::uint64_t mr(std::uint64_t a, std::uint64_t b) const {
        __uint128_t t = (__uint128_t)a * b;
        std::uint64_t inc = std::uint64_t(t) != 0;
        std::uint64_t x = t >> 64, y = ((__uint128_t)(a * b * im) * _m) >> 64;
        unsigned long long z = 0;
        bool f = __builtin_uaddll_overflow(x, y, &z);
        z += inc;
        return f ? z - _m : z;
    }
};

constexpr bool is_SPRP32(std::uint32_t n, std::uint32_t a) {
    std::uint32_t d = n - 1, s = 0;
    while ((d & 1) == 0) ++s, d >>= 1;
    std::uint64_t cur = 1, pw = d;
    while (pw) {
        if (pw & 1) cur = (cur * a) % n;
        a = (std::uint64_t)a * a % n;
        pw >>= 1;
    }
    if (cur == 1) return true;
    for (std::uint32_t r = 0; r < s; r++) {
        if (cur == n - 1) return true;
        cur = cur * cur % n;
    }
    return false;
}

// given 2 <= n,a < 2^64, a prime, check whether n is a-SPRP
constexpr bool is_SPRP64(const montgomery &m, std::uint64_t a) {
    auto n = m.umod();
    if (n == a) return true;
    if (n % a == 0) return false;
    std::uint64_t d = n - 1;
    int s = 0;
    while ((d & 1) == 0) ++s, d >>= 1;
    std::uint64_t cur = m.exp(a, d);
    if (cur == 1) return true;
    return m.same_pow(cur, s, n - 1);
}

constexpr bool is_prime_constexpr(std::uint64_t x) {
    if (x == 2 || x == 3 || x == 5 || x == 7) return true;
    if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0) return false;
    if (x < 121) return (x > 1);
    montgomery m(x);
    constexpr std::uint64_t bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (auto a : bases) {
        if (!is_SPRP64(m, a)) return false;
    }
    return true;
}

constexpr bool is_prime_constexpr(std::int64_t x) {
    if (x < 0) return false;
    return is_prime_constexpr(std::uint64_t(x));
}

constexpr bool is_prime_constexpr(std::uint32_t x) {
    if (x == 2 || x == 3 || x == 5 || x == 7) return true;
    if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0) return false;
    if (x < 121) return (x > 1);
    std::uint64_t h = x;
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = ((h >> 16) ^ h) * 0x45d9f3b;
    h = ((h >> 16) ^ h) & 255;
    constexpr uint16_t bases[] = {
        15591, 2018,  166,   7429,  8064,  16045, 10503, 4399,  1949,  1295,  2776,  3620,  560,
        3128,  5212,  2657,  2300,  2021,  4652,  1471,  9336,  4018,  2398,  20462, 10277, 8028,
        2213,  6219,  620,   3763,  4852,  5012,  3185,  1333,  6227,  5298,  1074,  2391,  5113,
        7061,  803,   1269,  3875,  422,   751,   580,   4729,  10239, 746,   2951,  556,   2206,
        3778,  481,   1522,  3476,  481,   2487,  3266,  5633,  488,   3373,  6441,  3344,  17,
        15105, 1490,  4154,  2036,  1882,  1813,  467,   3307,  14042, 6371,  658,   1005,  903,
        737,   1887,  7447,  1888,  2848,  1784,  7559,  3400,  951,   13969, 4304,  177,   41,
        19875, 3110,  13221, 8726,  571,   7043,  6943,  1199,  352,   6435,  165,   1169,  3315,
        978,   233,   3003,  2562,  2994,  10587, 10030, 2377,  1902,  5354,  4447,  1555,  263,
        27027, 2283,  305,   669,   1912,  601,   6186,  429,   1930,  14873, 1784,  1661,  524,
        3577,  236,   2360,  6146,  2850,  55637, 1753,  4178,  8466,  222,   2579,  2743,  2031,
        2226,  2276,  374,   2132,  813,   23788, 1610,  4422,  5159,  1725,  3597,  3366,  14336,
        579,   165,   1375,  10018, 12616, 9816,  1371,  536,   1867,  10864, 857,   2206,  5788,
        434,   8085,  17618, 727,   3639,  1595,  4944,  2129,  2029,  8195,  8344,  6232,  9183,
        8126,  1870,  3296,  7455,  8947,  25017, 541,   19115, 368,   566,   5674,  411,   522,
        1027,  8215,  2050,  6544,  10049, 614,   774,   2333,  3007,  35201, 4706,  1152,  1785,
        1028,  1540,  3743,  493,   4474,  2521,  26845, 8354,  864,   18915, 5465,  2447,  42,
        4511,  1660,  166,   1249,  6259,  2553,  304,   272,   7286,  73,    6554,  899,   2816,
        5197,  13330, 7054,  2818,  3199,  811,   922,   350,   7514,  4452,  3449,  2663,  4708,
        418,   1621,  1171,  3471,  88,    11345, 412,   1559,  194};
    return is_SPRP32(x, bases[h]);
}

// @param n `0 <= n`
// @param m `1 <= m`
// @return `(x ** n) % m`
constexpr std::int64_t pow_mod_constexpr(std::int64_t x, std::int64_t n, int m) {
    if (m == 1) return 0;
    unsigned int _m = (unsigned int)(m);
    std::uint64_t r = 1;
    std::uint64_t y = safe_mod(x, m);
    while (n) {
        if (n & 1) r = (r * y) % _m;
        y = (y * y) % _m;
        n >>= 1;
    }
    return r;
}

// Reference:
// M. Forisek and J. Jancina,
// Fast Primality Testing for Integers That Fit into a Machine Word
// @param n `0 <= n`
constexpr bool is_prime_constexpr(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 7 || n == 61) return true;
    if (n % 2 == 0) return false;
    std::int64_t d = n - 1;
    while (d % 2 == 0) d /= 2;
    constexpr std::int64_t bases[3] = {2, 7, 61};
    for (std::int64_t a : bases) {
        std::int64_t t = d;
        std::int64_t y = pow_mod_constexpr(a, t, n);
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = y * y % n;
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) { return false; }
    }
    return true;
}
template <int n>
constexpr bool is_prime = is_prime_constexpr(n);

// @param b `1 <= b`
// @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
constexpr std::pair<std::int64_t, std::int64_t> inv_gcd(std::int64_t a, std::int64_t b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};
    std::int64_t s = b, t = a;
    std::int64_t m0 = 0, m1 = 1;
    while (t) {
        std::int64_t u = s / t;
        s -= t * u;
        m0 -= m1 * u;
        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}

// Compile time primitive root
// @param m must be prime
// @return primitive root (and minimum in now)
constexpr int primitive_root_constexpr(int m) {
    if (m == 2) return 1;
    if (m == 167772161) return 3;
    if (m == 469762049) return 3;
    if (m == 754974721) return 11;
    if (m == 998244353) return 3;
    int divs[20] = {};
    divs[0] = 2;
    int cnt = 1;
    int x = (m - 1) / 2;
    while (x % 2 == 0) x /= 2;
    for (int i = 3; (std::int64_t)(i)*i <= x; i += 2) {
        if (x % i == 0) {
            divs[cnt++] = i;
            while (x % i == 0) { x /= i; }
        }
    }
    if (x > 1) { divs[cnt++] = x; }
    for (int g = 2;; g++) {
        bool ok = true;
        for (int i = 0; i < cnt; i++) {
            if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}
template <int m>
constexpr int primitive_root = primitive_root_constexpr(m);

}  // namespace internal
