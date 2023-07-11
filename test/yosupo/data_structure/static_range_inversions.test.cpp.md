---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/compress.hpp
    title: "\u5EA7\u6A19\u5727\u7E2E"
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/mo.hpp
    title: Mo's algorithm
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
    PROBLEM: https://judge.yosupo.jp/problem/static_range_inversions_query
    links:
    - https://judge.yosupo.jp/problem/static_range_inversions_query
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algorithm/compress.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n#include \"algorithm/compress.hpp\"\n#include \"algorithm/mo.hpp\"\n#include\
    \ \"binary_tree/fenwick_tree.hpp\"\n#include \"template/atcoder.hpp\"\n\nint main(void)\
    \ {\n    int n, q;\n    cin >> n >> q;\n    vector<int> a(n);\n    cin >> a;\n\
    \    a = compress(a);\n    ll sum = 0;\n    int size = *max_element(all(a)) +\
    \ 1;\n    fenwick_tree<int> ft(size);\n    auto fl = [&](int idx) {\n        sum\
    \ += ft.sum(a[idx]);\n        ft.add(a[idx], 1);\n    };\n    auto fr = [&](int\
    \ idx) {\n        sum += ft.sum(a[idx] + 1, size);\n        ft.add(a[idx], 1);\n\
    \    };\n    auto gl = [&](int idx) {\n        sum -= ft.sum(a[idx]);\n      \
    \  ft.add(a[idx], -1);\n    };\n    auto gr = [&](int idx) {\n        sum -= ft.sum(a[idx]\
    \ + 1, size);\n        ft.add(a[idx], -1);\n    };\n    Mo mo(n, fl, fr, gl, gr);\n\
    \    mo.input(q, 0);\n    mo.build();\n    vector<ll> ans(q);\n    while (q--)\
    \ {\n        int k = mo.process();\n        ans[k] = sum;\n    }\n    for (auto\
    \ x : ans) co(x);\n\n    return 0;\n}\n"
  dependsOn:
  - lib/algorithm/compress.hpp
  - lib/template/template.hpp
  - lib/algorithm/mo.hpp
  - lib/binary_tree/fenwick_tree.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/static_range_inversions.test.cpp
  requiredBy: []
  timestamp: '2023-05-22 20:02:34+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/static_range_inversions.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/static_range_inversions.test.cpp
- /verify/test/yosupo/data_structure/static_range_inversions.test.cpp.html
title: test/yosupo/data_structure/static_range_inversions.test.cpp
---
