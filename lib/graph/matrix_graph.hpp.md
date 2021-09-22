---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/graph/warshall_floyd.hpp
    title: lib/graph/warshall_floyd.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/all_pairs_shortest_path.test.cpp
    title: test/aoj/all_pairs_shortest_path.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
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
  code: "#pragma once\r\n#include \"template/template.hpp\"\r\n\r\ntemplate <class\
    \ T>\r\nstruct matrix_graph {\r\n    int V;\r\n    vector<vector<T>> m;\r\n\r\n\
    \    matrix_graph(int v, T _e = T()) : V(v) {\r\n        m = vector<vector<T>>(V,\
    \ vector<T>(V, _e));\r\n    }\r\n\r\n    const auto &operator[](int i) const {\
    \ return m[i]; }\r\n    auto &operator[](int i) { return m[i]; }\r\n    const\
    \ auto begin() const { return m.begin(); }\r\n    auto begin() { return m.begin();\
    \ }\r\n    const auto end() const { return m.end(); }\r\n    auto end() { return\
    \ m.end(); }\r\n\r\n    int size() const { return V; }\r\n\r\n    void add_edge(int\
    \ a, int b, T d = T(1)) { m[a][b] = d; }\r\n    void add_edges(int a, int b, T\
    \ d = T(1)) {\r\n        m[a][b] = d;\r\n        m[b][a] = d;\r\n    }\r\n\r\n\
    \    void complement() {\r\n        for (int i = 0; i < V; ++i) {\r\n        \
    \    for (int j = 0; j < V; ++j) m[i][j] = !m[i][j];\r\n        }\r\n    }\r\n\
    };\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/matrix_graph.hpp
  requiredBy:
  - lib/graph/warshall_floyd.hpp
  timestamp: '2021-09-22 06:33:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/all_pairs_shortest_path.test.cpp
documentation_of: lib/graph/matrix_graph.hpp
layout: document
redirect_from:
- /library/lib/graph/matrix_graph.hpp
- /library/lib/graph/matrix_graph.hpp.html
title: lib/graph/matrix_graph.hpp
---
