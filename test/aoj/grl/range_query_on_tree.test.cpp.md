---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/fenwick_tree.hpp
    title: "\u30D5\u30A7\u30CB\u30C3\u30AF\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  - icon: ':heavy_check_mark:'
    path: lib/tree/hld.hpp
    title: "HL\u5206\u89E3"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_D
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_D
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: binary_tree/fenwick_tree.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_D\"\n#include\
    \ <cstdint>\n#include <iostream>\n#include \"binary_tree/fenwick_tree.hpp\"\n\
    #include \"tree/hld.hpp\"\n\nint main(void) {\n    int n;\n    std::cin >> n;\n\
    \    Graph<void> g(n);\n    for (int i = 0; i < n; ++i) {\n        int k;\n  \
    \      std::cin >> k;\n        while (k--) {\n            int c;\n           \
    \ std::cin >> c;\n            g.add_edges(i, c);\n        }\n    }\n\n    heavy_light_decomposition\
    \ hld(g);\n    fenwick_tree<std::int64_t> ft(n);\n    int q;\n    std::cin >>\
    \ q;\n    while (q--) {\n        int id;\n        std::cin >> id;\n        if\
    \ (id == 0) {\n            int v, w;\n            std::cin >> v >> w;\n      \
    \      auto f = [&](int a, int b) { ft.add(a, w); };\n            hld.for_each_edge(hld.get_parent(v),\
    \ v, f);\n        } else {\n            int v;\n            std::cin >> v;\n \
    \           std::int64_t ans = 0;\n            auto f = [&](int a, int b) { ans\
    \ += ft.sum(a, b); };\n            hld.for_each_edge(0, v, f);\n            std::cout\
    \ << ans << std::endl;\n        }\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/binary_tree/fenwick_tree.hpp
  - lib/tree/hld.hpp
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/aoj/grl/range_query_on_tree.test.cpp
  requiredBy: []
  timestamp: '2023-11-16 21:07:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/grl/range_query_on_tree.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/grl/range_query_on_tree.test.cpp
- /verify/test/aoj/grl/range_query_on_tree.test.cpp.html
title: test/aoj/grl/range_query_on_tree.test.cpp
---
