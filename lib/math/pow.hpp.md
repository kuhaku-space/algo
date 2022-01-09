---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/math/primitive_root.hpp
    title: lib/math/primitive_root.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <class T>\r\nT power(T\
    \ a, int64_t n) {\r\n    T res(1), mul(a);\r\n    for (; n > 0; n >>= 1) {\r\n\
    \        if (n & 1) res *= mul;\r\n        mul *= mul;\r\n    }\r\n    return\
    \ res;\r\n}\r\n\r\nint64_t pow_int(int64_t a, int64_t n) {\r\n    assert(n >=\
    \ 0);\r\n    int64_t res = 1, mul = a;\r\n    for (; n > 0; n >>= 1) {\r\n   \
    \     if (n & 1) res *= mul;\r\n        mul *= mul;\r\n    }\r\n    return res;\r\
    \n}\r\n\r\nint64_t inv_mod(int64_t a, int64_t mod) {\r\n    int64_t b = mod, u\
    \ = 1, v = 0, t;\r\n    while (b > 0) {\r\n        t = a / b;\r\n        swap(a\
    \ -= t * b, b);\r\n        swap(u -= t * v, v);\r\n    }\r\n    return u >= 0\
    \ ? u % mod : (mod - (-u) % mod) % mod;\r\n}\r\n\r\nint64_t pow_mod(int64_t a,\
    \ int64_t n, int64_t mod) {\r\n    // if (n < 0) return inv_mod(pow_mod(a, -n,\
    \ mod), mod);\r\n    int64_t res = 1, mul = a;\r\n    for (; n > 0; n >>= 1) {\r\
    \n        if (n & 1) (res *= mul) %= mod;\r\n        (mul *= mul) %= mod;\r\n\
    \    }\r\n    return res;\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/pow.hpp
  requiredBy:
  - lib/math/primitive_root.hpp
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/pow.hpp
layout: document
redirect_from:
- /library/lib/math/pow.hpp
- /library/lib/math/pow.hpp.html
title: lib/math/pow.hpp
---
