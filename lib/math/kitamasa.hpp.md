---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/alds1/kitamasa.test.cpp
    title: test/aoj/alds1/kitamasa.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\ntemplate <class T>\nT kitamasa(const\
    \ std::vector<T> &a, const std::vector<T> &d, std::int64_t n) {\n    assert(a.size()\
    \ == d.size());\n    const int k = d.size();\n    if (n < k) return a[n];\n  \
    \  std::vector<int> bits;\n    while (n > k * 2) {\n        bits.emplace_back(n\
    \ & 1);\n        n >>= 1;\n    }\n    std::vector<T> x = d, y(k);\n    for (int\
    \ i = k; i < n; ++i) {\n        std::swap(x, y);\n        for (int i = 0; i <\
    \ k; ++i) x[i] = d[i] * y[k - 1];\n        for (int i = 0; i + 1 < k; ++i) x[i\
    \ + 1] += y[i];\n    }\n    std::reverse(std::begin(bits), std::end(bits));\n\
    \    std::vector<std::vector<T>> v(k, std::vector<T>(k));\n    for (auto &&bit\
    \ : bits) {\n        v[0] = x;\n        for (int i = 0; i + 1 < k; ++i) {\n  \
    \          for (int j = 0; j < k; ++j) v[i + 1][j] = d[j] * v[i][k - 1];\n   \
    \         for (int j = 0; j + 1 < k; ++j) v[i + 1][j + 1] += v[i][j];\n      \
    \  }\n        std::fill(std::begin(x), std::end(x), T());\n        for (int i\
    \ = 0; i < k; ++i) {\n            for (int j = 0; j < k; ++j) x[j] += v[0][i]\
    \ * v[i][j];\n        }\n        if (bit) {\n            std::swap(x, y);\n  \
    \          for (int i = 0; i < k; ++i) x[i] = d[i] * y[k - 1];\n            for\
    \ (int i = 0; i + 1 < k; ++i) x[i + 1] += y[i];\n        }\n    }\n    T res{};\n\
    \    for (int i = 0; i < k; ++i) res += x[i] * a[i];\n    return res;\n}\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/kitamasa.hpp
  requiredBy: []
  timestamp: '2023-07-27 07:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/alds1/kitamasa.test.cpp
documentation_of: lib/math/kitamasa.hpp
layout: document
redirect_from:
- /library/lib/math/kitamasa.hpp
- /library/lib/math/kitamasa.hpp.html
title: lib/math/kitamasa.hpp
---
