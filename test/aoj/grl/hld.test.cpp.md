---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  - icon: ':heavy_check_mark:'
    path: lib/tree/hld.hpp
    title: HLD
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/atcoder.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_5_C\"\
    \n#include \"template/atcoder.hpp\"\n#include \"tree/hld.hpp\"\n\nint main(void)\
    \ {\n    sonic();\n    int n;\n    cin >> n;\n    HLD hld(n);\n    rep(i, n) {\n\
    \        int k;\n        cin >> k;\n        rep(j, k) {\n            int c;\n\
    \            cin >> c;\n            hld.add_edge(i, c);\n        }\n    }\n\n\
    \    hld.build();\n\n    int q;\n    cin >> q;\n    while (q--) {\n        int\
    \ u, v;\n        cin >> u >> v;\n        co(hld.lca(u, v));\n    }\n\n    return\
    \ 0;\n}\n"
  dependsOn:
  - lib/template/atcoder.hpp
  - lib/template/template.hpp
  - lib/tree/hld.hpp
  isVerificationFile: true
  path: test/aoj/grl/hld.test.cpp
  requiredBy: []
  timestamp: '2022-02-08 12:58:02+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/grl/hld.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/grl/hld.test.cpp
- /verify/test/aoj/grl/hld.test.cpp.html
title: test/aoj/grl/hld.test.cpp
---
