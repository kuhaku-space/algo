---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: lib/graph/graph.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  - icon: ':heavy_check_mark:'
    path: lib/tree/union_find.hpp
    title: lib/tree/union_find.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n#include \"graph/graph.hpp\"\r\n#include\
    \ \"tree/union_find.hpp\"\r\n\r\n// verify : https://onlinejudge.u-aizu.ac.jp/problems/GRL_2_A\
    \ 21/02/24\r\n\r\n// \u6700\u5C0F\u5168\u57DF\u6728\r\ntemplate <class T>\r\n\
    vector<typename Graph<T>::edge> kruskal(const Graph<T> &g) {\r\n    using _edge\
    \ = typename Graph<T>::edge;\r\n    union_find uf(g.size());\r\n    vector<_edge>\
    \ res;\r\n    vector<_edge> edge_list;\r\n    for (auto &v : g) {\r\n        for\
    \ (auto &e : v) edge_list.emplace_back(e);\r\n    }\r\n    sort(edge_list.begin(),\
    \ edge_list.end());\r\n    for (auto &e : edge_list) {\r\n        if (!uf.is_same(e.from,\
    \ e.to)) {\r\n            uf.unite(e.from, e.to);\r\n            res.emplace_back(e);\r\
    \n        }\r\n    }\r\n    return res;\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  - lib/graph/graph.hpp
  - lib/tree/union_find.hpp
  isVerificationFile: false
  path: lib/graph/kruskal.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/graph/kruskal.hpp
layout: document
redirect_from:
- /library/lib/graph/kruskal.hpp
- /library/lib/graph/kruskal.hpp.html
title: lib/graph/kruskal.hpp
---
