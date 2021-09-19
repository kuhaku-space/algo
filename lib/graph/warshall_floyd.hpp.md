---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/graph/graph_matrix.hpp
    title: lib/graph/graph_matrix.hpp
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
  code: "#include \"template/template.hpp\"\r\n#include \"graph/graph_matrix.hpp\"\
    \r\n\r\ntemplate <class T>\r\nvoid warshall_floyd(Graph<T> &g) {\r\n    int n\
    \ = g.size();\r\n    for (int i = 0; i < n; ++i) g[i][i] = 0;\r\n    for (int\
    \ k = 0; k < n; ++k) {\r\n        for (int i = 0; i < n; ++i) {\r\n          \
    \  for (int j = 0; j < n; ++j) {\r\n                chmin(g[i][j], g[i][k] + g[k][j]);\r\
    \n            }\r\n        }\r\n    }\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  - lib/graph/graph_matrix.hpp
  isVerificationFile: false
  path: lib/graph/warshall_floyd.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/graph/warshall_floyd.hpp
layout: document
redirect_from:
- /library/lib/graph/warshall_floyd.hpp
- /library/lib/graph/warshall_floyd.hpp.html
title: lib/graph/warshall_floyd.hpp
---
