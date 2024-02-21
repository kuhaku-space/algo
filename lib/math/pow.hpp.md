---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/math/math.hpp
    title: lib/math/math.hpp
  - icon: ':warning:'
    path: lib/math/primitive_root.hpp
    title: lib/math/primitive_root.hpp
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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"template/template.hpp\"\r\n\r\nstd::int64_t safe_mod(std::int64_t\
    \ a, std::int64_t mod) {\r\n    a %= mod;\r\n    return a >= 0 ? a : a + mod;\r\
    \n}\r\n\r\nstd::int64_t pow_int(std::int64_t a, std::int64_t n) {\r\n    assert(n\
    \ >= 0);\r\n    std::int64_t res = 1, mul = a;\r\n    for (; n > 0; n >>= 1) {\r\
    \n        if (n & 1) res *= mul;\r\n        mul *= mul;\r\n    }\r\n    return\
    \ res;\r\n}\r\n\r\nstd::int64_t inv_mod(std::int64_t a, std::int64_t mod) {\r\n\
    \    std::int64_t b = mod, u = 1, v = 0, t;\r\n    while (b > 0) {\r\n       \
    \ t = a / b;\r\n        std::swap(a -= t * b, b);\r\n        std::swap(u -= t\
    \ * v, v);\r\n    }\r\n    return u >= 0 ? u % mod : (mod - (-u) % mod) % mod;\r\
    \n}\r\n\r\nstd::int64_t pow_mod(std::int64_t a, std::int64_t n, std::int64_t mod)\
    \ {\r\n    if (n < 0) return inv_mod(pow_mod(a, -n, mod), mod);\r\n    std::int64_t\
    \ res = 1, mul = safe_mod(a, mod);\r\n    for (; n > 0; n >>= 1) {\r\n       \
    \ if (n & 1) (res *= mul) %= mod;\r\n        (mul *= mul) %= mod;\r\n    }\r\n\
    \    return res;\r\n}\r\n\r\nint ceil_pow2(std::int64_t n) {\r\n    int x = 0;\r\
    \n    while ((std::uint64_t(1) << x) < (std::uint64_t)(n)) ++x;\r\n    return\
    \ x;\r\n}\r\n\r\nint floor_pow2(std::int64_t n) {\r\n    int x = 0;\r\n    while\
    \ ((std::uint64_t(1) << (x + 1)) <= (std::uint64_t)(n)) ++x;\r\n    return x;\r\
    \n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/pow.hpp
  requiredBy:
  - lib/math/primitive_root.hpp
  - lib/math/math.hpp
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/pow.hpp
layout: document
redirect_from:
- /library/lib/math/pow.hpp
- /library/lib/math/pow.hpp.html
title: lib/math/pow.hpp
---
