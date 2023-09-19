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
    PROBLEM: https://judge.yosupo.jp/problem/scc
    links:
    - https://judge.yosupo.jp/problem/scc
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: graph/scc.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/scc\"\n#include \"graph/scc.hpp\"\
    \n#include \"template/atcoder.hpp\"\n\nint main(void) {\n    int n, m;\n    std::cin\
    \ >> n >> m;\n    Graph<void> g(n);\n    g.input_edge(m, 0);\n    auto v = scc(g);\n\
    \    std::vector<std::vector<int>> ans(*max_element(v.begin(), v.end()) + 1);\n\
    \    rep (i, n) ans[v[i]].emplace_back(i);\n    co(ans.size());\n    for (auto\
    \ &&u : ans) {\n        co(u.size(), u);\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/graph/scc.hpp
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/yosupo/graph/strongly_connected_components.test.cpp
  requiredBy: []
  timestamp: '2023-09-11 18:21:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/graph/strongly_connected_components.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/graph/strongly_connected_components.test.cpp
- /verify/test/yosupo/graph/strongly_connected_components.test.cpp.html
title: test/yosupo/graph/strongly_connected_components.test.cpp
---
