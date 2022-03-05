---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/graph/graph.hpp
    title: lib/graph/graph.hpp
  - icon: ':x:'
    path: lib/graph/topological_sort.hpp
    title: "\u9589\u8DEF\u691C\u51FA"
  - icon: ':question:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/topological_sort.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_C\"\
    \n#include \"graph/topological_sort.hpp\"\n#include \"template/atcoder.hpp\"\n\
    \nint main(void) {\n    sonic();\n    int n, m;\n    cin >> n >> m;\n    Graph<void>\
    \ g(n);\n    g.input_edge(m, true);\n\n    co(has_cycle(g));\n\n    return 0;\n\
    }\n"
  dependsOn:
  - lib/graph/topological_sort.hpp
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  isVerificationFile: true
  path: test/aoj/grl/cycle.test.cpp
  requiredBy: []
  timestamp: '2022-03-05 12:54:03+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/aoj/grl/cycle.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/grl/cycle.test.cpp
- /verify/test/aoj/grl/cycle.test.cpp.html
title: test/aoj/grl/cycle.test.cpp
---
