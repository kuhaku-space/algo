---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/atcoder/convolution.hpp
    title: lib/atcoder/convolution.hpp
  - icon: ':warning:'
    path: lib/atcoder/math.hpp
    title: lib/atcoder/math.hpp
  - icon: ':warning:'
    path: lib/atcoder/modint.hpp
    title: lib/atcoder/modint.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://en.wikipedia.org/wiki/Barrett_reduction
  bundledCode: "#line 1 \"lib/atcoder/internal_math.hpp\"\n\n\n\r\n#include <utility>\r\
    \n\r\nnamespace atcoder {\r\n\r\nnamespace internal {\r\n\r\n// @param m `1 <=\
    \ m`\r\n// @return x mod m\r\nconstexpr long long safe_mod(long long x, long long\
    \ m) {\r\n    x %= m;\r\n    if (x < 0) x += m;\r\n    return x;\r\n}\r\n\r\n\
    // Fast moduler by barrett reduction\r\n// Reference: https://en.wikipedia.org/wiki/Barrett_reduction\r\
    \n// NOTE: reconsider after Ice Lake\r\nstruct barrett {\r\n    unsigned int _m;\r\
    \n    unsigned long long im;\r\n\r\n    // @param m `1 <= m`\r\n    barrett(unsigned\
    \ int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}\r\n\r\n    // @return\
    \ m\r\n    unsigned int umod() const { return _m; }\r\n\r\n    // @param a `0\
    \ <= a < m`\r\n    // @param b `0 <= b < m`\r\n    // @return `a * b % m`\r\n\
    \    unsigned int mul(unsigned int a, unsigned int b) const {\r\n        // [1]\
    \ m = 1\r\n        // a = b = im = 0, so okay\r\n\r\n        // [2] m >= 2\r\n\
    \        // im = ceil(2^64 / m)\r\n        // -> im * m = 2^64 + r (0 <= r < m)\r\
    \n        // let z = a*b = c*m + d (0 <= c, d < m)\r\n        // a*b * im = (c*m\
    \ + d) * im = c*(im*m) + d*im = c*2^64 + c*r + d*im\r\n        // c*r + d*im <\
    \ m * m + m * im < m * m + 2^64 + m <= 2^64 + m * (m + 1) < 2^64 * 2\r\n     \
    \   // ((ab * im) >> 64) == c or c + 1\r\n        unsigned long long z = a;\r\n\
    \        z *= b;\r\n#ifdef _MSC_VER\r\n        unsigned long long x;\r\n     \
    \   _umul128(z, im, &x);\r\n#else\r\n        unsigned long long x =\r\n      \
    \      (unsigned long long)(((unsigned __int128)(z)*im) >> 64);\r\n#endif\r\n\
    \        unsigned int v = (unsigned int)(z - x * _m);\r\n        if (_m <= v)\
    \ v += _m;\r\n        return v;\r\n    }\r\n};\r\n\r\n// @param n `0 <= n`\r\n\
    // @param m `1 <= m`\r\n// @return `(x ** n) % m`\r\nconstexpr long long pow_mod_constexpr(long\
    \ long x, long long n, int m) {\r\n    if (m == 1) return 0;\r\n    unsigned int\
    \ _m = (unsigned int)(m);\r\n    unsigned long long r = 1;\r\n    unsigned long\
    \ long y = safe_mod(x, m);\r\n    while (n) {\r\n        if (n & 1) r = (r * y)\
    \ % _m;\r\n        y = (y * y) % _m;\r\n        n >>= 1;\r\n    }\r\n    return\
    \ r;\r\n}\r\n\r\n// Reference:\r\n// M. Forisek and J. Jancina,\r\n// Fast Primality\
    \ Testing for Integers That Fit into a Machine Word\r\n// @param n `0 <= n`\r\n\
    constexpr bool is_prime_constexpr(int n) {\r\n    if (n <= 1) return false;\r\n\
    \    if (n == 2 || n == 7 || n == 61) return true;\r\n    if (n % 2 == 0) return\
    \ false;\r\n    long long d = n - 1;\r\n    while (d % 2 == 0) d /= 2;\r\n   \
    \ for (long long a : {2, 7, 61}) {\r\n        long long t = d;\r\n        long\
    \ long y = pow_mod_constexpr(a, t, n);\r\n        while (t != n - 1 && y != 1\
    \ && y != n - 1) {\r\n            y = y * y % n;\r\n            t <<= 1;\r\n \
    \       }\r\n        if (y != n - 1 && t % 2 == 0) {\r\n            return false;\r\
    \n        }\r\n    }\r\n    return true;\r\n}\r\ntemplate <int n> constexpr bool\
    \ is_prime = is_prime_constexpr(n);\r\n\r\n// @param b `1 <= b`\r\n// @return\
    \ pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g\r\nconstexpr std::pair<long\
    \ long, long long> inv_gcd(long long a, long long b) {\r\n    a = safe_mod(a,\
    \ b);\r\n    if (a == 0) return {b, 0};\r\n\r\n    // Contracts:\r\n    // [1]\
    \ s - m0 * a = 0 (mod b)\r\n    // [2] t - m1 * a = 0 (mod b)\r\n    // [3] s\
    \ * |m1| + t * |m0| <= b\r\n    long long s = b, t = a;\r\n    long long m0 =\
    \ 0, m1 = 1;\r\n\r\n    while (t) {\r\n        long long u = s / t;\r\n      \
    \  s -= t * u;\r\n        m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b\r\n\r\n\
    \        // [3]:\r\n        // (s - t * u) * |m1| + t * |m0 - m1 * u|\r\n    \
    \    // <= s * |m1| - t * u * |m1| + t * (|m0| + |m1| * u)\r\n        // = s *\
    \ |m1| + t * |m0| <= b\r\n\r\n        auto tmp = s;\r\n        s = t;\r\n    \
    \    t = tmp;\r\n        tmp = m0;\r\n        m0 = m1;\r\n        m1 = tmp;\r\n\
    \    }\r\n    // by [3]: |m0| <= b/g\r\n    // by g != b: |m0| < b/g\r\n    if\
    \ (m0 < 0) m0 += b / s;\r\n    return {s, m0};\r\n}\r\n\r\n// Compile time primitive\
    \ root\r\n// @param m must be prime\r\n// @return primitive root (and minimum\
    \ in now)\r\nconstexpr int primitive_root_constexpr(int m) {\r\n    if (m == 2)\
    \ return 1;\r\n    if (m == 167772161) return 3;\r\n    if (m == 469762049) return\
    \ 3;\r\n    if (m == 754974721) return 11;\r\n    if (m == 998244353) return 3;\r\
    \n    int divs[20] = {};\r\n    divs[0] = 2;\r\n    int cnt = 1;\r\n    int x\
    \ = (m - 1) / 2;\r\n    while (x % 2 == 0) x /= 2;\r\n    for (int i = 3; (long\
    \ long)(i)*i <= x; i += 2) {\r\n        if (x % i == 0) {\r\n            divs[cnt++]\
    \ = i;\r\n            while (x % i == 0) {\r\n                x /= i;\r\n    \
    \        }\r\n        }\r\n    }\r\n    if (x > 1) {\r\n        divs[cnt++] =\
    \ x;\r\n    }\r\n    for (int g = 2;; g++) {\r\n        bool ok = true;\r\n  \
    \      for (int i = 0; i < cnt; i++) {\r\n            if (pow_mod_constexpr(g,\
    \ (m - 1) / divs[i], m) == 1) {\r\n                ok = false;\r\n           \
    \     break;\r\n            }\r\n        }\r\n        if (ok) return g;\r\n  \
    \  }\r\n}\r\ntemplate <int m> constexpr int primitive_root = primitive_root_constexpr(m);\r\
    \n\r\n}  // namespace internal\r\n\r\n}  // namespace atcoder\r\n\r\n\n"
  code: "#ifndef ATCODER_INTERNAL_MATH_HPP\r\n#define ATCODER_INTERNAL_MATH_HPP 1\r\
    \n\r\n#include <utility>\r\n\r\nnamespace atcoder {\r\n\r\nnamespace internal\
    \ {\r\n\r\n// @param m `1 <= m`\r\n// @return x mod m\r\nconstexpr long long safe_mod(long\
    \ long x, long long m) {\r\n    x %= m;\r\n    if (x < 0) x += m;\r\n    return\
    \ x;\r\n}\r\n\r\n// Fast moduler by barrett reduction\r\n// Reference: https://en.wikipedia.org/wiki/Barrett_reduction\r\
    \n// NOTE: reconsider after Ice Lake\r\nstruct barrett {\r\n    unsigned int _m;\r\
    \n    unsigned long long im;\r\n\r\n    // @param m `1 <= m`\r\n    barrett(unsigned\
    \ int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}\r\n\r\n    // @return\
    \ m\r\n    unsigned int umod() const { return _m; }\r\n\r\n    // @param a `0\
    \ <= a < m`\r\n    // @param b `0 <= b < m`\r\n    // @return `a * b % m`\r\n\
    \    unsigned int mul(unsigned int a, unsigned int b) const {\r\n        // [1]\
    \ m = 1\r\n        // a = b = im = 0, so okay\r\n\r\n        // [2] m >= 2\r\n\
    \        // im = ceil(2^64 / m)\r\n        // -> im * m = 2^64 + r (0 <= r < m)\r\
    \n        // let z = a*b = c*m + d (0 <= c, d < m)\r\n        // a*b * im = (c*m\
    \ + d) * im = c*(im*m) + d*im = c*2^64 + c*r + d*im\r\n        // c*r + d*im <\
    \ m * m + m * im < m * m + 2^64 + m <= 2^64 + m * (m + 1) < 2^64 * 2\r\n     \
    \   // ((ab * im) >> 64) == c or c + 1\r\n        unsigned long long z = a;\r\n\
    \        z *= b;\r\n#ifdef _MSC_VER\r\n        unsigned long long x;\r\n     \
    \   _umul128(z, im, &x);\r\n#else\r\n        unsigned long long x =\r\n      \
    \      (unsigned long long)(((unsigned __int128)(z)*im) >> 64);\r\n#endif\r\n\
    \        unsigned int v = (unsigned int)(z - x * _m);\r\n        if (_m <= v)\
    \ v += _m;\r\n        return v;\r\n    }\r\n};\r\n\r\n// @param n `0 <= n`\r\n\
    // @param m `1 <= m`\r\n// @return `(x ** n) % m`\r\nconstexpr long long pow_mod_constexpr(long\
    \ long x, long long n, int m) {\r\n    if (m == 1) return 0;\r\n    unsigned int\
    \ _m = (unsigned int)(m);\r\n    unsigned long long r = 1;\r\n    unsigned long\
    \ long y = safe_mod(x, m);\r\n    while (n) {\r\n        if (n & 1) r = (r * y)\
    \ % _m;\r\n        y = (y * y) % _m;\r\n        n >>= 1;\r\n    }\r\n    return\
    \ r;\r\n}\r\n\r\n// Reference:\r\n// M. Forisek and J. Jancina,\r\n// Fast Primality\
    \ Testing for Integers That Fit into a Machine Word\r\n// @param n `0 <= n`\r\n\
    constexpr bool is_prime_constexpr(int n) {\r\n    if (n <= 1) return false;\r\n\
    \    if (n == 2 || n == 7 || n == 61) return true;\r\n    if (n % 2 == 0) return\
    \ false;\r\n    long long d = n - 1;\r\n    while (d % 2 == 0) d /= 2;\r\n   \
    \ for (long long a : {2, 7, 61}) {\r\n        long long t = d;\r\n        long\
    \ long y = pow_mod_constexpr(a, t, n);\r\n        while (t != n - 1 && y != 1\
    \ && y != n - 1) {\r\n            y = y * y % n;\r\n            t <<= 1;\r\n \
    \       }\r\n        if (y != n - 1 && t % 2 == 0) {\r\n            return false;\r\
    \n        }\r\n    }\r\n    return true;\r\n}\r\ntemplate <int n> constexpr bool\
    \ is_prime = is_prime_constexpr(n);\r\n\r\n// @param b `1 <= b`\r\n// @return\
    \ pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g\r\nconstexpr std::pair<long\
    \ long, long long> inv_gcd(long long a, long long b) {\r\n    a = safe_mod(a,\
    \ b);\r\n    if (a == 0) return {b, 0};\r\n\r\n    // Contracts:\r\n    // [1]\
    \ s - m0 * a = 0 (mod b)\r\n    // [2] t - m1 * a = 0 (mod b)\r\n    // [3] s\
    \ * |m1| + t * |m0| <= b\r\n    long long s = b, t = a;\r\n    long long m0 =\
    \ 0, m1 = 1;\r\n\r\n    while (t) {\r\n        long long u = s / t;\r\n      \
    \  s -= t * u;\r\n        m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b\r\n\r\n\
    \        // [3]:\r\n        // (s - t * u) * |m1| + t * |m0 - m1 * u|\r\n    \
    \    // <= s * |m1| - t * u * |m1| + t * (|m0| + |m1| * u)\r\n        // = s *\
    \ |m1| + t * |m0| <= b\r\n\r\n        auto tmp = s;\r\n        s = t;\r\n    \
    \    t = tmp;\r\n        tmp = m0;\r\n        m0 = m1;\r\n        m1 = tmp;\r\n\
    \    }\r\n    // by [3]: |m0| <= b/g\r\n    // by g != b: |m0| < b/g\r\n    if\
    \ (m0 < 0) m0 += b / s;\r\n    return {s, m0};\r\n}\r\n\r\n// Compile time primitive\
    \ root\r\n// @param m must be prime\r\n// @return primitive root (and minimum\
    \ in now)\r\nconstexpr int primitive_root_constexpr(int m) {\r\n    if (m == 2)\
    \ return 1;\r\n    if (m == 167772161) return 3;\r\n    if (m == 469762049) return\
    \ 3;\r\n    if (m == 754974721) return 11;\r\n    if (m == 998244353) return 3;\r\
    \n    int divs[20] = {};\r\n    divs[0] = 2;\r\n    int cnt = 1;\r\n    int x\
    \ = (m - 1) / 2;\r\n    while (x % 2 == 0) x /= 2;\r\n    for (int i = 3; (long\
    \ long)(i)*i <= x; i += 2) {\r\n        if (x % i == 0) {\r\n            divs[cnt++]\
    \ = i;\r\n            while (x % i == 0) {\r\n                x /= i;\r\n    \
    \        }\r\n        }\r\n    }\r\n    if (x > 1) {\r\n        divs[cnt++] =\
    \ x;\r\n    }\r\n    for (int g = 2;; g++) {\r\n        bool ok = true;\r\n  \
    \      for (int i = 0; i < cnt; i++) {\r\n            if (pow_mod_constexpr(g,\
    \ (m - 1) / divs[i], m) == 1) {\r\n                ok = false;\r\n           \
    \     break;\r\n            }\r\n        }\r\n        if (ok) return g;\r\n  \
    \  }\r\n}\r\ntemplate <int m> constexpr int primitive_root = primitive_root_constexpr(m);\r\
    \n\r\n}  // namespace internal\r\n\r\n}  // namespace atcoder\r\n\r\n#endif  //\
    \ ATCODER_INTERNAL_MATH_HPP\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/atcoder/internal_math.hpp
  requiredBy:
  - lib/atcoder/modint.hpp
  - lib/atcoder/math.hpp
  - lib/atcoder/convolution.hpp
  timestamp: '2021-09-18 16:27:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/atcoder/internal_math.hpp
layout: document
redirect_from:
- /library/lib/atcoder/internal_math.hpp
- /library/lib/atcoder/internal_math.hpp.html
title: lib/atcoder/internal_math.hpp
---
