---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: lib/graph/graph.hpp
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/abc061/tasks/abc061_d
    - https://atcoder.jp/contests/abc137/tasks/abc137_e
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n#include \"graph/graph.hpp\"\r\n\r\n\
    // verify : https://atcoder.jp/contests/abc137/tasks/abc137_e 21/02/24\r\n// verify\
    \ : https://atcoder.jp/contests/abc061/tasks/abc061_d 21/02/24\r\n\r\ntemplate\
    \ <class T>\r\nvector<T> bellman_ford(const Graph<T> &g, int s = 0,\r\n      \
    \                 T inf = numeric_limits<T>::max()) {\r\n    int n = g.size();\r\
    \n    vector<T> dist(n, inf);\r\n    dist[s] = T();\r\n    bool flg = true;\r\n\
    \    for (int cnt = 0; flg && cnt <= n << 1; ++cnt) {\r\n        flg = false;\r\
    \n        for (int i = 0; i < n; ++i) {\r\n            if (dist[i] == inf) continue;\r\
    \n            for (auto &j : g[i]) {\r\n                if (dist[i] == -inf ||\
    \ chmin(dist[j.to], dist[i] + j.dist)) {\r\n                    if (dist[j.to]\
    \ == -inf) continue;\r\n                    flg = true;\r\n                  \
    \  if (cnt >= n) dist[j.to] = -inf;\r\n                }\r\n            }\r\n\
    \        }\r\n    }\r\n    return dist;\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  - lib/graph/graph.hpp
  isVerificationFile: false
  path: lib/graph/bellman_ford.hpp
  requiredBy: []
  timestamp: '2021-09-22 06:52:24+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/graph/bellman_ford.hpp
layout: document
redirect_from:
- /library/lib/graph/bellman_ford.hpp
- /library/lib/graph/bellman_ford.hpp.html
title: lib/graph/bellman_ford.hpp
---
