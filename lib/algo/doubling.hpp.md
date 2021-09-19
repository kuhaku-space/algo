---
data:
  _extendedDependsOn:
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
  code: "#include \"template/template.hpp\"\r\n\r\nstruct Doubling {\r\n    const\
    \ int size = 64;\r\n    int n;\r\n    vector<vector<int>> data;\r\n\r\n    Doubling(int\
    \ _n) : n(_n), data(size, vector<int>(_n)) {}\r\n\r\n    void build(const vector<int>\
    \ &v) {\r\n        for (int i = 0; i < n; ++i) data[0][i] = v[i];\r\n\r\n    \
    \    for (int i = 0; i < size - 1; ++i) {\r\n            for (int j = 0; j < n;\
    \ ++j) {\r\n                data[i + 1][j] = data[i][data[i][j]];\r\n        \
    \    }\r\n        }\r\n    }\r\n\r\n    int solve(int f, int64_t k) {\r\n    \
    \    for (int cnt = 0; k > 0; k >>= 1, ++cnt) {\r\n            if (k & 1) f =\
    \ data[cnt][f];\r\n        }\r\n        return f;\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/algo/doubling.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/algo/doubling.hpp
layout: document
redirect_from:
- /library/lib/algo/doubling.hpp
- /library/lib/algo/doubling.hpp.html
title: lib/algo/doubling.hpp
---
