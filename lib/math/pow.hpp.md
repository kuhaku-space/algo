---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/math/primitive_root.hpp
    title: lib/math/primitive_root.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/dual_segment_tree.hpp
    title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/segment_tree.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/rmq.test.cpp
    title: test/aoj/dsl/rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/ruq.test.cpp
    title: test/aoj/dsl/ruq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/static_rmq.test.cpp
    title: test/yosupo/data_structure/static_rmq.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\nint64_t pow_int(int64_t a, int64_t\
    \ n) {\r\n    assert(n >= 0);\r\n    int64_t res = 1, mul = a;\r\n    for (; n\
    \ > 0; n >>= 1) {\r\n        if (n & 1) res *= mul;\r\n        mul *= mul;\r\n\
    \    }\r\n    return res;\r\n}\r\n\r\nint64_t inv_mod(int64_t a, int64_t mod)\
    \ {\r\n    int64_t b = mod, u = 1, v = 0, t;\r\n    while (b > 0) {\r\n      \
    \  t = a / b;\r\n        swap(a -= t * b, b);\r\n        swap(u -= t * v, v);\r\
    \n    }\r\n    return u >= 0 ? u % mod : (mod - (-u) % mod) % mod;\r\n}\r\n\r\n\
    int64_t pow_mod(int64_t a, int64_t n, int64_t mod) {\r\n    if (n < 0) return\
    \ inv_mod(pow_mod(a, -n, mod), mod);\r\n    int64_t res = 1, mul = a;\r\n    for\
    \ (; n > 0; n >>= 1) {\r\n        if (n & 1) (res *= mul) %= mod;\r\n        (mul\
    \ *= mul) %= mod;\r\n    }\r\n    return res;\r\n}\r\n\r\nint ceil_pow2(int n)\
    \ {\r\n    int x = 0;\r\n    while ((1U << x) < (unsigned int)(n)) x++;\r\n  \
    \  return x;\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/pow.hpp
  requiredBy:
  - lib/math/primitive_root.hpp
  - lib/segment_tree/dual_segment_tree.hpp
  - lib/segment_tree/segment_tree.hpp
  timestamp: '2022-01-13 23:29:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/static_rmq.test.cpp
  - test/aoj/dsl/ruq.test.cpp
  - test/aoj/dsl/rmq.test.cpp
documentation_of: lib/math/pow.hpp
layout: document
redirect_from:
- /library/lib/math/pow.hpp
- /library/lib/math/pow.hpp.html
title: lib/math/pow.hpp
---
