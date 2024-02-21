---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':heavy_check_mark:'
    path: lib/graph/lowlink.hpp
    title: LowLink
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_A
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/lowlink.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_3_A\"\n#include\
    \ <algorithm>\n#include <iostream>\n#include <vector>\n#include \"graph/lowlink.hpp\"\
    \n\nint main(void) {\n    int n, m;\n    std::cin >> n >> m;\n    Graph<void>\
    \ g(n);\n    g.input_edges(m, 0);\n\n    LowLink llink(g);\n    auto ans = llink.get_articulation_points();\n\
    \    std::sort(ans.begin(), ans.end());\n    for (auto e : ans) std::cout << e\
    \ << std::endl;\n\n    return 0;\n}\n"
  dependsOn:
  - lib/graph/lowlink.hpp
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/aoj/grl/articulation_points.test.cpp
  requiredBy: []
  timestamp: '2023-11-14 17:51:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/grl/articulation_points.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/grl/articulation_points.test.cpp
- /verify/test/aoj/grl/articulation_points.test.cpp.html
title: test/aoj/grl/articulation_points.test.cpp
---
