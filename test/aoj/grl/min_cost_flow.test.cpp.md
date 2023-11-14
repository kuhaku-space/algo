---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/flow/min_cost_flow.hpp
    title: "\u6700\u5C0F\u8CBB\u7528\u6D41"
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_B
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: flow/min_cost_flow.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/GRL_6_B\"\n#include\
    \ \"flow/min_cost_flow.hpp\"\n#include <iostream>\n\nint main(void) {\n    int\
    \ n, m, f;\n    std::cin >> n >> m >> f;\n\n    mcf_graph<int, int> mf(n);\n \
    \   for (int i = 0; i < m; ++i) {\n        int a, b, c, d;\n        std::cin >>\
    \ a >> b >> c >> d;\n        mf.add_edge(a, b, c, d);\n    }\n    auto ans = mf.flow(0,\
    \ n - 1, f);\n    std::cout << (ans.first == f ? ans.second : -1) << std::endl;\n\
    \n    return 0;\n}\n"
  dependsOn:
  - lib/flow/min_cost_flow.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/aoj/grl/min_cost_flow.test.cpp
  requiredBy: []
  timestamp: '2023-11-14 17:51:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/grl/min_cost_flow.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/grl/min_cost_flow.test.cpp
- /verify/test/aoj/grl/min_cost_flow.test.cpp.html
title: test/aoj/grl/min_cost_flow.test.cpp
---
