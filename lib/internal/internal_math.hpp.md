---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/bigint.hpp
    title: "\u591A\u500D\u9577\u6574\u6570"
  - icon: ':warning:'
    path: lib/fft/formal_power_series.hpp
    title: lib/fft/formal_power_series.hpp
  - icon: ':warning:'
    path: lib/fft/garner.hpp
    title: lib/fft/garner.hpp
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt.hpp
    title: "\u7573\u307F\u8FBC\u307F"
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt_mod.hpp
    title: "\u4EFB\u610Fmod\u7573\u307F\u8FBC\u307F"
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_fft.hpp
    title: lib/internal/internal_fft.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/combination.hpp
    title: lib/math/combination.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/enumeration.hpp
    title: lib/math/enumeration.hpp
  - icon: ':warning:'
    path: lib/math/floor_sum.hpp
    title: floor sum
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: lib/math/modint.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/sqrt.hpp
    title: lib/math/sqrt.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dpl/bell.test.cpp
    title: test/aoj/dpl/bell.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dpl/stirling.test.cpp
    title: test/aoj/dpl/stirling.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/jag/aho_corasick.test.cpp
    title: test/aoj/jag/aho_corasick.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/addition.test.cpp
    title: test/aoj/ntl/addition.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/difference.test.cpp
    title: test/aoj/ntl/difference.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/division.test.cpp
    title: test/aoj/ntl/division.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/multiplication.test.cpp
    title: test/aoj/ntl/multiplication.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/multiplication2.test.cpp
    title: test/aoj/ntl/multiplication2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/power.test.cpp
    title: test/aoj/ntl/power.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/remainder.test.cpp
    title: test/aoj/ntl/remainder.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution/bitwise_and_convolution.test.cpp
    title: test/yosupo/convolution/bitwise_and_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution/bitwise_xor_convolution.test.cpp
    title: test/yosupo/convolution/bitwise_xor_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution/convolution.test.cpp
    title: test/yosupo/convolution/convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution/convolution_mod.test.cpp
    title: test/yosupo/convolution/convolution_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/addition_of_big_integers.test.cpp
    title: test/yosupo/data_structure/addition_of_big_integers.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/point_set_range_composite.test.cpp
    title: test/yosupo/data_structure/point_set_range_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/queue_operate_all_composite.test.cpp
    title: test/yosupo/data_structure/queue_operate_all_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/range_affine_range_sum.test.cpp
    title: test/yosupo/data_structure/range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
    title: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/math/number_of_subsequences.test.cpp
    title: test/yosupo/math/number_of_subsequences.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/math/sqrt_mod.test.cpp
    title: test/yosupo/math/sqrt_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/matrix/determinant_of_matrix.test.cpp
    title: test/yosupo/matrix/determinant_of_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/matrix/matrix_product.test.cpp
    title: test/yosupo/matrix/matrix_product.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/tree/tree_path_composite_sum.test.cpp
    title: test/yosupo/tree/tree_path_composite_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://en.wikipedia.org/wiki/Barrett_reduction
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"template/template.hpp\"\n\nnamespace internal {\n\
    \n// @param m `1 <= m`\n// @return x mod m\nconstexpr std::int64_t safe_mod(std::int64_t\
    \ x, std::int64_t m) {\n    x %= m;\n    if (x < 0) x += m;\n    return x;\n}\n\
    \n// Fast modular multiplication by barrett reduction\n// Reference: https://en.wikipedia.org/wiki/Barrett_reduction\n\
    // NOTE: reconsider after Ice Lake\nstruct barrett {\n    unsigned int _m;\n \
    \   std::uint64_t im;\n\n    // @param m `1 <= m`\n    explicit barrett(unsigned\
    \ int m) : _m(m), im((std::uint64_t)(-1) / m + 1) {}\n\n    // @return m\n   \
    \ unsigned int umod() const { return _m; }\n\n    // @param a `0 <= a < m`\n \
    \   // @param b `0 <= b < m`\n    // @return `a * b % m`\n    unsigned int mul(unsigned\
    \ int a, unsigned int b) const {\n        std::uint64_t z = a;\n        z *= b;\n\
    \        std::uint64_t x = (std::uint64_t)(((__uint128_t)(z)*im) >> 64);\n   \
    \     std::uint64_t y = x * _m;\n        return (unsigned int)(z - y + (z < y\
    \ ? _m : 0));\n    }\n};\n\nstruct montgomery {\n    std::uint64_t _m;\n    std::uint64_t\
    \ im;\n    std::uint64_t r2;\n\n    // @param m `1 <= m`\n    explicit constexpr\
    \ montgomery(std::uint64_t m) : _m(m), im(m), r2(-__uint128_t(m) % m) {\n    \
    \    for (int i = 0; i < 5; ++i) im = im * (2 - _m * im);\n        im = -im;\n\
    \    }\n\n    // @return m\n    constexpr std::uint64_t umod() const { return\
    \ _m; }\n\n    // @param a `0 <= a < m`\n    // @param b `0 <= b < m`\n    //\
    \ @return `a * b % m`\n    constexpr std::uint64_t mul(std::uint64_t a, std::uint64_t\
    \ b) const { return mr(mr(a, b), r2); }\n\n    constexpr std::uint64_t exp(std::uint64_t\
    \ a, std::uint64_t b) const {\n        std::uint64_t res = 1, p = mr(a, r2);\n\
    \        while (b) {\n            if (b & 1) res = mr(res, p);\n            p\
    \ = mr(p, p);\n            b >>= 1;\n        }\n        return res;\n    }\n\n\
    \    constexpr bool same_pow(std::uint64_t x, int s, std::uint64_t n) const {\n\
    \        x = mr(x, r2), n = mr(n, r2);\n        for (int r = 0; r < s; r++) {\n\
    \            if (x == n) return true;\n            x = mr(x, x);\n        }\n\
    \        return false;\n    }\n\n  private:\n    constexpr std::uint64_t mr(std::uint64_t\
    \ x) const {\n        return ((__uint128_t)(x * im) * _m + x) >> 64;\n    }\n\
    \    constexpr std::uint64_t mr(std::uint64_t a, std::uint64_t b) const {\n  \
    \      __uint128_t t = (__uint128_t)a * b;\n        std::uint64_t inc = std::uint64_t(t)\
    \ != 0;\n        std::uint64_t x = t >> 64, y = ((__uint128_t)(a * b * im) * _m)\
    \ >> 64;\n        unsigned long long z = 0;\n        bool f = __builtin_uaddll_overflow(x,\
    \ y, &z);\n        z += inc;\n        return f ? z - _m : z;\n    }\n};\n\nconstexpr\
    \ bool is_SPRP32(std::uint32_t n, std::uint32_t a) {\n    std::uint32_t d = n\
    \ - 1, s = 0;\n    while ((d & 1) == 0) ++s, d >>= 1;\n    std::uint64_t cur =\
    \ 1, pw = d;\n    while (pw) {\n        if (pw & 1) cur = (cur * a) % n;\n   \
    \     a = (std::uint64_t)a * a % n;\n        pw >>= 1;\n    }\n    if (cur ==\
    \ 1) return true;\n    for (std::uint32_t r = 0; r < s; r++) {\n        if (cur\
    \ == n - 1) return true;\n        cur = cur * cur % n;\n    }\n    return false;\n\
    }\n\n// given 2 <= n,a < 2^64, a prime, check whether n is a-SPRP\nconstexpr bool\
    \ is_SPRP64(const montgomery &m, std::uint64_t a) {\n    auto n = m.umod();\n\
    \    if (n == a) return true;\n    if (n % a == 0) return false;\n    std::uint64_t\
    \ d = n - 1;\n    int s = 0;\n    while ((d & 1) == 0) ++s, d >>= 1;\n    std::uint64_t\
    \ cur = m.exp(a, d);\n    if (cur == 1) return true;\n    return m.same_pow(cur,\
    \ s, n - 1);\n}\n\nconstexpr bool is_prime_constexpr(std::uint64_t x) {\n    if\
    \ (x == 2 || x == 3 || x == 5 || x == 7) return true;\n    if (x % 2 == 0 || x\
    \ % 3 == 0 || x % 5 == 0 || x % 7 == 0) return false;\n    if (x < 121) return\
    \ (x > 1);\n    montgomery m(x);\n    constexpr std::uint64_t bases[] = {2, 325,\
    \ 9375, 28178, 450775, 9780504, 1795265022};\n    for (auto a : bases) {\n   \
    \     if (!is_SPRP64(m, a)) return false;\n    }\n    return true;\n}\n\nconstexpr\
    \ bool is_prime_constexpr(std::int64_t x) {\n    if (x < 0) return false;\n  \
    \  return is_prime_constexpr(std::uint64_t(x));\n}\n\nconstexpr bool is_prime_constexpr(std::uint32_t\
    \ x) {\n    if (x == 2 || x == 3 || x == 5 || x == 7) return true;\n    if (x\
    \ % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0) return false;\n    if (x\
    \ < 121) return (x > 1);\n    std::uint64_t h = x;\n    h = ((h >> 16) ^ h) *\
    \ 0x45d9f3b;\n    h = ((h >> 16) ^ h) * 0x45d9f3b;\n    h = ((h >> 16) ^ h) &\
    \ 255;\n    constexpr uint16_t bases[] = {\n        15591, 2018,  166,   7429,\
    \  8064,  16045, 10503, 4399,  1949,  1295,  2776,  3620,  560,\n        3128,\
    \  5212,  2657,  2300,  2021,  4652,  1471,  9336,  4018,  2398,  20462, 10277,\
    \ 8028,\n        2213,  6219,  620,   3763,  4852,  5012,  3185,  1333,  6227,\
    \  5298,  1074,  2391,  5113,\n        7061,  803,   1269,  3875,  422,   751,\
    \   580,   4729,  10239, 746,   2951,  556,   2206,\n        3778,  481,   1522,\
    \  3476,  481,   2487,  3266,  5633,  488,   3373,  6441,  3344,  17,\n      \
    \  15105, 1490,  4154,  2036,  1882,  1813,  467,   3307,  14042, 6371,  658,\
    \   1005,  903,\n        737,   1887,  7447,  1888,  2848,  1784,  7559,  3400,\
    \  951,   13969, 4304,  177,   41,\n        19875, 3110,  13221, 8726,  571, \
    \  7043,  6943,  1199,  352,   6435,  165,   1169,  3315,\n        978,   233,\
    \   3003,  2562,  2994,  10587, 10030, 2377,  1902,  5354,  4447,  1555,  263,\n\
    \        27027, 2283,  305,   669,   1912,  601,   6186,  429,   1930,  14873,\
    \ 1784,  1661,  524,\n        3577,  236,   2360,  6146,  2850,  55637, 1753,\
    \  4178,  8466,  222,   2579,  2743,  2031,\n        2226,  2276,  374,   2132,\
    \  813,   23788, 1610,  4422,  5159,  1725,  3597,  3366,  14336,\n        579,\
    \   165,   1375,  10018, 12616, 9816,  1371,  536,   1867,  10864, 857,   2206,\
    \  5788,\n        434,   8085,  17618, 727,   3639,  1595,  4944,  2129,  2029,\
    \  8195,  8344,  6232,  9183,\n        8126,  1870,  3296,  7455,  8947,  25017,\
    \ 541,   19115, 368,   566,   5674,  411,   522,\n        1027,  8215,  2050,\
    \  6544,  10049, 614,   774,   2333,  3007,  35201, 4706,  1152,  1785,\n    \
    \    1028,  1540,  3743,  493,   4474,  2521,  26845, 8354,  864,   18915, 5465,\
    \  2447,  42,\n        4511,  1660,  166,   1249,  6259,  2553,  304,   272, \
    \  7286,  73,    6554,  899,   2816,\n        5197,  13330, 7054,  2818,  3199,\
    \  811,   922,   350,   7514,  4452,  3449,  2663,  4708,\n        418,   1621,\
    \  1171,  3471,  88,    11345, 412,   1559,  194};\n    return is_SPRP32(x, bases[h]);\n\
    }\n\n// @param n `0 <= n`\n// @param m `1 <= m`\n// @return `(x ** n) % m`\nconstexpr\
    \ std::int64_t pow_mod_constexpr(std::int64_t x, std::int64_t n, int m) {\n  \
    \  if (m == 1) return 0;\n    unsigned int _m = (unsigned int)(m);\n    std::uint64_t\
    \ r = 1;\n    std::uint64_t y = safe_mod(x, m);\n    while (n) {\n        if (n\
    \ & 1) r = (r * y) % _m;\n        y = (y * y) % _m;\n        n >>= 1;\n    }\n\
    \    return r;\n}\n\n// Reference:\n// M. Forisek and J. Jancina,\n// Fast Primality\
    \ Testing for Integers That Fit into a Machine Word\n// @param n `0 <= n`\nconstexpr\
    \ bool is_prime_constexpr(int n) {\n    if (n <= 1) return false;\n    if (n ==\
    \ 2 || n == 7 || n == 61) return true;\n    if (n % 2 == 0) return false;\n  \
    \  std::int64_t d = n - 1;\n    while (d % 2 == 0) d /= 2;\n    constexpr std::int64_t\
    \ bases[3] = {2, 7, 61};\n    for (std::int64_t a : bases) {\n        std::int64_t\
    \ t = d;\n        std::int64_t y = pow_mod_constexpr(a, t, n);\n        while\
    \ (t != n - 1 && y != 1 && y != n - 1) {\n            y = y * y % n;\n       \
    \     t <<= 1;\n        }\n        if (y != n - 1 && t % 2 == 0) {\n         \
    \   return false;\n        }\n    }\n    return true;\n}\ntemplate <int n>\nconstexpr\
    \ bool is_prime = is_prime_constexpr(n);\n\n// @param b `1 <= b`\n// @return pair(g,\
    \ x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g\nconstexpr std::pair<std::int64_t,\
    \ std::int64_t> inv_gcd(std::int64_t a, std::int64_t b) {\n    a = safe_mod(a,\
    \ b);\n    if (a == 0) return {b, 0};\n    std::int64_t s = b, t = a;\n    std::int64_t\
    \ m0 = 0, m1 = 1;\n    while (t) {\n        std::int64_t u = s / t;\n        s\
    \ -= t * u;\n        m0 -= m1 * u;\n        auto tmp = s;\n        s = t;\n  \
    \      t = tmp;\n        tmp = m0;\n        m0 = m1;\n        m1 = tmp;\n    }\n\
    \    if (m0 < 0) m0 += b / s;\n    return {s, m0};\n}\n\n// Compile time primitive\
    \ root\n// @param m must be prime\n// @return primitive root (and minimum in now)\n\
    constexpr int primitive_root_constexpr(int m) {\n    if (m == 2) return 1;\n \
    \   if (m == 167772161) return 3;\n    if (m == 469762049) return 3;\n    if (m\
    \ == 754974721) return 11;\n    if (m == 998244353) return 3;\n    int divs[20]\
    \ = {};\n    divs[0] = 2;\n    int cnt = 1;\n    int x = (m - 1) / 2;\n    while\
    \ (x % 2 == 0) x /= 2;\n    for (int i = 3; (std::int64_t)(i)*i <= x; i += 2)\
    \ {\n        if (x % i == 0) {\n            divs[cnt++] = i;\n            while\
    \ (x % i == 0) {\n                x /= i;\n            }\n        }\n    }\n \
    \   if (x > 1) {\n        divs[cnt++] = x;\n    }\n    for (int g = 2;; g++) {\n\
    \        bool ok = true;\n        for (int i = 0; i < cnt; i++) {\n          \
    \  if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {\n                ok\
    \ = false;\n                break;\n            }\n        }\n        if (ok)\
    \ return g;\n    }\n}\ntemplate <int m>\nconstexpr int primitive_root = primitive_root_constexpr(m);\n\
    \n// @param n `n < 2^32`\n// @param m `1 <= m < 2^32`\n// @return sum_{i=0}^{n-1}\
    \ floor((ai + b) / m) (mod 2^64)\nstd::uint64_t floor_sum_unsigned(std::uint64_t\
    \ n, std::uint64_t m, std::uint64_t a,\n                                 std::uint64_t\
    \ b) {\n    std::uint64_t ans = 0;\n    while (true) {\n        if (a >= m) {\n\
    \            ans += n * (n - 1) / 2 * (a / m);\n            a %= m;\n        }\n\
    \        if (b >= m) {\n            ans += n * (b / m);\n            b %= m;\n\
    \        }\n\n        std::uint64_t y_max = a * n + b;\n        if (y_max < m)\
    \ break;\n        // y_max < m * (n + 1)\n        // floor(y_max / m) <= n\n \
    \       n = (std::uint64_t)(y_max / m);\n        b = (std::uint64_t)(y_max % m);\n\
    \        std::swap(m, a);\n    }\n    return ans;\n}\n\n}  // namespace internal\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/internal/internal_math.hpp
  requiredBy:
  - lib/internal/internal_fft.hpp
  - lib/math/combination.hpp
  - lib/math/modint.hpp
  - lib/math/floor_sum.hpp
  - lib/math/enumeration.hpp
  - lib/math/sqrt.hpp
  - lib/data_structure/bigint.hpp
  - lib/fft/garner.hpp
  - lib/fft/formal_power_series.hpp
  - lib/fft/ntt_mod.hpp
  - lib/fft/ntt.hpp
  timestamp: '2023-09-26 21:06:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/ntl/division.test.cpp
  - test/aoj/ntl/remainder.test.cpp
  - test/aoj/ntl/multiplication.test.cpp
  - test/aoj/ntl/difference.test.cpp
  - test/aoj/ntl/addition.test.cpp
  - test/aoj/ntl/multiplication2.test.cpp
  - test/aoj/ntl/power.test.cpp
  - test/aoj/jag/aho_corasick.test.cpp
  - test/aoj/dpl/bell.test.cpp
  - test/aoj/dpl/stirling.test.cpp
  - test/yosupo/matrix/matrix_product.test.cpp
  - test/yosupo/matrix/determinant_of_matrix.test.cpp
  - test/yosupo/math/number_of_subsequences.test.cpp
  - test/yosupo/math/sqrt_mod.test.cpp
  - test/yosupo/tree/tree_path_composite_sum.test.cpp
  - test/yosupo/data_structure/range_affine_range_sum.test.cpp
  - test/yosupo/data_structure/addition_of_big_integers.test.cpp
  - test/yosupo/data_structure/point_set_range_composite.test.cpp
  - test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  - test/yosupo/data_structure/queue_operate_all_composite.test.cpp
  - test/yosupo/convolution/convolution.test.cpp
  - test/yosupo/convolution/bitwise_xor_convolution.test.cpp
  - test/yosupo/convolution/convolution_mod.test.cpp
  - test/yosupo/convolution/bitwise_and_convolution.test.cpp
documentation_of: lib/internal/internal_math.hpp
layout: document
redirect_from:
- /library/lib/internal/internal_math.hpp
- /library/lib/internal/internal_math.hpp.html
title: lib/internal/internal_math.hpp
---
