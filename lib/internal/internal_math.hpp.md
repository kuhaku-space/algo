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
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt.hpp
    title: lib/fft/ntt.hpp
  - icon: ':warning:'
    path: lib/fft/ntt_mod.hpp
    title: "\u4EFB\u610Fmod\u6570\u8AD6\u5909\u63DB"
  - icon: ':heavy_check_mark:'
    path: lib/math/combination.hpp
    title: lib/math/combination.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/enumeration.hpp
    title: lib/math/enumeration.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: lib/math/modint.hpp
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
    path: test/yosupo/convolution/convolution.test.cpp
    title: test/yosupo/convolution/convolution.test.cpp
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
    path: test/yosupo/matrix/matrix_product.test.cpp
    title: test/yosupo/matrix/matrix_product.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/new/number_of_subsequences.test.cpp
    title: test/yosupo/new/number_of_subsequences.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/tree/tree_path_composite_sum.test.cpp
    title: test/yosupo/tree/tree_path_composite_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://en.wikipedia.org/wiki/Barrett_reduction
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
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
    \        std::uint64_t x = (std::uint64_t)(((unsigned __int128)(z)*im) >> 64);\n\
    \        std::uint64_t y = x * _m;\n        return (unsigned int)(z - y + (z <\
    \ y ? _m : 0));\n    }\n};\n\n// @param n `0 <= n`\n// @param m `1 <= m`\n// @return\
    \ `(x ** n) % m`\nconstexpr std::int64_t pow_mod_constexpr(std::int64_t x, std::int64_t\
    \ n, int m) {\n    if (m == 1) return 0;\n    unsigned int _m = (unsigned int)(m);\n\
    \    std::uint64_t r = 1;\n    std::uint64_t y = safe_mod(x, m);\n    while (n)\
    \ {\n        if (n & 1) r = (r * y) % _m;\n        y = (y * y) % _m;\n       \
    \ n >>= 1;\n    }\n    return r;\n}\n\n// Reference:\n// M. Forisek and J. Jancina,\n\
    // Fast Primality Testing for Integers That Fit into a Machine Word\n// @param\
    \ n `0 <= n`\nconstexpr bool is_prime_constexpr(int n) {\n    if (n <= 1) return\
    \ false;\n    if (n == 2 || n == 7 || n == 61) return true;\n    if (n % 2 ==\
    \ 0) return false;\n    std::int64_t d = n - 1;\n    while (d % 2 == 0) d /= 2;\n\
    \    constexpr std::int64_t bases[3] = {2, 7, 61};\n    for (std::int64_t a :\
    \ bases) {\n        std::int64_t t = d;\n        std::int64_t y = pow_mod_constexpr(a,\
    \ t, n);\n        while (t != n - 1 && y != 1 && y != n - 1) {\n            y\
    \ = y * y % n;\n            t <<= 1;\n        }\n        if (y != n - 1 && t %\
    \ 2 == 0) {\n            return false;\n        }\n    }\n    return true;\n}\n\
    template <int n>\nconstexpr bool is_prime = is_prime_constexpr(n);\n\n// @param\
    \ b `1 <= b`\n// @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x\
    \ < b/g\nconstexpr std::pair<std::int64_t, std::int64_t> inv_gcd(std::int64_t\
    \ a, std::int64_t b) {\n    a = safe_mod(a, b);\n    if (a == 0) return {b, 0};\n\
    \    std::int64_t s = b, t = a;\n    std::int64_t m0 = 0, m1 = 1;\n    while (t)\
    \ {\n        std::int64_t u = s / t;\n        s -= t * u;\n        m0 -= m1 *\
    \ u;\n        auto tmp = s;\n        s = t;\n        t = tmp;\n        tmp = m0;\n\
    \        m0 = m1;\n        m1 = tmp;\n    }\n    if (m0 < 0) m0 += b / s;\n  \
    \  return {s, m0};\n}\n\n// Compile time primitive root\n// @param m must be prime\n\
    // @return primitive root (and minimum in now)\nconstexpr int primitive_root_constexpr(int\
    \ m) {\n    if (m == 2) return 1;\n    if (m == 167772161) return 3;\n    if (m\
    \ == 469762049) return 3;\n    if (m == 754974721) return 11;\n    if (m == 998244353)\
    \ return 3;\n    int divs[20] = {};\n    divs[0] = 2;\n    int cnt = 1;\n    int\
    \ x = (m - 1) / 2;\n    while (x % 2 == 0) x /= 2;\n    for (int i = 3; (std::int64_t)(i)*i\
    \ <= x; i += 2) {\n        if (x % i == 0) {\n            divs[cnt++] = i;\n \
    \           while (x % i == 0) {\n                x /= i;\n            }\n   \
    \     }\n    }\n    if (x > 1) {\n        divs[cnt++] = x;\n    }\n    for (int\
    \ g = 2;; g++) {\n        bool ok = true;\n        for (int i = 0; i < cnt; i++)\
    \ {\n            if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {\n    \
    \            ok = false;\n                break;\n            }\n        }\n \
    \       if (ok) return g;\n    }\n}\ntemplate <int m>\nconstexpr int primitive_root\
    \ = primitive_root_constexpr(m);\n\n// @param n `n < 2^32`\n// @param m `1 <=\
    \ m < 2^32`\n// @return sum_{i=0}^{n-1} floor((ai + b) / m) (mod 2^64)\nstd::uint64_t\
    \ floor_sum_unsigned(std::uint64_t n, std::uint64_t m, std::uint64_t a,\n    \
    \                             std::uint64_t b) {\n    std::uint64_t ans = 0;\n\
    \    while (true) {\n        if (a >= m) {\n            ans += n * (n - 1) / 2\
    \ * (a / m);\n            a %= m;\n        }\n        if (b >= m) {\n        \
    \    ans += n * (b / m);\n            b %= m;\n        }\n\n        std::uint64_t\
    \ y_max = a * n + b;\n        if (y_max < m) break;\n        // y_max < m * (n\
    \ + 1)\n        // floor(y_max / m) <= n\n        n = (std::uint64_t)(y_max /\
    \ m);\n        b = (std::uint64_t)(y_max % m);\n        std::swap(m, a);\n   \
    \ }\n    return ans;\n}\n\n}  // namespace internal\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/internal/internal_math.hpp
  requiredBy:
  - lib/data_structure/bigint.hpp
  - lib/fft/ntt.hpp
  - lib/fft/formal_power_series.hpp
  - lib/fft/ntt_mod.hpp
  - lib/math/combination.hpp
  - lib/math/enumeration.hpp
  - lib/math/modint.hpp
  timestamp: '2023-05-17 11:33:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/new/number_of_subsequences.test.cpp
  - test/yosupo/tree/tree_path_composite_sum.test.cpp
  - test/yosupo/convolution/convolution.test.cpp
  - test/yosupo/data_structure/point_set_range_composite.test.cpp
  - test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  - test/yosupo/data_structure/range_affine_range_sum.test.cpp
  - test/yosupo/data_structure/queue_operate_all_composite.test.cpp
  - test/yosupo/matrix/matrix_product.test.cpp
  - test/aoj/jag/aho_corasick.test.cpp
  - test/aoj/dpl/bell.test.cpp
  - test/aoj/dpl/stirling.test.cpp
  - test/aoj/ntl/multiplication.test.cpp
  - test/aoj/ntl/division.test.cpp
  - test/aoj/ntl/remainder.test.cpp
  - test/aoj/ntl/multiplication2.test.cpp
  - test/aoj/ntl/power.test.cpp
  - test/aoj/ntl/difference.test.cpp
  - test/aoj/ntl/addition.test.cpp
documentation_of: lib/internal/internal_math.hpp
layout: document
redirect_from:
- /library/lib/internal/internal_math.hpp
- /library/lib/internal/internal_math.hpp.html
title: lib/internal/internal_math.hpp
---
