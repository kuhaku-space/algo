---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/flow/min_cost_flow.hpp
    title: "\u6700\u5C0F\u8CBB\u7528\u6D41"
  - icon: ':heavy_check_mark:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/macro.hpp
    title: lib/template/macro.hpp
  - icon: ':heavy_check_mark:'
    path: lib/template/sonic.hpp
    title: lib/template/sonic.hpp
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_B
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: flow/min_cost_flow.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/6/GRL_6_B\"\
    \n#include \"flow/min_cost_flow.hpp\"\n#include \"template/atcoder.hpp\"\n\nint\
    \ main(void) {\n    sonic();\n    int n, m, f;\n    cin >> n >> m >> f;\n\n  \
    \  mcf_graph<int, int> mf(n);\n    rep(i, m) {\n        int a, b, c, d;\n    \
    \    cin >> a >> b >> c >> d;\n        mf.add_edge(a, b, c, d);\n    }\n\n   \
    \ auto ans = mf.flow(0, n - 1, f);\n    if (ans.first == f)\n        co(ans.second);\n\
    \    else\n        co(-1);\n\n    return 0;\n}\n"
  dependsOn:
  - lib/flow/min_cost_flow.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/aoj/grl/min_cost_flow.test.cpp
  requiredBy: []
  timestamp: '2022-07-16 07:44:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/grl/min_cost_flow.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/grl/min_cost_flow.test.cpp
- /verify/test/aoj/grl/min_cost_flow.test.cpp.html
title: test/aoj/grl/min_cost_flow.test.cpp
---
