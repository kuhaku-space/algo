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
    path: test/aoj/grl/topological_sort.test.cpp
    title: test/aoj/grl/topological_sort.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30C8\u30DD\u30ED\u30B8\u30AB\u30EB\u30BD\u30FC\u30C8"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/graph.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"graph/graph.hpp\"\r\n#include \"template/template.hpp\"\
    \r\n\r\n/**\r\n * @brief \u30C8\u30DD\u30ED\u30B8\u30AB\u30EB\u30BD\u30FC\u30C8\
    \r\n *\r\n * @tparam T \u8FBA\u306E\u91CD\u307F\u306E\u578B\r\n * @param g \u30B0\
    \u30E9\u30D5\r\n * @return std::vector<int> \u9802\u70B9\u306E\u9806\u5E8F\r\n\
    \ */\r\ntemplate <class T>\r\nstd::vector<int> topological_sort(const Graph<T>\
    \ &g) {\r\n    int n = g.size();\r\n    std::vector<int> res;\r\n    std::vector<bool>\
    \ seen(n);\r\n    auto dfs = [&](auto self, int v) {\r\n        if (seen[v]) return;\r\
    \n        seen[v] = true;\r\n        for (auto &e : g[v])\r\n            if (!seen[e.to()])\
    \ self(self, e.to());\r\n        res.emplace_back(v);\r\n    };\r\n    for (int\
    \ i = 0; i < n; ++i) dfs(dfs, i);\r\n    std::reverse(res.begin(), res.end());\r\
    \n    return res;\r\n}\r\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/topological_sort.hpp
  requiredBy: []
  timestamp: '2022-03-25 03:44:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/topological_sort.test.cpp
documentation_of: lib/graph/topological_sort.hpp
layout: document
redirect_from:
- /library/lib/graph/topological_sort.hpp
- /library/lib/graph/topological_sort.hpp.html
title: "\u30C8\u30DD\u30ED\u30B8\u30AB\u30EB\u30BD\u30FC\u30C8"
---
