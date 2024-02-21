---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/disjoint_sparse_table.hpp
    title: Disjoint Sparse Table
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_bit.hpp
    title: lib/internal/internal_bit.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: data_structure/disjoint_sparse_table.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n#include <iostream>\n\
    #include <vector>\n#include \"data_structure/disjoint_sparse_table.hpp\"\n#include\
    \ \"segment_tree/monoid.hpp\"\n\nint main(void) {\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    std::vector<int> a(n);\n    for (auto &e : a) std::cin >> e;\n\
    \    disjoint_sparse_table<Min<int>> st(a);\n    while (q--) {\n        int l,\
    \ r;\n        std::cin >> l >> r;\n        std::cout << st.prod(l, r) << '\\n';\n\
    \    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/data_structure/disjoint_sparse_table.hpp
  - lib/internal/internal_bit.hpp
  - lib/segment_tree/monoid.hpp
  isVerificationFile: true
  path: test/yosupo/data_structure/static_rmq.2.test.cpp
  requiredBy: []
  timestamp: '2024-02-21 23:45:40+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/data_structure/static_rmq.2.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/data_structure/static_rmq.2.test.cpp
- /verify/test/yosupo/data_structure/static_rmq.2.test.cpp.html
title: test/yosupo/data_structure/static_rmq.2.test.cpp
---
