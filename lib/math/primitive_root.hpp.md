---
data:
  _extendedDependsOn:
  - icon: ':warning:'
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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n#include \"math/pow.hpp\"\r\n\r\nint\
    \ get_primitive_root(const int mod) {\r\n    if (mod == 998244353) return 3;\r\
    \n    int64_t divs[20] = {};\r\n    divs[0] = 2;\r\n    int64_t cnt = 1;\r\n \
    \   int64_t x = (mod - 1) / 2;\r\n    while (x % 2 == 0) x /= 2;\r\n    for (int64_t\
    \ i = 3; i * i <= x; i += 2) {\r\n        if (x % i == 0) {\r\n            divs[cnt++]\
    \ = i;\r\n            while (x % i == 0) x /= i;\r\n        }\r\n    }\r\n   \
    \ if (x > 1) divs[cnt++] = x;\r\n    for (int64_t g = 2;; ++g) {\r\n        bool\
    \ ok = true;\r\n        for (int64_t i = 0; i < cnt; ++i) {\r\n            if\
    \ (pow_mod(g, (mod - 1) / divs[i], mod) == 1) {\r\n                ok = false;\r\
    \n                break;\r\n            }\r\n        }\r\n        if (ok) return\
    \ g;\r\n    }\r\n    return 0;\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  - lib/math/pow.hpp
  isVerificationFile: false
  path: lib/math/primitive_root.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/primitive_root.hpp
layout: document
redirect_from:
- /library/lib/math/primitive_root.hpp
- /library/lib/math/primitive_root.hpp.html
title: lib/math/primitive_root.hpp
---
