---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/_old/tree.hpp
    title: lib/_old/tree.hpp
  - icon: ':heavy_check_mark:'
    path: lib/graph/bellman_ford.hpp
    title: "\u30D9\u30EB\u30DE\u30F3\u30D5\u30A9\u30FC\u30C9\u6CD5"
  - icon: ':heavy_check_mark:'
    path: lib/graph/dijkstra.hpp
    title: "\u30C0\u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5"
  - icon: ':heavy_check_mark:'
    path: lib/graph/dijkstra_heap.hpp
    title: "\u30C0\u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5\uFF08\u30D2\u30FC\u30D7\uFF09"
  - icon: ':warning:'
    path: lib/graph/dijkstra_potential.hpp
    title: lib/graph/dijkstra_potential.hpp
  - icon: ':heavy_check_mark:'
    path: lib/graph/kruskal.hpp
    title: "\u30AF\u30E9\u30B9\u30AB\u30EB\u6CD5"
  - icon: ':heavy_check_mark:'
    path: lib/graph/lowlink.hpp
    title: LowLink
  - icon: ':heavy_check_mark:'
    path: lib/graph/prim.hpp
    title: "\u30D7\u30EA\u30E0\u6CD5"
  - icon: ':heavy_check_mark:'
    path: lib/graph/scc.hpp
    title: "\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3"
  - icon: ':warning:'
    path: lib/graph/spanning_tree.hpp
    title: "\u5168\u57DF\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/graph/topological_sort.hpp
    title: "\u9589\u8DEF\u691C\u51FA"
  - icon: ':warning:'
    path: lib/graph/two_sat.hpp
    title: lib/graph/two_sat.hpp
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
    path: test/aoj/grl/articulation_points.test.cpp
    title: test/aoj/grl/articulation_points.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/bellman_ford.test.cpp
    title: test/aoj/grl/bellman_ford.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/bridges.test.cpp
    title: test/aoj/grl/bridges.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/cycle.test.cpp
    title: test/aoj/grl/cycle.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/dijkstra.test.cpp
    title: test/aoj/grl/dijkstra.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/dijkstra_binary.test.cpp
    title: test/aoj/grl/dijkstra_binary.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/dijkstra_fibonacci.test.cpp
    title: test/aoj/grl/dijkstra_fibonacci.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/dijkstra_radix.test.cpp
    title: test/aoj/grl/dijkstra_radix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/kruskal.test.cpp
    title: test/aoj/grl/kruskal.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/prim.test.cpp
    title: test/aoj/grl/prim.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/scc.test.cpp
    title: test/aoj/grl/scc.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/topological_sort.test.cpp
    title: test/aoj/grl/topological_sort.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/graph/shortest_path.test.cpp
    title: test/yosupo/graph/shortest_path.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
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
  code: "#pragma once\r\n#include \"template/template.hpp\"\r\n\r\ntemplate <class\
    \ T>\r\nstruct Graph {\r\n  private:\r\n    struct edge {\r\n        int from,\
    \ to;\r\n        T dist;\r\n        constexpr edge() : from(), to(), dist() {}\r\
    \n        constexpr edge(int _from, int _to, T _dist) : from(_from), to(_to),\
    \ dist(_dist) {}\r\n        bool operator<(const edge &rhs) const { return this->dist\
    \ < rhs.dist; }\r\n        bool operator>(const edge &rhs) const { return rhs\
    \ < *this; }\r\n    };\r\n\r\n  public:\r\n    using edge_type = edge;\r\n\r\n\
    \    Graph(int v) : edges(v) {}\r\n\r\n    const auto &operator[](int i) const\
    \ { return this->edges[i]; }\r\n    auto &operator[](int i) { return this->edges[i];\
    \ }\r\n    const auto begin() const { return this->edges.begin(); }\r\n    auto\
    \ begin() { return this->edges.begin(); }\r\n    const auto end() const { return\
    \ this->edges.end(); }\r\n    auto end() { return this->edges.end(); }\r\n   \
    \ auto size() const { return this->edges.size(); }\r\n    void add_edge(int a,\
    \ int b, T d = T(1)) { this->edges[a].emplace_back(a, b, d); }\r\n    void add_edges(int\
    \ a, int b, T d = T(1)) {\r\n        this->edges[a].emplace_back(a, b, d);\r\n\
    \        this->edges[b].emplace_back(b, a, d);\r\n    }\r\n    void input_edge(int\
    \ m, bool zero_based = false) {\r\n        for (int i = 0; i < m; ++i) {\r\n \
    \           int a, b;\r\n            T d;\r\n            cin >> a >> b >> d;\r\
    \n            if (zero_based)\r\n                this->add_edge(a, b, d);\r\n\
    \            else\r\n                this->add_edge(a - 1, b - 1, d);\r\n    \
    \    }\r\n    }\r\n    void input_edges(int m, bool zero_based = false) {\r\n\
    \        for (int i = 0; i < m; ++i) {\r\n            int a, b;\r\n          \
    \  T d;\r\n            cin >> a >> b >> d;\r\n            if (zero_based)\r\n\
    \                this->add_edges(a, b, d);\r\n            else\r\n           \
    \     this->add_edges(a - 1, b - 1, d);\r\n        }\r\n    }\r\n\r\n  private:\r\
    \n    std::vector<std::vector<edge>> edges;\r\n};\r\n\r\ntemplate <>\r\nstruct\
    \ Graph<void> {\r\n    using edge_type = std::pair<int, int>;\r\n    Graph(int\
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
    \   this->add_edges(a - 1, b - 1);\r\n        }\r\n    }\r\n\r\n  private:\r\n\
    \    std::vector<std::vector<int>> edges;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/graph.hpp
  requiredBy:
  - lib/tree/tree_subtree.hpp
  - lib/tree/tree_dist.hpp
  - lib/tree/tree_parent.hpp
  - lib/_old/tree.hpp
  - lib/graph/lowlink.hpp
  - lib/graph/two_sat.hpp
  - lib/graph/spanning_tree.hpp
  - lib/graph/topological_sort.hpp
  - lib/graph/dijkstra_potential.hpp
  - lib/graph/kruskal.hpp
  - lib/graph/prim.hpp
  - lib/graph/dijkstra_heap.hpp
  - lib/graph/scc.hpp
  - lib/graph/dijkstra.hpp
  - lib/graph/bellman_ford.hpp
  timestamp: '2022-03-05 10:24:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/graph/shortest_path.test.cpp
  - test/aoj/grl/articulation_points.test.cpp
  - test/aoj/grl/prim.test.cpp
  - test/aoj/grl/topological_sort.test.cpp
  - test/aoj/grl/dijkstra_binary.test.cpp
  - test/aoj/grl/dijkstra_fibonacci.test.cpp
  - test/aoj/grl/kruskal.test.cpp
  - test/aoj/grl/dijkstra.test.cpp
  - test/aoj/grl/dijkstra_radix.test.cpp
  - test/aoj/grl/bridges.test.cpp
  - test/aoj/grl/cycle.test.cpp
  - test/aoj/grl/bellman_ford.test.cpp
  - test/aoj/grl/scc.test.cpp
documentation_of: lib/graph/graph.hpp
layout: document
redirect_from:
- /library/lib/graph/graph.hpp
- /library/lib/graph/graph.hpp.html
title: lib/graph/graph.hpp
---
