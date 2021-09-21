---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/algo/modint.hpp
    title: lib/algo/modint.hpp
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt.hpp
    title: lib/fft/ntt.hpp
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n#include \"algo/modint.hpp\"\r\n#include\
    \ \"fft/ntt.hpp\"\r\n\r\ntemplate <class T>\r\nstruct formal_power_series {\r\n\
    \    vector<T> data;\r\n\r\n    formal_power_series(vector<T> _v) : data(_v) {}\r\
    \n\r\n    const Mint& operator[](const int64_t x) const { return data[x]; }\r\n\
    \    Mint& operator[](const int64_t x) { return data[x]; }\r\n\r\n    inline size_t\
    \ size() const { return data.size(); }\r\n\r\n    void resize(size_t _sz) { data.resize(_sz);\
    \ }\r\n\r\n    void pow(int64_t x) {\r\n        int64_t n = size();\r\n      \
    \  vector<int64_t> ans(n);\r\n        ans[0] = T(1);\r\n        for (; x > 0;\
    \ x >>= 1) {\r\n            if (x & 1) {\r\n                ntt.convolution_self(ans,\
    \ data);\r\n                ans.resize(n);\r\n            }\r\n            ntt.convolution_self(data,\
    \ data);\r\n            data.resize(n);\r\n        }\r\n        swap(data, ans);\r\
    \n    }\r\n\r\n    void conv_naive(const formal_power_series& a) {\r\n       \
    \ int64_t n = size() + a.size() - 1;\r\n        vector<T> ans(n);\r\n        for\
    \ (int64_t i = 0; i < a.size(); ++i) {\r\n            if (a[i] == 0) continue;\r\
    \n            for (int64_t j = 0; j < size(); ++j) {\r\n                ans[i\
    \ + j] += data[j] * a[i];\r\n            }\r\n        }\r\n        swap(data,\
    \ ans);\r\n    }\r\n\r\n    // data * (1 - x^n)\r\n    void mul(int64_t n) {\r\
    \n        for (int64_t i = size() - 1; i >= n; --i) data[i] -= data[i - n];\r\n\
    \    }\r\n\r\n    // data / (1 - x^n)\r\n    void div(int64_t n) {\r\n       \
    \ for (int64_t i = n; i < size(); ++i) data[i] += data[i - n];\r\n    }\r\n\r\n\
    \    void cumsum() {\r\n        for (int64_t i = 1; i < size(); ++i) data[i] +=\
    \ data[i - 1];\r\n    }\r\n\r\n    void cumsum_inv() {\r\n        for (int64_t\
    \ i = size() - 1; i > 0; --i) data[i] -= data[i - 1];\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  - lib/algo/modint.hpp
  - lib/fft/ntt.hpp
  isVerificationFile: false
  path: lib/fft/formal_power_series.hpp
  requiredBy: []
  timestamp: '2021-09-21 21:57:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/fft/formal_power_series.hpp
layout: document
redirect_from:
- /library/lib/fft/formal_power_series.hpp
- /library/lib/fft/formal_power_series.hpp.html
title: lib/fft/formal_power_series.hpp
---
