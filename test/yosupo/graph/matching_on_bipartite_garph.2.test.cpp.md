---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/flow/hopcroft_karp.hpp
    title: lib/flow/hopcroft_karp.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/bipartitematching
    links:
    - https://judge.yosupo.jp/problem/bipartitematching
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: flow/hopcroft_karp.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\n#include\
    \ \"flow/hopcroft_karp.hpp\"\n#include \"template/atcoder.hpp\"\n\nint main(void)\
    \ {\n    int l, r, m;\n    cin >> l >> r >> m;\n    hopcroft_karp g(l, r);\n \
    \   while (m--) {\n        int u, v;\n        cin >> u >> v;\n        g.add_edge(u,\
    \ v);\n    }\n    co(g.matching());\n    for (auto p : g.get_pairs()) co(p.first,\
    \ p.second);\n\n    return 0;\n}\n"
  dependsOn:
  - lib/flow/hopcroft_karp.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/yosupo/graph/matching_on_bipartite_garph.2.test.cpp
  requiredBy: []
  timestamp: '2023-09-26 21:06:03+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/graph/matching_on_bipartite_garph.2.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/graph/matching_on_bipartite_garph.2.test.cpp
- /verify/test/yosupo/graph/matching_on_bipartite_garph.2.test.cpp.html
title: test/yosupo/graph/matching_on_bipartite_garph.2.test.cpp
---
