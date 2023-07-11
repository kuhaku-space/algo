---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/graph/graph.hpp
    title: "\u91CD\u307F\u4ED8\u304D\u30B0\u30E9\u30D5"
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_math.hpp
    title: lib/internal/internal_math.hpp
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_type_traits.hpp
    title: lib/internal/internal_type_traits.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: lib/math/modint.hpp
  - icon: ':heavy_check_mark:'
    path: lib/string/aho_corasick.hpp
    title: "Aho Corasick \u6CD5"
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Regional/2863?year=2017
    links:
    - https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Regional/2863?year=2017
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: string/aho_corasick.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/challenges/sources/JAG/Regional/2863?year=2017\"\
    \n#include \"string/aho_corasick.hpp\"\n#include \"math/modint.hpp\"\n#include\
    \ \"template/atcoder.hpp\"\n#include \"tree/tree_function.hpp\"\n\nusing Mint\
    \ = modint107;\n\nint main(void) {\n    int m;\n    cin >> m;\n    vector<string>\
    \ t(m);\n    cin >> t;\n    aho_corasick<26, 'a'> aho;\n    vector<vector<int>>\
    \ correct;\n    rep (i, m) {\n        auto v = aho.insert(t[i]);\n        correct.resize(aho.size());\n\
    \        correct[v.back()].emplace_back(i);\n    }\n    auto failure = aho.build();\n\
    \    auto bfs = tree_bfs(failure);\n    for (auto x : bfs) {\n        int y =\
    \ failure[x];\n        vector<int> v;\n        set_union(correct[x].begin(), correct[x].end(),\
    \ correct[y].begin(), correct[y].end(),\n                  back_inserter(v));\n\
    \        correct[x] = v;\n    }\n    string s;\n    cin >> s;\n    int n = s.size();\n\
    \    auto res = aho.search(s);\n    vector<Mint> dp(n + 1);\n    dp[0] = 1;\n\
    \    rep (i, n + 1) {\n        for (auto y : correct[res[i]]) {\n            dp[i]\
    \ += dp[i - t[y].size()];\n        }\n    }\n    co(dp[n]);\n\n    return 0;\n\
    }\n"
  dependsOn:
  - lib/string/aho_corasick.hpp
  - lib/template/template.hpp
  - lib/math/modint.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  - lib/tree/tree_function.hpp
  - lib/graph/graph.hpp
  isVerificationFile: true
  path: test/aoj/jag/aho_corasick.test.cpp
  requiredBy: []
  timestamp: '2023-05-24 16:19:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/jag/aho_corasick.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/jag/aho_corasick.test.cpp
- /verify/test/aoj/jag/aho_corasick.test.cpp.html
title: test/aoj/jag/aho_corasick.test.cpp
---
