---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/flow/hopcroft_karp.hpp
    title: Hopcroft-Karp algorithm
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/GRL_7_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_7_A
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: flow/hopcroft_karp.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_7_A\"\n#include\
    \ <iostream>\n#include \"flow/hopcroft_karp.hpp\"\n\nint main(void) {\n    int\
    \ l, r, m;\n    std::cin >> l >> r >> m;\n    hopcroft_karp g(l, r);\n    while\
    \ (m--) {\n        int u, v;\n        std::cin >> u >> v;\n        g.add_edge(u,\
    \ v);\n    }\n    std::cout << g.matching() << std::endl;\n\n    return 0;\n}\n"
  dependsOn:
  - lib/flow/hopcroft_karp.hpp
  isVerificationFile: true
  path: test/aoj/grl/bipartite_matching.2.test.cpp
  requiredBy: []
  timestamp: '2023-12-09 13:20:54+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/grl/bipartite_matching.2.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/grl/bipartite_matching.2.test.cpp
- /verify/test/aoj/grl/bipartite_matching.2.test.cpp.html
title: test/aoj/grl/bipartite_matching.2.test.cpp
---
