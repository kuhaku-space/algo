---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/fft/garner.hpp
    title: lib/fft/garner.hpp
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt.hpp
    title: "\u6570\u8AD6\u5909\u63DB"
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: modint
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
    document_title: "\u4EFB\u610Fmod\u6570\u8AD6\u5909\u63DB"
    links:
    - https://asako.growi.cloud/compro/NTT
    - https://math314.hateblo.jp/entry/2015/05/07/014908
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: fft/garner.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"fft/garner.hpp\"\r\n#include \"fft/ntt.hpp\"\r\
    \n#include \"template/template.hpp\"\r\n\r\nusing NTT_1 = NTT<167772161, 3>; \
    \  // 2^25 * 5 + 1\r\nusing NTT_2 = NTT<469762049, 3>;   // 2^26 * 7 + 1\r\nusing\
    \ NTT_3 = NTT<998244353, 3>;   // 2^23 * 119 + 1\r\nusing NTT_4 = NTT<1224736769,\
    \ 3>;  // 2^24 * 73 + 1\r\n\r\n/**\r\n * @brief \u4EFB\u610Fmod\u6570\u8AD6\u5909\
    \u63DB\r\n * @see https://math314.hateblo.jp/entry/2015/05/07/014908\r\n * @see\
    \ https://asako.growi.cloud/compro/NTT\r\n *\r\n * @tparam T\r\n * @param a\r\n\
    \ * @param b\r\n * @param mod\r\n * @return std::vector<int>\r\n */\r\ntemplate\
    \ <class T, class U>\r\nstd::vector<int> convolution(std::vector<T> a, std::vector<U>\
    \ b, int mod) {\r\n    const int n = a.size() + b.size() - 1;\r\n    for (auto&\
    \ i : a) i %= mod;\r\n    for (auto& i : b) i %= mod;\r\n    auto x = NTT_1::convolution(a,\
    \ b);\r\n    auto y = NTT_2::convolution(a, b);\r\n    auto z = NTT_3::convolution(a,\
    \ b);\r\n\r\n    std::vector<int> res(n);\r\n    std::vector<int> r(3), m(3);\r\
    \n    for (int i = 0; i < n; ++i) {\r\n        r[0] = (int)x[i], m[0] = NTT_1::get_mod();\r\
    \n        r[1] = (int)y[i], m[1] = NTT_2::get_mod();\r\n        r[2] = (int)z[i],\
    \ m[2] = NTT_3::get_mod();\r\n        res[i] = garner(r, m, mod);\r\n    }\r\n\
    \r\n    return res;\r\n}\r\n\r\ntemplate <class T>\r\nstd::vector<T> power(std::vector<T>\
    \ v, std::int64_t x, int mod = MOD) {\r\n    int n = v.size();\r\n    std::vector<T>\
    \ res(n);\r\n    res[0] = 1;\r\n    for (; x; x >>= 1) {\r\n        if (x & 1)\
    \ {\r\n            res = convolution(res, v, mod);\r\n            res.resize(n);\r\
    \n        }\r\n        v = convolution(v, v, mod);\r\n        v.resize(n);\r\n\
    \    }\r\n    return res;\r\n}\r\n"
  dependsOn:
  - lib/fft/garner.hpp
  - lib/math/pow.hpp
  - lib/template/template.hpp
  - lib/fft/ntt.hpp
  - lib/math/modint.hpp
  isVerificationFile: false
  path: lib/fft/ntt_mod.hpp
  requiredBy: []
  timestamp: '2022-07-31 15:35:50+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/fft/ntt_mod.hpp
layout: document
redirect_from:
- /library/lib/fft/ntt_mod.hpp
- /library/lib/fft/ntt_mod.hpp.html
title: "\u4EFB\u610Fmod\u6570\u8AD6\u5909\u63DB"
---
