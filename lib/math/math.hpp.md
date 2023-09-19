---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/math/pow.hpp
    title: lib/math/pow.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/pow.hpp:\
    \ line -1: no such header\n"
  code: "#include \"math/pow.hpp\"\r\n#include \"template/template.hpp\"\r\n\r\nstd::int64_t\
    \ gcd(std::int64_t a, std::int64_t b) {\r\n    while (b) {\r\n        a %= b;\r\
    \n        std::swap(a, b);\r\n    }\r\n    return a;\r\n}\r\n\r\nstd::int64_t\
    \ gcd(const std::vector<std::int64_t> &v) {\r\n    if (v.empty()) return 1;\r\n\
    \    std::int64_t res = v[0];\r\n    for (auto i : v) res = gcd(res, i);\r\n \
    \   return res;\r\n}\r\n\r\nstd::int64_t lcm(std::int64_t a, std::int64_t b) {\r\
    \n    return a / gcd(a, b) * b;\r\n}\r\n\r\nstd::int64_t lcm(const std::vector<std::int64_t>\
    \ &v) {\r\n    std::int64_t res = 1;\r\n    for (auto i : v) res = lcm(res, i);\r\
    \n    return res;\r\n}\r\n\r\nstd::int64_t floor_div(std::int64_t p, std::int64_t\
    \ q) {\r\n    std::int64_t res = p / q;\r\n    if (q * res > p) --res;\r\n   \
    \ return res;\r\n}\r\n\r\nstd::int64_t ceil_div(std::int64_t p, std::int64_t q)\
    \ {\r\n    std::int64_t res = p / q;\r\n    if (q * res < p) ++res;\r\n    return\
    \ res;\r\n}\r\n\r\nstd::int64_t round_ll(double d) {\r\n    if (d < 0) return\
    \ -round_ll(-d);\r\n    return std::int64_t(d + 0.5);\r\n}\r\n\r\nstd::int64_t\
    \ round_ll(long double d) {\r\n    if (d < 0) return -round_ll(-d);\r\n    return\
    \ std::int64_t(d + 0.5);\r\n}\r\n\r\nconstexpr bool is_prime(int n) {\r\n    if\
    \ (n <= 1) return false;\r\n    if (n == 2 || n == 7 || n == 61) return true;\r\
    \n    if (n % 2 == 0) return false;\r\n    std::int64_t d = n - 1;\r\n    while\
    \ (d % 2 == 0) d /= 2;\r\n    constexpr std::int64_t bases[3] = {2, 7, 61};\r\n\
    \    for (std::int64_t a : bases) {\r\n        std::int64_t t = d;\r\n       \
    \ std::int64_t y = pow_mod(a, t, n);\r\n        while (t != n - 1 && y != 1 &&\
    \ y != n - 1) {\r\n            y = y * y % n;\r\n            t <<= 1;\r\n    \
    \    }\r\n        if (y != n - 1 && t % 2 == 0) {\r\n            return false;\r\
    \n        }\r\n    }\r\n    return true;\r\n}\r\n"
  dependsOn:
  - lib/math/pow.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/math.hpp
  requiredBy: []
  timestamp: '2023-05-22 20:02:34+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/math.hpp
layout: document
redirect_from:
- /library/lib/math/math.hpp
- /library/lib/math/math.hpp.html
title: lib/math/math.hpp
---
