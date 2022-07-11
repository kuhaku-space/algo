---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/math/pow.hpp
    title: lib/math/pow.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/fft/ntt_mod.hpp
    title: "\u4EFB\u610Fmod\u6570\u8AD6\u5909\u63DB"
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/pow.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"math/pow.hpp\"\r\n#include \"template/template.hpp\"\
    \r\n\r\ntemplate <class T>\r\nint garner(std::vector<T> r, std::vector<int> m,\
    \ const int mod) {\r\n    int n = r.size();\r\n    r.emplace_back(0);\r\n    m.emplace_back(mod);\r\
    \n\r\n    std::vector<std::int64_t> coffs(n + 1, 1);\r\n    std::vector<std::int64_t>\
    \ constants(n + 1, 0);\r\n    for (int i = 0; i < n; ++i) {\r\n        int v =\
    \ (r[i] - constants[i]) * inv_mod(coffs[i], m[i]) % m[i];\r\n        if (v < 0)\
    \ v += m[i];\r\n\r\n        for (int j = i + 1; j < n + 1; ++j) {\r\n        \
    \    (constants[j] += coffs[j] * v) %= m[j];\r\n            (coffs[j] *= m[i])\
    \ %= m[j];\r\n        }\r\n    }\r\n\r\n    return constants[n];\r\n}\r\n"
  dependsOn:
  - lib/math/pow.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/fft/garner.hpp
  requiredBy:
  - lib/fft/ntt_mod.hpp
  timestamp: '2022-06-18 18:40:23+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/fft/garner.hpp
layout: document
redirect_from:
- /library/lib/fft/garner.hpp
- /library/lib/fft/garner.hpp.html
title: lib/fft/garner.hpp
---
