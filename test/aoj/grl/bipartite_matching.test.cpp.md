---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/flow/max_flow.hpp
    title: "\u6700\u5927\u6D41"
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/GRL_7_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_7_A
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: flow/max_flow.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_7_A\"\n#include\
    \ <iostream>\n#include \"flow/max_flow.hpp\"\n\nint main(void) {\n    int x, y,\
    \ e;\n    std::cin >> x >> y >> e;\n    mf_graph<int> mf(x + y + 2);\n    while\
    \ (e--) {\n        int s, t;\n        std::cin >> s >> t;\n        mf.add_edge(s,\
    \ x + t, 1);\n    }\n\n    int s = x + y, t = s + 1;\n    for (int i = 0; i <\
    \ x; ++i) mf.add_edge(s, i, 1);\n    for (int i = 0; i < y; ++i) mf.add_edge(x\
    \ + i, t, 1);\n    std::cout << mf.flow(s, t) << std::endl;\n\n    return 0;\n\
    }\n"
  dependsOn:
  - lib/flow/max_flow.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/aoj/grl/bipartite_matching.test.cpp
  requiredBy: []
  timestamp: '2023-11-14 17:51:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/grl/bipartite_matching.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/grl/bipartite_matching.test.cpp
- /verify/test/aoj/grl/bipartite_matching.test.cpp.html
title: test/aoj/grl/bipartite_matching.test.cpp
---
