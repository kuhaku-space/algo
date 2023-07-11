---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/math/pow.hpp
    title: lib/math/pow.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/monoid.hpp
    title: lib/segment_tree/monoid.hpp
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/segment_tree.hpp
    title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
  - icon: ':heavy_check_mark:'
    path: lib/segment_tree/segment_tree_raq.hpp
    title: lib/segment_tree/segment_tree_raq.hpp
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: segment_tree/segment_tree_raq.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/2/DSL_2_H\"\
    \n#include \"segment_tree/segment_tree_raq.hpp\"\n#include \"template/atcoder.hpp\"\
    \n\nint main(void) {\n    sonic();\n    int n, q;\n    cin >> n >> q;\n    segment_tree_range_add_range_min<ll>\
    \ st(n, 0);\n\n    rep(i, q) {\n        int type;\n        cin >> type;\n    \
    \    if (type == 0) {\n            int s, t, x;\n            cin >> s >> t >>\
    \ x;\n            st.apply(s, t + 1, x);\n        } else {\n            int s,\
    \ t;\n            cin >> s >> t;\n            co(st.prod(s, t + 1));\n       \
    \ }\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/segment_tree/segment_tree_raq.hpp
  - lib/segment_tree/segment_tree.hpp
  - lib/math/pow.hpp
  - lib/template/template.hpp
  - lib/segment_tree/monoid.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/aoj/dsl/raq_rmq.test.cpp
  requiredBy: []
  timestamp: '2023-05-22 20:52:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/dsl/raq_rmq.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/dsl/raq_rmq.test.cpp
- /verify/test/aoj/dsl/raq_rmq.test.cpp.html
title: test/aoj/dsl/raq_rmq.test.cpp
---
