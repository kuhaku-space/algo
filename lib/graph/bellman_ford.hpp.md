---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/graph/graph.hpp
    title: lib/graph/graph.hpp
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aoj/grl/bellman_ford.test.cpp
    title: test/aoj/grl/bellman_ford.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "\u30D9\u30EB\u30DE\u30F3\u30D5\u30A9\u30FC\u30C9\u6CD5"
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
  code: "#include \"template/template.hpp\"\r\n#include \"graph/graph.hpp\"\r\n\r\n\
    /**\r\n * @brief \u30D9\u30EB\u30DE\u30F3\u30D5\u30A9\u30FC\u30C9\u6CD5\r\n *\
    \ \r\n * @tparam T \r\n * @param graph \u30B0\u30E9\u30D5\r\n * @param s \u59CB\
    \u70B9\r\n * @param inf \r\n * @return vector<T> \r\n */\r\ntemplate <class T>\r\
    \nvector<T> bellman_ford(const Graph<T> &graph, int s = 0,\r\n               \
    \        T inf = numeric_limits<T>::max()) {\r\n    int n = graph.size();\r\n\
    \    vector<T> dists(n, inf);\r\n    dists[s] = T();\r\n    bool is_updated =\
    \ true;\r\n    for (int count = 0; is_updated && count <= n << 1; ++count) {\r\
    \n        is_updated = false;\r\n        for (int i = 0; i < n; ++i) {\r\n   \
    \         if (dists[i] == inf) continue;\r\n            for (auto &j : graph[i])\
    \ {\r\n                if (dists[i] == -inf || chmin(dists[j.to], dists[i] + j.dists))\
    \ {\r\n                    if (dists[j.to] == -inf) continue;\r\n            \
    \        is_updated = true;\r\n                    if (count >= n) dists[j.to]\
    \ = -inf;\r\n                }\r\n            }\r\n        }\r\n    }\r\n    return\
    \ dists;\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  - lib/graph/graph.hpp
  isVerificationFile: false
  path: lib/graph/bellman_ford.hpp
  requiredBy: []
  timestamp: '2022-02-06 19:57:45+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/aoj/grl/bellman_ford.test.cpp
documentation_of: lib/graph/bellman_ford.hpp
layout: document
redirect_from:
- /library/lib/graph/bellman_ford.hpp
- /library/lib/graph/bellman_ford.hpp.html
title: "\u30D9\u30EB\u30DE\u30F3\u30D5\u30A9\u30FC\u30C9\u6CD5"
---
