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
    path: test/aoj/grl/prim.test.cpp
    title: test/aoj/grl/prim.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30D7\u30EA\u30E0\u6CD5"
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
  code: "#pragma once\n#include \"graph/graph.hpp\"\n#include \"template/template.hpp\"\
    \n\n/**\n * @brief \u30D7\u30EA\u30E0\u6CD5\n * @details \u6700\u5C0F\u5168\u57DF\
    \u6728\u3092\u6C42\u3081\u308B\n *\n * @tparam T \u8FBA\u306E\u91CD\u307F\u306E\
    \u578B\n * @param g \u30B0\u30E9\u30D5\n * @param r \u59CB\u70B9\n * @return std::vector<typename\
    \ Graph<T>::edge_type>\n */\ntemplate <class T>\nstd::vector<typename Graph<T>::edge_type>\
    \ prim(const Graph<T> &g, int r = 0) {\n    using _edge = typename Graph<T>::edge_type;\n\
    \    std::vector<_edge> res;\n    std::vector<bool> visited(g.size());\n    visited[r]\
    \ = true;\n    std::priority_queue<_edge, std::vector<_edge>, greater<>> p_que;\n\
    \    for (auto &e : g[r]) { p_que.emplace(e); }\n    while (!p_que.empty()) {\n\
    \        auto edge = p_que.top();\n        p_que.pop();\n        if (visited[edge.to()])\
    \ continue;\n        visited[edge.to()] = true;\n        res.emplace_back(edge);\n\
    \        for (auto &e : g[edge.to()]) {\n            if (!visited[e.to()]) p_que.emplace(e);\n\
    \        }\n    }\n    return res;\n}\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/prim.hpp
  requiredBy: []
  timestamp: '2022-05-13 04:24:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/prim.test.cpp
documentation_of: lib/graph/prim.hpp
layout: document
redirect_from:
- /library/lib/graph/prim.hpp
- /library/lib/graph/prim.hpp.html
title: "\u30D7\u30EA\u30E0\u6CD5"
---
