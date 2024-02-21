---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':heavy_check_mark:'
    path: lib/graph/scc.hpp
    title: "\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3"
  - icon: ':heavy_check_mark:'
    path: lib/graph/two_sat.hpp
    title: 2-SAT
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
    PROBLEM: https://judge.yosupo.jp/problem/two_sat
    links:
    - https://judge.yosupo.jp/problem/two_sat
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/two_sat.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/two_sat\"\n#include \"\
    graph/two_sat.hpp\"\n#include <iostream>\n#include <string>\n\nint main(void)\
    \ {\n    std::string tmp;\n    int n, m;\n    std::cin >> tmp >> tmp >> n >> m;\n\
    \    two_sat ts(n);\n    while (m--) {\n        int a, b, c;\n        std::cin\
    \ >> a >> b >> c;\n        bool f = true, g = true;\n        if (a < 0) a = -a,\
    \ f = false;\n        if (b < 0) b = -b, g = false;\n        ts.add(a - 1, f,\
    \ b - 1, g);\n    }\n    auto v = ts.solve();\n    if (!ts.is_satisfy(v)) {\n\
    \        std::cout << \"s UNSATISFIABLE\\n\";\n        return 0;\n    }\n    std::cout\
    \ << \"s SATISFIABLE\\n\";\n    auto u = ts.build(v);\n    std::vector<int> ans(n);\n\
    \    for (int i = 0; i < n; ++i) ans[i] = (u[i] ? i + 1 : -i - 1);\n    std::cout\
    \ << \"v \";\n    for (auto &&e : ans) std::cout << e << ' ';\n    std::cout <<\
    \ 0 << '\\n';\n\n    return 0;\n}\n"
  dependsOn:
  - lib/graph/two_sat.hpp
  - lib/graph/graph.hpp
  - lib/graph/scc.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/yosupo/math/two_sat.test.cpp
  requiredBy: []
  timestamp: '2024-01-10 03:54:57+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/math/two_sat.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/math/two_sat.test.cpp
- /verify/test/yosupo/math/two_sat.test.cpp.html
title: test/yosupo/math/two_sat.test.cpp
---
