---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/atcoder/internal_math.hpp
    title: lib/atcoder/internal_math.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/atcoder/math.hpp\"\n\n\n\r\n#include <algorithm>\r\n\
    #include <cassert>\r\n#include <tuple>\r\n#include <vector>\r\n#include <atcoder/internal_math>\r\
    \n\r\nnamespace atcoder {\r\n\r\nlong long pow_mod(long long x, long long n, int\
    \ m) {\r\n    assert(0 <= n && 1 <= m);\r\n    if (m == 1) return 0;\r\n    internal::barrett\
    \ bt((unsigned int)(m));\r\n    unsigned int r = 1, y = (unsigned int)(internal::safe_mod(x,\
    \ m));\r\n    while (n) {\r\n        if (n & 1) r = bt.mul(r, y);\r\n        y\
    \ = bt.mul(y, y);\r\n        n >>= 1;\r\n    }\r\n    return r;\r\n}\r\n\r\nlong\
    \ long inv_mod(long long x, long long m) {\r\n    assert(1 <= m);\r\n    auto\
    \ z = internal::inv_gcd(x, m);\r\n    assert(z.first == 1);\r\n    return z.second;\r\
    \n}\r\n\r\n// (rem, mod)\r\nstd::pair<long long, long long> crt(const std::vector<long\
    \ long>& r,\r\n                                    const std::vector<long long>&\
    \ m) {\r\n    assert(r.size() == m.size());\r\n    int n = int(r.size());\r\n\
    \    // Contracts: 0 <= r0 < m0\r\n    long long r0 = 0, m0 = 1;\r\n    for (int\
    \ i = 0; i < n; i++) {\r\n        assert(1 <= m[i]);\r\n        long long r1 =\
    \ internal::safe_mod(r[i], m[i]), m1 = m[i];\r\n        if (m0 < m1) {\r\n   \
    \         std::swap(r0, r1);\r\n            std::swap(m0, m1);\r\n        }\r\n\
    \        if (m0 % m1 == 0) {\r\n            if (r0 % m1 != r1) return {0, 0};\r\
    \n            continue;\r\n        }\r\n        // assume: m0 > m1, lcm(m0, m1)\
    \ >= 2 * max(m0, m1)\r\n\r\n        // (r0, m0), (r1, m1) -> (r2, m2 = lcm(m0,\
    \ m1));\r\n        // r2 % m0 = r0\r\n        // r2 % m1 = r1\r\n        // ->\
    \ (r0 + x*m0) % m1 = r1\r\n        // -> x*u0*g % (u1*g) = (r1 - r0) (u0*g = m0,\
    \ u1*g = m1)\r\n        // -> x = (r1 - r0) / g * inv(u0) (mod u1)\r\n\r\n   \
    \     // im = inv(u0) (mod u1) (0 <= im < u1)\r\n        long long g, im;\r\n\
    \        std::tie(g, im) = internal::inv_gcd(m0, m1);\r\n\r\n        long long\
    \ u1 = (m1 / g);\r\n        // |r1 - r0| < (m0 + m1) <= lcm(m0, m1)\r\n      \
    \  if ((r1 - r0) % g) return {0, 0};\r\n\r\n        // u1 * u1 <= m1 * m1 / g\
    \ / g <= m0 * m1 / g = lcm(m0, m1)\r\n        long long x = (r1 - r0) / g % u1\
    \ * im % u1;\r\n\r\n        // |r0| + |m0 * x|\r\n        // < m0 + m0 * (u1 -\
    \ 1)\r\n        // = m0 + m0 * m1 / g - m0\r\n        // = lcm(m0, m1)\r\n   \
    \     r0 += x * m0;\r\n        m0 *= u1;  // -> lcm(m0, m1)\r\n        if (r0\
    \ < 0) r0 += m0;\r\n    }\r\n    return {r0, m0};\r\n}\r\n\r\nlong long floor_sum(long\
    \ long n, long long m, long long a, long long b) {\r\n    long long ans = 0;\r\
    \n    if (a >= m) {\r\n        ans += (n - 1) * n * (a / m) / 2;\r\n        a\
    \ %= m;\r\n    }\r\n    if (b >= m) {\r\n        ans += n * (b / m);\r\n     \
    \   b %= m;\r\n    }\r\n\r\n    long long y_max = (a * n + b) / m, x_max = (y_max\
    \ * m - b);\r\n    if (y_max == 0) return ans;\r\n    ans += (n - (x_max + a -\
    \ 1) / a) * y_max;\r\n    ans += floor_sum(y_max, a, m, (a - x_max % a) % a);\r\
    \n    return ans;\r\n}\r\n\r\n}  // namespace atcoder\r\n\r\n\n"
  code: "#ifndef ATCODER_MATH_HPP\r\n#define ATCODER_MATH_HPP 1\r\n\r\n#include <algorithm>\r\
    \n#include <cassert>\r\n#include <tuple>\r\n#include <vector>\r\n#include <atcoder/internal_math>\r\
    \n\r\nnamespace atcoder {\r\n\r\nlong long pow_mod(long long x, long long n, int\
    \ m) {\r\n    assert(0 <= n && 1 <= m);\r\n    if (m == 1) return 0;\r\n    internal::barrett\
    \ bt((unsigned int)(m));\r\n    unsigned int r = 1, y = (unsigned int)(internal::safe_mod(x,\
    \ m));\r\n    while (n) {\r\n        if (n & 1) r = bt.mul(r, y);\r\n        y\
    \ = bt.mul(y, y);\r\n        n >>= 1;\r\n    }\r\n    return r;\r\n}\r\n\r\nlong\
    \ long inv_mod(long long x, long long m) {\r\n    assert(1 <= m);\r\n    auto\
    \ z = internal::inv_gcd(x, m);\r\n    assert(z.first == 1);\r\n    return z.second;\r\
    \n}\r\n\r\n// (rem, mod)\r\nstd::pair<long long, long long> crt(const std::vector<long\
    \ long>& r,\r\n                                    const std::vector<long long>&\
    \ m) {\r\n    assert(r.size() == m.size());\r\n    int n = int(r.size());\r\n\
    \    // Contracts: 0 <= r0 < m0\r\n    long long r0 = 0, m0 = 1;\r\n    for (int\
    \ i = 0; i < n; i++) {\r\n        assert(1 <= m[i]);\r\n        long long r1 =\
    \ internal::safe_mod(r[i], m[i]), m1 = m[i];\r\n        if (m0 < m1) {\r\n   \
    \         std::swap(r0, r1);\r\n            std::swap(m0, m1);\r\n        }\r\n\
    \        if (m0 % m1 == 0) {\r\n            if (r0 % m1 != r1) return {0, 0};\r\
    \n            continue;\r\n        }\r\n        // assume: m0 > m1, lcm(m0, m1)\
    \ >= 2 * max(m0, m1)\r\n\r\n        // (r0, m0), (r1, m1) -> (r2, m2 = lcm(m0,\
    \ m1));\r\n        // r2 % m0 = r0\r\n        // r2 % m1 = r1\r\n        // ->\
    \ (r0 + x*m0) % m1 = r1\r\n        // -> x*u0*g % (u1*g) = (r1 - r0) (u0*g = m0,\
    \ u1*g = m1)\r\n        // -> x = (r1 - r0) / g * inv(u0) (mod u1)\r\n\r\n   \
    \     // im = inv(u0) (mod u1) (0 <= im < u1)\r\n        long long g, im;\r\n\
    \        std::tie(g, im) = internal::inv_gcd(m0, m1);\r\n\r\n        long long\
    \ u1 = (m1 / g);\r\n        // |r1 - r0| < (m0 + m1) <= lcm(m0, m1)\r\n      \
    \  if ((r1 - r0) % g) return {0, 0};\r\n\r\n        // u1 * u1 <= m1 * m1 / g\
    \ / g <= m0 * m1 / g = lcm(m0, m1)\r\n        long long x = (r1 - r0) / g % u1\
    \ * im % u1;\r\n\r\n        // |r0| + |m0 * x|\r\n        // < m0 + m0 * (u1 -\
    \ 1)\r\n        // = m0 + m0 * m1 / g - m0\r\n        // = lcm(m0, m1)\r\n   \
    \     r0 += x * m0;\r\n        m0 *= u1;  // -> lcm(m0, m1)\r\n        if (r0\
    \ < 0) r0 += m0;\r\n    }\r\n    return {r0, m0};\r\n}\r\n\r\nlong long floor_sum(long\
    \ long n, long long m, long long a, long long b) {\r\n    long long ans = 0;\r\
    \n    if (a >= m) {\r\n        ans += (n - 1) * n * (a / m) / 2;\r\n        a\
    \ %= m;\r\n    }\r\n    if (b >= m) {\r\n        ans += n * (b / m);\r\n     \
    \   b %= m;\r\n    }\r\n\r\n    long long y_max = (a * n + b) / m, x_max = (y_max\
    \ * m - b);\r\n    if (y_max == 0) return ans;\r\n    ans += (n - (x_max + a -\
    \ 1) / a) * y_max;\r\n    ans += floor_sum(y_max, a, m, (a - x_max % a) % a);\r\
    \n    return ans;\r\n}\r\n\r\n}  // namespace atcoder\r\n\r\n#endif  // ATCODER_MATH_HPP\r\
    \n"
  dependsOn:
  - lib/atcoder/internal_math.hpp
  isVerificationFile: false
  path: lib/atcoder/math.hpp
  requiredBy: []
  timestamp: '2021-09-18 16:27:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/atcoder/math.hpp
layout: document
redirect_from:
- /library/lib/atcoder/math.hpp
- /library/lib/atcoder/math.hpp.html
title: lib/atcoder/math.hpp
---
