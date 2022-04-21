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
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#include \"graph/graph.hpp\"\n#include \"template/template.hpp\"\n\ntemplate\
    \ <class T>\nstd::vector<int> tree_bfs(const Graph<T> &g, int r = 0) {\n    int\
    \ pos = 0;\n    std::vector<int> res;\n    std::vector<bool> visited(g.size());\n\
    \    res.emplace_back(r);\n    visited[r] = true;\n    while (pos < res.size())\
    \ {\n        auto index = res[pos++];\n        for (auto &e : g[index]) {\n  \
    \          if (visited[e.to()]) continue;\n            res.emplace_back(e.to());\n\
    \            visited[e.to()] = true;\n        }\n    }\n    return res;\n}\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/tree_bfs.hpp
  requiredBy: []
  timestamp: '2022-04-14 07:10:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/tree_bfs.hpp
layout: document
redirect_from:
- /library/lib/tree/tree_bfs.hpp
- /library/lib/tree/tree_bfs.hpp.html
title: lib/tree/tree_bfs.hpp
---
