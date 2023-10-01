---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
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
  - icon: ':heavy_check_mark:'
    path: lib/tree/tree_function.hpp
    title: "\u6728\u306E\u8DDD\u96E2\u3092\u6C42\u3081\u308B"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/tree_diameter
    links:
    - https://judge.yosupo.jp/problem/tree_diameter
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/atcoder.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/tree_diameter\"\n#include\
    \ \"template/atcoder.hpp\"\n#include \"tree/tree_function.hpp\"\n\nint main(void)\
    \ {\n    int n;\n    cin >> n;\n    Graph<int> g(n);\n    g.input_edges(n - 1,\
    \ 0);\n    auto d = tree_dist<int, ll>(g, 0);\n    int st = max_element(all(d))\
    \ - d.begin();\n    d = tree_dist<int, ll>(g, st);\n    auto p = tree_parent(g,\
    \ st);\n    int gl = max_element(all(d)) - d.begin();\n    vector<int> ans;\n\
    \    while (gl != -1) {\n        ans.emplace_back(gl);\n        gl = p[gl];\n\
    \    }\n    co(*max_element(all(d)), ans.size());\n    co(ans);\n\n    return\
    \ 0;\n}\n"
  dependsOn:
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/template.hpp
  - lib/template/sonic.hpp
  - lib/tree/tree_function.hpp
  - lib/graph/graph.hpp
  isVerificationFile: true
  path: test/yosupo/tree/tree_diameter.test.cpp
  requiredBy: []
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/tree/tree_diameter.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/tree/tree_diameter.test.cpp
- /verify/test/yosupo/tree/tree_diameter.test.cpp.html
title: test/yosupo/tree/tree_diameter.test.cpp
---
