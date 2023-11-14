---
data:
  _extendedDependsOn:
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/warshall_floyd.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_1_C\"\n#include\
    \ \"graph/warshall_floyd.hpp\"\n#include <cstdint>\n#include <iostream>\n#include\
    \ <string>\n#include \"graph/matrix_graph.hpp\"\n\nint main(void) {\n    int v,\
    \ e;\n    std::cin >> v >> e;\n    matrix_graph<std::int64_t> g(v, INF);\n   \
    \ while (e--) {\n        int s, t, d;\n        std::cin >> s >> t >> d;\n    \
    \    g.add_edge(s, t, d);\n    }\n    warshall_floyd(g);\n    for (int i = 0;\
    \ i < v; ++i) {\n        if (g[i][i] < 0) {\n            std::cout << \"NEGATIVE\
    \ CYCLE\" << std::endl;\n            return 0;\n        }\n    }\n\n    for (int\
    \ i = 0; i < v; ++i) {\n        for (int j = 0; j < v; ++j) {\n            if\
    \ (g[i][j] >= INF / 2) std::cout << \"INF\";\n            else std::cout << g[i][j];\n\
    \            if (j == v - 1) std::cout << std::endl;\n            else std::cout\
    \ << ' ';\n        }\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/graph/warshall_floyd.hpp
  - lib/graph/matrix_graph.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/aoj/grl/warshall_floyd.test.cpp
  requiredBy: []
  timestamp: '2023-11-14 17:51:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/grl/warshall_floyd.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/grl/warshall_floyd.test.cpp
- /verify/test/aoj/grl/warshall_floyd.test.cpp.html
title: test/aoj/grl/warshall_floyd.test.cpp
---
