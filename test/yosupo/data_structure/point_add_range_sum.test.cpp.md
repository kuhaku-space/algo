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
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: binary_tree/fenwick_tree.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    #include \"binary_tree/fenwick_tree.hpp\"\n#include \"template/atcoder.hpp\"\n\
    \nint main(void) {\n    sonic();\n    int n, q;\n    cin >> n >> q;\n    vector<int>\
    \ a(n);\n    cin >> a;\n    fenwick_tree<ll> ft(a);\n    while (q--) {\n     \
    \   int x, y, z;\n        cin >> x >> y >> z;\n        if (x == 0)\n         \
    \   ft.add(y, z);\n        else\n            co(ft.sum(y, z));\n    }\n\n    return\
    \ 0;\n}\n"
  dependsOn:
  - lib/binary_tree/fenwick_tree.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/point_add_range_sum.test.cpp
  requiredBy: []
  timestamp: '2023-05-22 19:46:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/point_add_range_sum.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/point_add_range_sum.test.cpp
- /verify/test/yosupo/data_structure/point_add_range_sum.test.cpp.html
title: test/yosupo/data_structure/point_add_range_sum.test.cpp
---
