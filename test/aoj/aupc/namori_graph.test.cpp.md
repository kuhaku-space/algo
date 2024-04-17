---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':heavy_check_mark:'
    path: lib/graph/namori_graph.hpp
    title: lib/graph/namori_graph.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/2891
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/2891
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/namori_graph.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/2891\"\n\n#include\
    \ \"graph/namori_graph.hpp\"\n#include <iostream>\n#include \"graph/graph.hpp\"\
    \n\nint main(void) {\n    int n;\n    std::cin >> n;\n    Graph<void> g(n);\n\
    \    g.input_edges(n);\n    auto parent = cycle_detection_on_namori_graph(g);\n\
    \n    int q;\n    std::cin >> q;\n    while (q--) {\n        int a, b;\n     \
    \   std::cin >> a >> b;\n        std::cout << (parent[a - 1] == -1 && parent[b\
    \ - 1] == -1 ? 2 : 1) << '\\n';\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/graph/namori_graph.hpp
  - lib/graph/graph.hpp
  isVerificationFile: true
  path: test/aoj/aupc/namori_graph.test.cpp
  requiredBy: []
  timestamp: '2024-04-17 13:11:30+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/aupc/namori_graph.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/aupc/namori_graph.test.cpp
- /verify/test/aoj/aupc/namori_graph.test.cpp.html
title: test/aoj/aupc/namori_graph.test.cpp
---
