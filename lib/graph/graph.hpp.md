---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/_old/tree.hpp
    title: lib/_old/tree.hpp
  - icon: ':x:'
    path: lib/graph/bellman_ford.hpp
    title: "\u30D9\u30EB\u30DE\u30F3\u30D5\u30A9\u30FC\u30C9\u6CD5"
  - icon: ':warning:'
    path: lib/graph/cycle.hpp
    title: "\u9589\u8DEF\u691C\u51FA"
  - icon: ':x:'
    path: lib/graph/dijkstra.hpp
    title: "\u30C0\u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5"
  - icon: ':x:'
    path: lib/graph/dijkstra_heap.hpp
    title: "\u30C0\u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5\uFF08\u30D2\u30FC\u30D7\uFF09"
  - icon: ':warning:'
    path: lib/graph/dijkstra_potential.hpp
    title: lib/graph/dijkstra_potential.hpp
  - icon: ':x:'
    path: lib/graph/kruskal.hpp
    title: "\u30AF\u30E9\u30B9\u30AB\u30EB\u6CD5"
  - icon: ':x:'
    path: lib/graph/lowlink.hpp
    title: LowLink
  - icon: ':x:'
    path: lib/graph/prim.hpp
    title: "\u30D7\u30EA\u30E0\u6CD5"
  - icon: ':x:'
    path: lib/graph/scc.hpp
    title: "\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3"
  - icon: ':warning:'
    path: lib/graph/spanning_tree.hpp
    title: "\u5168\u57DF\u6728"
  - icon: ':x:'
    path: lib/graph/topological_sort.hpp
    title: "\u30C8\u30DD\u30ED\u30B8\u30AB\u30EB\u30BD\u30FC\u30C8"
  - icon: ':warning:'
    path: lib/graph/two_sat.hpp
    title: 2-SAT
  - icon: ':warning:'
    path: lib/tree/tree_dist.hpp
    title: "\u6728\u306E\u8DDD\u96E2\u3092\u6C42\u3081\u308B"
  - icon: ':warning:'
    path: lib/tree/tree_parent.hpp
    title: "\u6728\u306E\u9802\u70B9\u306E\u89AA\u3092\u6C42\u3081\u308B"
  - icon: ':warning:'
    path: lib/tree/tree_subtree.hpp
    title: "\u90E8\u5206\u6728\u306E\u5927\u304D\u3055\u3092\u6C42\u3081\u308B"
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aoj/grl/articulation_points.test.cpp
    title: test/aoj/grl/articulation_points.test.cpp
  - icon: ':x:'
    path: test/aoj/grl/bellman_ford.test.cpp
    title: test/aoj/grl/bellman_ford.test.cpp
  - icon: ':x:'
    path: test/aoj/grl/bridges.test.cpp
    title: test/aoj/grl/bridges.test.cpp
  - icon: ':x:'
    path: test/aoj/grl/cycle.test.cpp
    title: test/aoj/grl/cycle.test.cpp
  - icon: ':x:'
    path: test/aoj/grl/dijkstra.test.cpp
    title: test/aoj/grl/dijkstra.test.cpp
  - icon: ':x:'
    path: test/aoj/grl/dijkstra_binary.test.cpp
    title: test/aoj/grl/dijkstra_binary.test.cpp
  - icon: ':x:'
    path: test/aoj/grl/dijkstra_fibonacci.test.cpp
    title: test/aoj/grl/dijkstra_fibonacci.test.cpp
  - icon: ':x:'
    path: test/aoj/grl/dijkstra_radix.test.cpp
    title: test/aoj/grl/dijkstra_radix.test.cpp
  - icon: ':x:'
    path: test/aoj/grl/kruskal.test.cpp
    title: test/aoj/grl/kruskal.test.cpp
  - icon: ':x:'
    path: test/aoj/grl/prim.test.cpp
    title: test/aoj/grl/prim.test.cpp
  - icon: ':x:'
    path: test/aoj/grl/scc.test.cpp
    title: test/aoj/grl/scc.test.cpp
  - icon: ':x:'
    path: test/aoj/grl/topological_sort.test.cpp
    title: test/aoj/grl/topological_sort.test.cpp
  - icon: ':x:'
    path: test/yosupo/graph/shortest_path.test.cpp
    title: test/yosupo/graph/shortest_path.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
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
  code: "#pragma once\r\n#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief\
    \ \u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5\r\n * \r\n * @tparam T \u8FBA\u306E\
    \u91CD\u307F\u306E\u578B\r\n */\r\ntemplate <class T>\r\nstruct Graph {\r\n  private:\r\
    \n    struct _edge {\r\n        constexpr _edge() : _from(), _to(), _weight()\
    \ {}\r\n        constexpr _edge(int from, int to, T weight) : _from(from), _to(to),\
    \ _weight(weight) {}\r\n        bool operator<(const _edge &rhs) const { return\
    \ this->weight() < rhs.weight(); }\r\n        bool operator>(const _edge &rhs)\
    \ const { return rhs < *this; }\r\n\r\n        constexpr int from() const { return\
    \ this->_from; }\r\n        constexpr int to() const { return this->_to; }\r\n\
    \        constexpr T weight() const { return this->_weight; }\r\n\r\n      private:\r\
    \n        int _from, _to;\r\n        T _weight;\r\n    };\r\n\r\n  public:\r\n\
    \    using edge_type = typename Graph<T>::_edge;\r\n\r\n    Graph(int v) : _size(v),\
    \ edges(v) {}\r\n\r\n    const auto &operator[](int i) const { return this->edges[i];\
    \ }\r\n    auto &operator[](int i) { return this->edges[i]; }\r\n    const auto\
    \ begin() const { return this->edges.begin(); }\r\n    auto begin() { return this->edges.begin();\
    \ }\r\n    const auto end() const { return this->edges.end(); }\r\n    auto end()\
    \ { return this->edges.end(); }\r\n    constexpr int size() const { return this->_size;\
    \ }\r\n\r\n    void add_edge(const edge_type &e) { this->edges[e.from()].emplace_back(e);\
    \ }\r\n    void add_edge(int from, int to, T weight = T(1)) {\r\n        this->edges[from].emplace_back(from,\
    \ to, weight);\r\n    }\r\n    void add_edges(int from, int to, T weight = T(1))\
    \ {\r\n        this->edges[from].emplace_back(from, to, weight);\r\n        this->edges[to].emplace_back(to,\
    \ from, weight);\r\n    }\r\n\r\n    void input_edge(int m, int base = 1) {\r\n\
    \        for (int i = 0; i < m; ++i) {\r\n            int from, to;\r\n      \
    \      T weight;\r\n            cin >> from >> to >> weight;\r\n            this->add_edge(from\
    \ - base, to - base, weight);\r\n        }\r\n    }\r\n    void input_edges(int\
    \ m, int base = 1) {\r\n        for (int i = 0; i < m; ++i) {\r\n            int\
    \ from, to;\r\n            T weight;\r\n            cin >> from >> to >> weight;\r\
    \n            this->add_edges(from - base, to - base, weight);\r\n        }\r\n\
    \    }\r\n\r\n  private:\r\n    int _size;\r\n    std::vector<std::vector<edge_type>>\
    \ edges;\r\n};\r\n\r\ntemplate <>\r\nstruct Graph<void> {\r\n  private:\r\n  \
    \  struct _edge {\r\n        constexpr _edge() : _from(), _to() {}\r\n       \
    \ constexpr _edge(int from, int to) : _from(from), _to(to) {}\r\n\r\n        constexpr\
    \ int from() const { return this->_from; }\r\n        constexpr int to() const\
    \ { return this->_to; }\r\n        constexpr int weight() const { return 1; }\r\
    \n        bool operator<(const _edge &rhs) const { return false; }\r\n       \
    \ bool operator>(const _edge &rhs) const { return rhs < *this; }\r\n\r\n     \
    \ private:\r\n        int _from, _to;\r\n    };\r\n\r\n  public:\r\n    using\
    \ edge_type = typename Graph<void>::_edge;\r\n\r\n    Graph(int v) : _size(v),\
    \ edges(v) {}\r\n\r\n    const auto &operator[](int i) const { return this->edges[i];\
    \ }\r\n    auto &operator[](int i) { return this->edges[i]; }\r\n    const auto\
    \ begin() const { return this->edges.begin(); }\r\n    auto begin() { return this->edges.begin();\
    \ }\r\n    const auto end() const { return this->edges.end(); }\r\n    auto end()\
    \ { return this->edges.end(); }\r\n    constexpr int size() const { return this->_size;\
    \ }\r\n\r\n    void add_edge(const edge_type &e) { this->edges[e.from()].emplace_back(e);\
    \ }\r\n    void add_edge(int from, int to) { this->edges[from].emplace_back(from,\
    \ to); }\r\n    void add_edges(int from, int to) {\r\n        this->edges[from].emplace_back(from,\
    \ to);\r\n        this->edges[to].emplace_back(to, from);\r\n    }\r\n\r\n   \
    \ void input_edge(int m, int base = 1) {\r\n        for (int i = 0; i < m; ++i)\
    \ {\r\n            int from, to;\r\n            cin >> from >> to;\r\n       \
    \     this->add_edge(from - base, to - base);\r\n        }\r\n    }\r\n    void\
    \ input_edges(int m, int base = 1) {\r\n        for (int i = 0; i < m; ++i) {\r\
    \n            int from, to;\r\n            cin >> from >> to;\r\n            this->add_edges(from\
    \ - base, to - base);\r\n        }\r\n    }\r\n\r\n  private:\r\n    int _size;\r\
    \n    std::vector<std::vector<edge_type>> edges;\r\n};\r\n"
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
  - lib/graph/cycle.hpp
  - lib/graph/scc.hpp
  - lib/graph/dijkstra.hpp
  - lib/graph/bellman_ford.hpp
  timestamp: '2022-03-25 03:25:48+09:00'
  verificationStatus: LIBRARY_ALL_WA
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
title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
---
