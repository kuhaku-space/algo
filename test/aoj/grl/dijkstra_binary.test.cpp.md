---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: lib/graph/dijkstra_heap.hpp
    title: "\u30C0\u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5\uFF08\u30D2\u30FC\u30D7\uFF09"
  - icon: ':x:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':x:'
    path: lib/heap/binary_heap.hpp
    title: "\u4E8C\u5206\u30D2\u30FC\u30D7"
  - icon: ':x:'
    path: lib/heap/fibonacci_heap.hpp
    title: "\u30D5\u30A3\u30DC\u30CA\u30C3\u30C1\u30D2\u30FC\u30D7"
  - icon: ':x:'
    path: lib/heap/radix_heap.hpp
    title: lib/heap/radix_heap.hpp
  - icon: ':question:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_A
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/dijkstra_heap.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_A\"\
    \n#include \"graph/dijkstra_heap.hpp\"\n#include \"template/atcoder.hpp\"\n\n\
    int main(void) {\n    sonic();\n    int n, m, r;\n    cin >> n >> m >> r;\n  \
    \  Graph<int> g(n);\n    g.input_edge(m, true);\n\n    auto dist = dijkstra<int,\
    \ b_heap<int>>(g, r, Inf);\n    rep(i, n) {\n        if (dist[i] != Inf)\n   \
    \         co(dist[i]);\n        else\n            co(\"INF\");\n    }\n\n    return\
    \ 0;\n}\n"
  dependsOn:
  - lib/graph/dijkstra_heap.hpp
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  - lib/heap/binary_heap.hpp
  - lib/heap/fibonacci_heap.hpp
  - lib/heap/radix_heap.hpp
  - lib/template/atcoder.hpp
  isVerificationFile: true
  path: test/aoj/grl/dijkstra_binary.test.cpp
  requiredBy: []
  timestamp: '2022-03-24 17:46:31+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/aoj/grl/dijkstra_binary.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/grl/dijkstra_binary.test.cpp
- /verify/test/aoj/grl/dijkstra_binary.test.cpp.html
title: test/aoj/grl/dijkstra_binary.test.cpp
---
