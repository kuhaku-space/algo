---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: lib/graph/graph.hpp
  - icon: ':heavy_check_mark:'
    path: lib/heap/binary_heap.hpp
    title: "\u4E8C\u5206\u30D2\u30FC\u30D7"
  - icon: ':heavy_check_mark:'
    path: lib/heap/fibonacci_heap.hpp
    title: "\u30D5\u30A3\u30DC\u30CA\u30C3\u30C1\u30D2\u30FC\u30D7"
  - icon: ':heavy_check_mark:'
    path: lib/heap/radix_heap.hpp
    title: lib/heap/radix_heap.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/dijkstra_binary.test.cpp
    title: test/aoj/grl/dijkstra_binary.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/dijkstra_fibonacci.test.cpp
    title: test/aoj/grl/dijkstra_fibonacci.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/dijkstra_radix.test.cpp
    title: test/aoj/grl/dijkstra_radix.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30C0\u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5\uFF08\u30D2\u30FC\u30D7\
      \uFF09"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: heap/binary_heap.hpp:\
    \ line -1: no such header\n"
  code: "#include \"heap/binary_heap.hpp\"\n#include \"heap/fibonacci_heap.hpp\"\n\
    #include \"heap/radix_heap.hpp\"\n#include \"graph/graph.hpp\"\n#include \"template/template.hpp\"\
    \n\ntemplate <class T>\nusing b_heap = binary_heap<int, T, std::greater<>>;\n\
    template <class T>\nusing f_heap = fibonacci_heap<int, T, std::greater<>>;\ntemplate\
    \ <class T>\nusing r_heap = radix_heap<int, T>;\n\n/**\n * @brief \u30C0\u30A4\
    \u30AF\u30B9\u30C8\u30E9\u6CD5\uFF08\u30D2\u30FC\u30D7\uFF09\n *\n * @tparam T\n\
    \ * @param g \u30B0\u30E9\u30D5\n * @param s \u59CB\u70B9\n * @param inf \u6B63\
    \u306E\u7121\u9650\u8868\u73FE\n * @retval std::vector<T> \u5404\u9802\u70B9\u307E\
    \u3067\u306E\u6700\u77ED\u8DDD\u96E2\n */\ntemplate <class T, class Heap>\nstd::vector<T>\
    \ dijkstra(const Graph<T> &g, int s = 0, T inf = std::numeric_limits<T>::max())\
    \ {\n    Heap heap;\n    std::vector<typename Heap::node_pointer> nodes(g.size());\n\
    \    std::vector<T> dists(g.size(), inf);\n    dists[s] = T();\n    heap.emplace(s,\
    \ T());\n    while (!heap.empty()) {\n        auto [to, dist] = heap.top();\n\
    \        heap.pop();\n        if (dists[to] < dist) continue;\n        for (auto\
    \ &e : g[to]) {\n            if (chmin(dists[e.to], dist + e.dist)) {\n      \
    \          if (!nodes[e.to])\n                    nodes[e.to] = heap.push(e.to,\
    \ dist + e.dist);\n                else\n                    heap.update(nodes[e.to],\
    \ dist + e.dist);\n            }\n        }\n    }\n    return dists;\n}\n"
  dependsOn:
  - lib/heap/binary_heap.hpp
  - lib/template/template.hpp
  - lib/heap/fibonacci_heap.hpp
  - lib/heap/radix_heap.hpp
  - lib/graph/graph.hpp
  isVerificationFile: false
  path: lib/graph/dijkstra_heap.hpp
  requiredBy: []
  timestamp: '2022-03-20 18:02:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/dijkstra_binary.test.cpp
  - test/aoj/grl/dijkstra_fibonacci.test.cpp
  - test/aoj/grl/dijkstra_radix.test.cpp
documentation_of: lib/graph/dijkstra_heap.hpp
layout: document
redirect_from:
- /library/lib/graph/dijkstra_heap.hpp
- /library/lib/graph/dijkstra_heap.hpp.html
title: "\u30C0\u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5\uFF08\u30D2\u30FC\u30D7\uFF09"
---
