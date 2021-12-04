---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/fft/garner.hpp
    title: lib/fft/garner.hpp
  - icon: ':x:'
    path: lib/fft/ntt.hpp
    title: lib/fft/ntt.hpp
  - icon: ':x:'
    path: lib/math/modint.hpp
    title: modint
  - icon: ':warning:'
    path: lib/math/modint64.hpp
    title: lib/math/modint64.hpp
  - icon: ':x:'
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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: fft/garner.hpp:\
    \ line -1: no such header\n"
  code: "#include \"fft/garner.hpp\"\r\n#include \"fft/ntt.hpp\"\r\n#include \"math/modint64.hpp\"\
    \r\n#include \"template/template.hpp\"\r\n\r\nusing NTT_1 = NTT<167772161, 3>;\
    \   // 2^25 * 5 + 1\r\nusing NTT_2 = NTT<469762049, 3>;   // 2^26 * 7 + 1\r\n\
    using NTT_3 = NTT<1224736769, 3>;  // 2^24 * 73 + 1\r\n\r\nvector<int64_t> convolution(vector<int64_t>\
    \ a, vector<int64_t> b, int mod) {\r\n    const int n = a.size() + b.size() -\
    \ 1;\r\n    for (auto& i : a) i %= mod;\r\n    for (auto& i : b) i %= mod;\r\n\
    \    NTT_1 ntt1;\r\n    NTT_2 ntt2;\r\n    NTT_3 ntt3;\r\n    auto x = ntt1.convolution(a,\
    \ b);\r\n    auto y = ntt2.convolution(a, b);\r\n    auto z = ntt3.convolution(a,\
    \ b);\r\n\r\n    vector<int64_t> res(n);\r\n    vector<int64_t> r(3), m(3);\r\n\
    \    for (int i = 0; i < n; ++i) {\r\n        r[0] = x[i], m[0] = ntt1.get_mod();\r\
    \n        r[1] = y[i], m[1] = ntt2.get_mod();\r\n        r[2] = z[i], m[2] = ntt3.get_mod();\r\
    \n        res[i] = garner(r, m, mod);\r\n    }\r\n\r\n    return res;\r\n}\r\n\
    \r\nvector<int64_t> power(vector<int64_t> v, int64_t x) {\r\n    int64_t n = v.size();\r\
    \n    vector<int64_t> res(n);\r\n    res[0] = 1;\r\n    for (; x > 0; x >>= 1)\
    \ {\r\n        if (x & 1) {\r\n            res = convolution(res, v, MOD);\r\n\
    \            res.resize(n);\r\n        }\r\n        v = convolution(v, v, MOD);\r\
    \n        v.resize(n);\r\n    }\r\n    return res;\r\n}\r\n"
  dependsOn:
  - lib/fft/garner.hpp
  - lib/template/template.hpp
  - lib/fft/ntt.hpp
  - lib/math/modint.hpp
  - lib/math/modint64.hpp
  isVerificationFile: false
  path: lib/fft/ntt_mod.hpp
  requiredBy: []
  timestamp: '2021-11-06 08:06:01+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/fft/ntt_mod.hpp
layout: document
redirect_from:
- /library/lib/fft/ntt_mod.hpp
- /library/lib/fft/ntt_mod.hpp.html
title: lib/fft/ntt_mod.hpp
---
