---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/fenwick_tree.hpp
    title: "\u30D5\u30A7\u30CB\u30C3\u30AF\u6728"
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/5/GRL_5_D
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/5/GRL_5_D
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.10/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: binary_tree/fenwick_tree.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/5/GRL_5_D\"\
    \n#include \"binary_tree/fenwick_tree.hpp\"\n#include \"template/atcoder.hpp\"\
    \n#include \"tree/hld.hpp\"\n\nint main(void) {\n    int n;\n    cin >> n;\n \
    \   fenwick_tree<ll> ft(n);\n    HLD hld(n);\n    rep (i, n) {\n        int k;\n\
    \        cin >> k;\n        rep (j, k) {\n            int c;\n            cin\
    \ >> c;\n            hld.add_edge(i, c);\n        }\n    }\n    hld.build();\n\
    \n    int q;\n    cin >> q;\n    while (q--) {\n        int id;\n        cin >>\
    \ id;\n        if (id == 0) {\n            int v, w;\n            cin >> v >>\
    \ w;\n            auto f = [&](int a, int b) {\n                ft.add(a, w);\n\
    \            };\n            hld.for_each_edge(hld.get_parent(v), v, f);\n   \
    \     } else {\n            int v;\n            cin >> v;\n            ll ans\
    \ = 0;\n            auto f = [&](int a, int b) {\n                ans += ft.sum(a,\
    \ b);\n            };\n            hld.for_each_edge(0, v, f);\n            co(ans);\n\
    \        }\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/binary_tree/fenwick_tree.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  - lib/tree/hld.hpp
  isVerificationFile: true
  path: test/aoj/grl/range_query_on_tree.test.cpp
  requiredBy: []
  timestamp: '2022-07-31 09:58:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/grl/range_query_on_tree.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/grl/range_query_on_tree.test.cpp
- /verify/test/aoj/grl/range_query_on_tree.test.cpp.html
title: test/aoj/grl/range_query_on_tree.test.cpp
---
