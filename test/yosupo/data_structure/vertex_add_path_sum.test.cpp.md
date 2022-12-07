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
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_path_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_path_sum
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: binary_tree/fenwick_tree.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_path_sum\"\n\
    #include \"binary_tree/fenwick_tree.hpp\"\n#include \"template/atcoder.hpp\"\n\
    #include \"tree/hld.hpp\"\n\nint main(void) {\n    int n, q;\n    cin >> n >>\
    \ q;\n    vector<int> a(n);\n    cin >> a;\n    HLD hld(n);\n    hld.input_edges(0);\n\
    \    hld.build();\n    fenwick_tree<ll> ft(n);\n    rep (i, n) ft.add(hld.get(i),\
    \ a[i]);\n    while (q--) {\n        int c;\n        cin >> c;\n        if (c\
    \ == 0) {\n            int p, x;\n            cin >> p >> x;\n            ft.add(hld.get(p),\
    \ x);\n        } else {\n            int u, v;\n            cin >> u >> v;\n \
    \           ll ans = 0;\n            auto f = [&](int u, int v) {\n          \
    \      ans += ft.sum(u, v);\n            };\n            hld.for_each(u, v, f);\n\
    \            co(ans);\n        }\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/binary_tree/fenwick_tree.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  - lib/tree/hld.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/vertex_add_path_sum.test.cpp
  requiredBy: []
  timestamp: '2022-07-31 09:58:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/vertex_add_path_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/vertex_add_path_sum.test.cpp
- /verify/test/yosupo/data_structure/vertex_add_path_sum.test.cpp.html
title: test/yosupo/data_structure/vertex_add_path_sum.test.cpp
---
