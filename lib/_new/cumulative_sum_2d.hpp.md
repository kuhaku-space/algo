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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <class T>\r\nstruct cumulative_sum_2d\
    \ {\r\n    vector<vector<T>> v;\r\n\r\n    cumulative_sum_2d(const vector<vector<T>>\
    \ &_v) : v(_v) { make(); }\r\n\r\n    void make() {\r\n        int n = v.size();\r\
    \n        int m = v[0].size();\r\n        v.resize(n + 1);\r\n        for (int\
    \ i = 0; i < n; ++i) v[i].resize(m + 1);\r\n        for (int i = n - 1; i >= 0;\
    \ --i) {\r\n            for (int j = n - 1; j >= 0; --j) {\r\n               \
    \ v[i][j] += v[i + 1][j];\r\n            }\r\n        }\r\n        for (int i\
    \ = n - 1; i >= 0; --i) {\r\n            for (int j = n - 1; j >= 0; --j) {\r\n\
    \                v[i][j] += v[i][j + 1];\r\n            }\r\n        }\r\n   \
    \ }\r\n\r\n    T get(int x1, int y1, int x2, int y2) {\r\n        return v[x1][y1]\
    \ - v[x1][y2] - v[x2][y1] + v[x2][y2];\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/_new/cumulative_sum_2d.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/_new/cumulative_sum_2d.hpp
layout: document
redirect_from:
- /library/lib/_new/cumulative_sum_2d.hpp
- /library/lib/_new/cumulative_sum_2d.hpp.html
title: lib/_new/cumulative_sum_2d.hpp
---
