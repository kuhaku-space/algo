---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  - icon: ':heavy_check_mark:'
    path: lib/tree/union_find.hpp
    title: "\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/kruskal.test.cpp
    title: test/aoj/grl/kruskal.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30AF\u30E9\u30B9\u30AB\u30EB\u6CD5"
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
    \r\n#include \"tree/union_find.hpp\"\r\n\r\n/**\r\n * @brief \u30AF\u30E9\u30B9\
    \u30AB\u30EB\u6CD5\r\n * @details \u6700\u5C0F\u5168\u57DF\u6728\u3092\u6C42\u3081\
    \u308B\r\n *\r\n * @tparam T \u8FBA\u306E\u91CD\u307F\u306E\u578B\r\n * @param\
    \ g \u30B0\u30E9\u30D5\r\n * @return std::vector<typename Graph<T>::edge_type>\r\
    \n */\r\ntemplate <class T>\r\nstd::vector<typename Graph<T>::edge_type> kruskal(const\
    \ Graph<T> &g) {\r\n    using _edge = typename Graph<T>::edge_type;\r\n    union_find\
    \ uf(g.size());\r\n    std::vector<_edge> res;\r\n    std::vector<_edge> edge_list;\r\
    \n    for (auto &v : g) {\r\n        for (auto &e : v) edge_list.emplace_back(e);\r\
    \n    }\r\n    std::sort(edge_list.begin(), edge_list.end());\r\n    for (auto\
    \ &e : edge_list) {\r\n        if (!uf.same(e.from(), e.to())) {\r\n         \
    \   uf.unite(e.from(), e.to());\r\n            res.emplace_back(e);\r\n      \
    \  }\r\n    }\r\n    return res;\r\n}\r\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  - lib/tree/union_find.hpp
  isVerificationFile: false
  path: lib/graph/kruskal.hpp
  requiredBy: []
  timestamp: '2022-03-25 03:44:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/kruskal.test.cpp
documentation_of: lib/graph/kruskal.hpp
layout: document
redirect_from:
- /library/lib/graph/kruskal.hpp
- /library/lib/graph/kruskal.hpp.html
title: "\u30AF\u30E9\u30B9\u30AB\u30EB\u6CD5"
---
