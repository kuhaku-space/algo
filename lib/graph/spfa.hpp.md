---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/spfa.test.cpp
    title: test/aoj/grl/spfa.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: SPFA
    links:
    - https://ei1333.github.io/luzhiled/snippets/graph/shortest-path-faster-algorithm.html
    - https://hogloid.hatenablog.com/entry/20120409/1333973448
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#include \"graph/graph.hpp\"\n#include \"template/template.hpp\"\n\n/**\n\
    \ * @brief SPFA\n *\n * @tparam T \u8FBA\u306E\u91CD\u307F\u306E\u578B\n * @param\
    \ g \u30B0\u30E9\u30D5\n * @param s \u59CB\u70B9\n * @param inf\n * @return std::vector<T>\n\
    \ *\n * @see https://hogloid.hatenablog.com/entry/20120409/1333973448\n * @see\
    \ https://ei1333.github.io/luzhiled/snippets/graph/shortest-path-faster-algorithm.html\n\
    \ */\ntemplate <class T>\nstd::vector<T> shortest_path_faster_algorithm(Graph<T>\
    \ &g, int s,\n                                              T inf = std::numeric_limits<T>::max())\
    \ {\n    int n = g.size();\n    std::vector<T> dists(n, inf);\n    std::vector<int>\
    \ pending(n, 0), times(n, 0);\n    std::queue<int> que;\n\n    que.emplace(s);\n\
    \    pending[s] = true;\n    ++times[s];\n    dists[s] = 0;\n\n    while (!que.empty())\
    \ {\n        int p = que.front();\n        que.pop();\n        pending[p] = false;\n\
    \        for (auto &e : g[p]) {\n            if (!chmin(dists[e.to()], dists[p]\
    \ + e.weight())) continue;\n            if (!pending[e.to()]) {\n            \
    \    if (++times[e.to()] >= n) return std::vector<T>();\n                pending[e.to()]\
    \ = true;\n                que.emplace(e.to());\n            }\n        }\n  \
    \  }\n    return dists;\n}\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/spfa.hpp
  requiredBy: []
  timestamp: '2023-10-12 00:40:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/spfa.test.cpp
documentation_of: lib/graph/spfa.hpp
layout: document
redirect_from:
- /library/lib/graph/spfa.hpp
- /library/lib/graph/spfa.hpp.html
title: SPFA
---
