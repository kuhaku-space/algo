---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/graph/bellman_ford.hpp
    title: lib/graph/bellman_ford.hpp
  - icon: ':warning:'
    path: lib/graph/dijkstra.hpp
    title: lib/graph/dijkstra.hpp
  - icon: ':warning:'
    path: lib/graph/kruskal.hpp
    title: lib/graph/kruskal.hpp
  - icon: ':warning:'
    path: lib/graph/lowlink.hpp
    title: lib/graph/lowlink.hpp
  - icon: ':warning:'
    path: lib/graph/scc.hpp
    title: lib/graph/scc.hpp
  - icon: ':warning:'
    path: lib/graph/topological_sort.hpp
    title: lib/graph/topological_sort.hpp
  - icon: ':warning:'
    path: lib/graph/two_sat.hpp
    title: lib/graph/two_sat.hpp
  - icon: ':warning:'
    path: lib/tree/tree.hpp
    title: lib/tree/tree.hpp
  - icon: ':warning:'
    path: lib/tree/tree_dist.hpp
    title: lib/tree/tree_dist.hpp
  - icon: ':warning:'
    path: lib/tree/tree_parent.hpp
    title: lib/tree/tree_parent.hpp
  - icon: ':warning:'
    path: lib/tree/tree_subtree.hpp
    title: lib/tree/tree_subtree.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/graph/shortest_path.test.cpp
    title: test/yosupo/graph/shortest_path.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"template/template.hpp\"\r\n\r\ntemplate <class\
    \ T>\r\nstruct Graph {\r\n    struct edge {\r\n        int from, to;\r\n     \
    \   T dist;\r\n\r\n        bool operator<(const edge &rhs) const { return this->dist\
    \ < rhs.dist; }\r\n        bool operator>(const edge &rhs) const { return rhs\
    \ < *this; }\r\n    };\r\n    vector<vector<edge>> edges;\r\n\r\n    Graph(int\
    \ v) : edges(v) {}\r\n\r\n    const auto &operator[](int i) const { return this->edges[i];\
    \ }\r\n    auto &operator[](int i) { return this->edges[i]; }\r\n    const auto\
    \ begin() const { return this->edges.begin(); }\r\n    auto begin() { return this->edges.begin();\
    \ }\r\n    const auto end() const { return this->edges.end(); }\r\n    auto end()\
    \ { return this->edges.end(); }\r\n    auto size() const { return this->edges.size();\
    \ }\r\n    void add_edge(int a, int b, T d = T(1)) { this->edges[a].emplace_back(edge{a,\
    \ b, d}); }\r\n    void add_edges(int a, int b, T d = T(1)) {\r\n        this->edges[a].emplace_back(edge{a,\
    \ b, d});\r\n        this->edges[b].emplace_back(edge{b, a, d});\r\n    }\r\n\
    \    void input_edge(int m, bool zero_based = false) {\r\n        for (int i =\
    \ 0; i < m; ++i) {\r\n            int a, b;\r\n            T d;\r\n          \
    \  cin >> a >> b >> d;\r\n            if (zero_based)\r\n                this->add_edge(a,\
    \ b, d);\r\n            else\r\n                this->add_edge(a - 1, b - 1, d);\r\
    \n        }\r\n    }\r\n    void input_edges(int m, bool zero_based = false) {\r\
    \n        for (int i = 0; i < m; ++i) {\r\n            int a, b;\r\n         \
    \   T d;\r\n            cin >> a >> b >> d;\r\n            if (zero_based)\r\n\
    \                this->add_edges(a, b, d);\r\n            else\r\n           \
    \     this->add_edges(a - 1, b - 1, d);\r\n        }\r\n    }\r\n};\r\n\r\ntemplate\
    \ <>\r\nstruct Graph<void> {\r\n    vector<vector<int>> edges;\r\n\r\n    Graph(int\
    \ v) : edges(v) {}\r\n\r\n    const auto &operator[](int i) const { return this->edges[i];\
    \ }\r\n    auto &operator[](int i) { return this->edges[i]; }\r\n    const auto\
    \ begin() const { return this->edges.begin(); }\r\n    auto begin() { return this->edges.begin();\
    \ }\r\n    const auto end() const { return this->edges.end(); }\r\n    auto end()\
    \ { return this->edges.end(); }\r\n    auto size() const { return this->edges.size();\
    \ }\r\n    void add_edge(int a, int b) { this->edges[a].emplace_back(b); }\r\n\
    \    void add_edges(int a, int b) {\r\n        this->edges[a].emplace_back(b);\r\
    \n        this->edges[b].emplace_back(a);\r\n    }\r\n    void input_edge(int\
    \ m, bool zero_based = false) {\r\n        for (int i = 0; i < m; ++i) {\r\n \
    \           int a, b;\r\n            cin >> a >> b;\r\n            if (zero_based)\r\
    \n                this->add_edge(a, b);\r\n            else\r\n              \
    \  this->add_edge(a - 1, b - 1);\r\n        }\r\n    }\r\n    void input_edges(int\
    \ m, bool zero_based = false) {\r\n        for (int i = 0; i < m; ++i) {\r\n \
    \           int a, b;\r\n            cin >> a >> b;\r\n            if (zero_based)\r\
    \n                this->add_edges(a, b);\r\n            else\r\n             \
    \   this->add_edges(a - 1, b - 1);\r\n        }\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/graph.hpp
  requiredBy:
  - lib/graph/dijkstra.hpp
  - lib/graph/topological_sort.hpp
  - lib/graph/scc.hpp
  - lib/graph/bellman_ford.hpp
  - lib/graph/lowlink.hpp
  - lib/graph/two_sat.hpp
  - lib/graph/kruskal.hpp
  - lib/tree/tree.hpp
  - lib/tree/tree_subtree.hpp
  - lib/tree/tree_parent.hpp
  - lib/tree/tree_dist.hpp
  timestamp: '2021-09-22 06:52:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/graph/shortest_path.test.cpp
documentation_of: lib/graph/graph.hpp
layout: document
redirect_from:
- /library/lib/graph/graph.hpp
- /library/lib/graph/graph.hpp.html
title: lib/graph/graph.hpp
---
