---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/fibonacci_heap.hpp
    title: "\u30D5\u30A3\u30DC\u30CA\u30C3\u30C1\u30D2\u30FC\u30D7"
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
    document_title: "\u30C0\u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5\uFF08\u30D5\u30A3\u30DC\
      \u30CA\u30C3\u30C1\u30D2\u30FC\u30D7\uFF09"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: data_structure/fibonacci_heap.hpp:\
    \ line -1: no such header\n"
  code: "#include \"data_structure/fibonacci_heap.hpp\"\n#include \"graph/graph.hpp\"\
    \n#include \"template/template.hpp\"\n\n/**\n * @brief \u30C0\u30A4\u30AF\u30B9\
    \u30C8\u30E9\u6CD5\uFF08\u30D5\u30A3\u30DC\u30CA\u30C3\u30C1\u30D2\u30FC\u30D7\
    \uFF09\n *\n * @tparam T\n * @param g \u30B0\u30E9\u30D5\n * @param s \u59CB\u70B9\
    \n * @param inf \u6B63\u306E\u7121\u9650\u8868\u73FE\n * @retval std::vector<T>\
    \ \u5404\u9802\u70B9\u307E\u3067\u306E\u6700\u77ED\u8DDD\u96E2\n */\ntemplate\
    \ <class T>\nstd::vector<T> dijkstra(const Graph<T> &g, int s = 0, T inf = std::numeric_limits<T>::max())\
    \ {\n    std::vector<T> dists(g.size(), inf);\n    using f_heap = fibonacci_heap<int,\
    \ T, std::greater<>>;\n    f_heap heap;\n    std::vector<typename f_heap::node_pointer>\
    \ nodes(g.size());\n    dists[s] = T();\n    heap.push(s, T());\n    while (!heap.empty())\
    \ {\n        auto [to, dist] = heap.top();\n        heap.pop();\n        if (dists[to]\
    \ < dist) continue;\n        for (auto &i : g[to]) {\n            if (chmin(dists[i.to],\
    \ dist + i.dist)) {\n                if (nodes[i.to])\n                    heap.update(nodes[i.to],\
    \ dist + i.dist);\n                else\n                    nodes[i.to] = heap.push(i.to,\
    \ dist + i.dist);\n            }\n        }\n    }\n    return dists;\n}\n"
  dependsOn:
  - lib/data_structure/fibonacci_heap.hpp
  - lib/template/template.hpp
  - lib/graph/graph.hpp
  isVerificationFile: false
  path: lib/graph/dijkstra_fibonacci.hpp
  requiredBy: []
  timestamp: '2022-03-09 11:13:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/dijkstra_fibonacci.test.cpp
documentation_of: lib/graph/dijkstra_fibonacci.hpp
layout: document
redirect_from:
- /library/lib/graph/dijkstra_fibonacci.hpp
- /library/lib/graph/dijkstra_fibonacci.hpp.html
title: "\u30C0\u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5\uFF08\u30D5\u30A3\u30DC\u30CA\u30C3\
  \u30C1\u30D2\u30FC\u30D7\uFF09"
---
