---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/bellman_ford.test.cpp
    title: test/aoj/grl/bellman_ford.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30D9\u30EB\u30DE\u30F3\u30D5\u30A9\u30FC\u30C9\u6CD5"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#include \"graph/graph.hpp\"\r\n#include \"template/template.hpp\"\r\n\r\n\
    /**\r\n * @brief \u30D9\u30EB\u30DE\u30F3\u30D5\u30A9\u30FC\u30C9\u6CD5\r\n *\r\
    \n * @tparam T\r\n * @param graph \u30B0\u30E9\u30D5\r\n * @param s \u59CB\u70B9\
    \r\n * @param inf\r\n * @return std::vector<T>\r\n */\r\ntemplate <class T>\r\n\
    std::vector<T> bellman_ford(const Graph<T> &graph, int s = 0,\r\n            \
    \                T inf = std::numeric_limits<T>::max()) {\r\n    int n = graph.size();\r\
    \n    std::vector<T> dists(n, inf);\r\n    dists[s] = T();\r\n    bool updated\
    \ = true;\r\n    for (int count = 0; updated && count <= n << 1; ++count) {\r\n\
    \        updated = false;\r\n        for (int i = 0; i < n; ++i) {\r\n       \
    \     if (dists[i] == inf) continue;\r\n            for (auto &e : graph[i]) {\r\
    \n                if (dists[i] == -inf || chmin(dists[e.to()], dists[i] + e.weight()))\
    \ {\r\n                    if (dists[e.to()] == -inf) continue;\r\n          \
    \          updated = true;\r\n                    if (count >= n) dists[e.to()]\
    \ = -inf;\r\n                }\r\n            }\r\n        }\r\n    }\r\n    return\
    \ dists;\r\n}\r\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/bellman_ford.hpp
  requiredBy: []
  timestamp: '2023-10-12 00:40:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/bellman_ford.test.cpp
documentation_of: lib/graph/bellman_ford.hpp
layout: document
redirect_from:
- /library/lib/graph/bellman_ford.hpp
- /library/lib/graph/bellman_ford.hpp.html
title: "\u30D9\u30EB\u30DE\u30F3\u30D5\u30A9\u30FC\u30C9\u6CD5"
---
