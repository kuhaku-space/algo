---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/matrix_graph.hpp
    title: "\u96A3\u63A5\u884C\u5217"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/warshall_floyd.test.cpp
    title: test/aoj/grl/warshall_floyd.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/jag/hopcroft_karp.test.cpp
    title: test/aoj/jag/hopcroft_karp.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/matrix_graph.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"graph/matrix_graph.hpp\"\r\n#include \"template/template.hpp\"\
    \r\n\r\ntemplate <class T>\r\nvoid warshall_floyd(matrix_graph<T> &g) {\r\n  \
    \  int n = g.size();\r\n    for (int i = 0; i < n; ++i) g[i][i] = T();\r\n   \
    \ for (int k = 0; k < n; ++k) {\r\n        for (int i = 0; i < n; ++i) {\r\n \
    \           for (int j = 0; j < n; ++j) {\r\n                chmin(g[i][j], g[i][k]\
    \ + g[k][j]);\r\n            }\r\n        }\r\n    }\r\n}\r\n"
  dependsOn:
  - lib/graph/matrix_graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/warshall_floyd.hpp
  requiredBy: []
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/jag/hopcroft_karp.test.cpp
  - test/aoj/grl/warshall_floyd.test.cpp
documentation_of: lib/graph/warshall_floyd.hpp
layout: document
redirect_from:
- /library/lib/graph/warshall_floyd.hpp
- /library/lib/graph/warshall_floyd.hpp.html
title: lib/graph/warshall_floyd.hpp
---
