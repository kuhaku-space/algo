---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/BIT.hpp
    title: "\u30D5\u30A7\u30CB\u30C3\u30AF\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/BIT_RAQ.hpp
    title: "\u30D5\u30A7\u30CB\u30C3\u30AF\u6728\uFF08\u533A\u9593\u52A0\u7B97\u3001\
      \u533A\u9593\u7DCF\u548C\uFF09"
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
    path: lib/tree/hld.hpp
    title: HLD
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/5/GRL_5_E
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/5/GRL_5_E
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: binary_tree/BIT_RAQ.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/5/GRL_5_E\"\
    \n#include \"binary_tree/BIT_RAQ.hpp\"\n#include \"template/atcoder.hpp\"\n#include\
    \ \"tree/hld.hpp\"\n\nint main(void) {\n    int n;\n    cin >> n;\n    BIT_RAQ<ll>\
    \ bit(n);\n    HLD hld(n);\n    rep (i, n) {\n        int k;\n        cin >> k;\n\
    \        rep (j, k) {\n            int c;\n            cin >> c;\n           \
    \ hld.add_edge(i, c);\n        }\n    }\n    hld.build();\n\n    int q;\n    cin\
    \ >> q;\n    rep (i, q) {\n        int id;\n        cin >> id;\n        if (id\
    \ == 0) {\n            int v, w;\n            cin >> v >> w;\n            auto\
    \ f = [&](int a, int b) {\n                bit.add(a, b, w);\n            };\n\
    \            hld.for_each_edge(0, v, f);\n        } else {\n            int v;\n\
    \            cin >> v;\n            ll ans = 0;\n            auto f = [&](int\
    \ a, int b) {\n                ans += bit.sum(a, b);\n            };\n       \
    \     hld.for_each_edge(0, v, f);\n            co(ans);\n        }\n    }\n\n\
    \    return 0;\n}\n"
  dependsOn:
  - lib/binary_tree/BIT_RAQ.hpp
  - lib/binary_tree/BIT.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  - lib/tree/hld.hpp
  isVerificationFile: true
  path: test/aoj/grl/range_query_on_tree_2.test.cpp
  requiredBy: []
  timestamp: '2022-07-13 04:24:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/grl/range_query_on_tree_2.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/grl/range_query_on_tree_2.test.cpp
- /verify/test/aoj/grl/range_query_on_tree_2.test.cpp.html
title: test/aoj/grl/range_query_on_tree_2.test.cpp
---
