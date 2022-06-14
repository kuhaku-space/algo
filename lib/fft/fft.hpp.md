---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/agc047/tasks/agc047_c
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n// i * j = g^(x + y) \u3068\u3057\
    \u3066FFT\u306B\u5E30\u7740\r\n// verify : https://atcoder.jp/contests/agc047/tasks/agc047_c\
    \ 21/02/24\r\n\r\nnamespace FFT {\r\nusing CP = complex<double>;\r\n\r\nvoid _fft(vector<CP>\
    \ &a, bool inv) {\r\n    int N = a.size();\r\n    static bool is_first = true;\r\
    \n    static vector<CP> vbw(30), vibw(30);\r\n    if (is_first) {\r\n        is_first\
    \ = false;\r\n        for (int i = 0; i < 30; ++i) {\r\n            vbw[i] = polar(1.0,\
    \ 2.0 * PI / (1 << (i + 1)));\r\n            vibw[i] = polar(1.0, -2.0 * PI /\
    \ (1 << (i + 1)));\r\n        }\r\n    }\r\n    for (int i = 0, j = 1; j < N -\
    \ 1; ++j) {\r\n        for (int k = N >> 1; k > (i ^= k); k >>= 1)\r\n       \
    \     ;\r\n        if (i > j) swap(a[i], a[j]);\r\n    }\r\n    for (int k = 0,\
    \ t = 1; t < N; ++k, t <<= 1) {\r\n        CP bw = vbw[k];\r\n        if (inv)\
    \ bw = vibw[k];\r\n        for (int i = 0; i < N; i += t * 2) {\r\n          \
    \  CP w(1.0);\r\n            for (int j = 0; j < t; ++j) {\r\n               \
    \ int l = i + j, r = i + j + t;\r\n                CP c = a[l], d = a[r] * w;\r\
    \n                a[l] = c + d, a[r] = c - d;\r\n                w *= bw;\r\n\
    \            }\r\n        }\r\n    }\r\n    if (inv) {\r\n        for (int i =\
    \ 0; i < N; ++i) a[i] /= N;\r\n    }\r\n}\r\n\r\ntemplate <class T>\r\nvoid convolution_self(vector<T>\
    \ &a, const vector<T> &b) {\r\n    int n = a.size() + b.size() - 1;\r\n    int\
    \ N = 1;\r\n    while (N < n) N <<= 1;\r\n\r\n    vector<CP> va(N), vb(N);\r\n\
    \    for (int i = 0; i < a.size(); ++i) va[i] = CP(a[i]);\r\n    for (int i =\
    \ 0; i < b.size(); ++i) vb[i] = CP(b[i]);\r\n    _fft(va, false), _fft(vb, false);\r\
    \n    for (int i = 0; i < N; ++i) va[i] *= vb[i];\r\n    _fft(va, true);\r\n\r\
    \n    a.resize(n);\r\n    for (int i = 0; i < n; ++i) a[i] = T(va[i].real() +\
    \ 0.5);\r\n}\r\n\r\ntemplate <class T>\r\nvector<T> convolution(const vector<T>\
    \ &a, const vector<T> &b) {\r\n    vector<T> res = a;\r\n    convolution_self(res,\
    \ b);\r\n    return res;\r\n}\r\n}  // namespace FFT\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/fft/fft.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/fft/fft.hpp
layout: document
redirect_from:
- /library/lib/fft/fft.hpp
- /library/lib/fft/fft.hpp.html
title: lib/fft/fft.hpp
---
