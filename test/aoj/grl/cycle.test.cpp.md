---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/cycle.hpp
    title: "\u9589\u8DEF\u691C\u51FA"
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_A
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/cycle.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_4_A\"\n#include\
    \ \"graph/cycle.hpp\"\n#include <iostream>\n\nint main(void) {\n    int n, m;\n\
    \    std::cin >> n >> m;\n    Graph<void> g(n);\n    g.input_edge(m, 0);\n   \
    \ std::cout << has_cycle(g) << std::endl;\n\n    return 0;\n}\n"
  dependsOn:
  - lib/graph/cycle.hpp
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/aoj/grl/cycle.test.cpp
  requiredBy: []
  timestamp: '2023-11-14 17:51:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/grl/cycle.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/grl/cycle.test.cpp
- /verify/test/aoj/grl/cycle.test.cpp.html
title: test/aoj/grl/cycle.test.cpp
---
