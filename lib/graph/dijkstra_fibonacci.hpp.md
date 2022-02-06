---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/fibonacci_heap.hpp
    title: lib/data_structure/fibonacci_heap.hpp
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: lib/graph/graph.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/dijkstra_fibonacci.test.cpp
    title: test/aoj/grl/dijkstra_fibonacci.test.cpp
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
  code: "#include \"template/template.hpp\"\n#include \"graph/graph.hpp\"\n#include\
    \ \"data_structure/fibonacci_heap.hpp\"\n\ntemplate <class T>\nstd::vector<T>\
    \ dijkstra(const Graph<T> &g, int s = 0, T inf = std::numeric_limits<T>::max())\
    \ {\n    struct _edge {\n        int to;\n        T dist;\n        constexpr _edge()\
    \ : to(), dist() {}\n        constexpr _edge(int _to, T _dist) : to(_to), dist(_dist)\
    \ {}\n        bool operator<(const _edge &rhs) const {\n            return this->dist\
    \ < rhs.dist;\n        }\n        bool operator>(const _edge &rhs) const {\n \
    \           return rhs < *this;\n        }\n    };\n    std::vector<T> dists(g.size(),\
    \ inf);\n    using f_heap = fibonacci_heap<int, T, greater<>>;\n    std::vector<typename\
    \ f_heap::node_pointer> nodes(g.size());\n    f_heap heap;\n    dists[s] = T();\n\
    \    heap.push(s, T());\n    while (!heap.empty()) {\n        auto [to, dist]\
    \ = heap.top();\n        heap.pop();\n        if (dists[to] < dist)\n        \
    \    continue;\n        for (auto &i : g[to]) {\n            if (chmin(dists[i.to],\
    \ dist + i.dist)) {\n                if (nodes[i.to])\n                    heap.update(nodes[i.to],\
    \ dist + i.dist);\n                else\n                    nodes[i.to] = heap.push(i.to,\
    \ dist + i.dist);\n            }\n        }\n    }\n    return dists;\n}\n"
  dependsOn:
  - lib/template/template.hpp
  - lib/graph/graph.hpp
  - lib/data_structure/fibonacci_heap.hpp
  isVerificationFile: false
  path: lib/graph/dijkstra_fibonacci.hpp
  requiredBy: []
  timestamp: '2022-02-06 20:20:01+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/dijkstra_fibonacci.test.cpp
documentation_of: lib/graph/dijkstra_fibonacci.hpp
layout: document
redirect_from:
- /library/lib/graph/dijkstra_fibonacci.hpp
- /library/lib/graph/dijkstra_fibonacci.hpp.html
title: lib/graph/dijkstra_fibonacci.hpp
---
