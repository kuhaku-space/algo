---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/flow/hopcroft_karp.hpp
    title: lib/flow/hopcroft_karp.hpp
  - icon: ':heavy_check_mark:'
    path: lib/graph/matrix_graph.hpp
    title: "\u96A3\u63A5\u884C\u5217"
  - icon: ':heavy_check_mark:'
    path: lib/graph/warshall_floyd.hpp
    title: lib/graph/warshall_floyd.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/2251
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/2251
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: flow/hopcroft_karp.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/2251\"\n#include\
    \ \"flow/hopcroft_karp.hpp\"\n#include <algorithm>\n#include <iostream>\n#include\
    \ \"graph/matrix_graph.hpp\"\n#include \"graph/warshall_floyd.hpp\"\n\nint main(void)\
    \ {\n    while (true) {\n        int n, m, l;\n        std::cin >> n >> m >> l;\n\
    \        if (!n) break;\n        matrix_graph<int> g(n, Inf);\n        while (m--)\
    \ {\n            int u, v, w;\n            std::cin >> u >> v >> w;\n        \
    \    g.add_edges(u, v, w);\n        }\n        warshall_floyd(g);\n        std::vector<std::pair<int,\
    \ int>> q(l);\n        for (auto &[a, b] : q) std::cin >> a >> b;\n        std::sort(q.begin(),\
    \ q.end(), [](auto l, auto r) { return l.second < r.second; });\n        hopcroft_karp\
    \ hk(l, l);\n        for (int i = 0; i < l; ++i) {\n            auto [a, b] =\
    \ q[i];\n            for (int j = i + 1; j < l; ++j) {\n                auto [c,\
    \ d] = q[j];\n                if (b + g[a][c] <= d) hk.add_edge(i, j);\n     \
    \       }\n        }\n        std::cout << l - hk.matching() << std::endl;\n \
    \   }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/flow/hopcroft_karp.hpp
  - lib/template/template.hpp
  - lib/graph/matrix_graph.hpp
  - lib/graph/warshall_floyd.hpp
  isVerificationFile: true
  path: test/aoj/jag/hopcroft_karp.test.cpp
  requiredBy: []
  timestamp: '2023-11-15 01:07:11+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/jag/hopcroft_karp.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/jag/hopcroft_karp.test.cpp
- /verify/test/aoj/jag/hopcroft_karp.test.cpp.html
title: test/aoj/jag/hopcroft_karp.test.cpp
---
