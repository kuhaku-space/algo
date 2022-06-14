---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/treap.hpp
    title: Treap
  - icon: ':heavy_check_mark:'
    path: lib/random/split_mix_64.hpp
    title: "\u7591\u4F3C\u4E71\u6570\u751F\u6210\u5668 SplitMix64"
  - icon: ':heavy_check_mark:'
    path: lib/random/xorshift.hpp
    title: "\u64EC\u4F3C\u4E71\u6570\u751F\u6210\u5668"
  - icon: ':heavy_check_mark:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/7/ITP2_7_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/7/ITP2_7_B
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.4/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: binary_tree/treap.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/7/ITP2_7_B\"\
    \n#include \"binary_tree/treap.hpp\"\n#include \"template/atcoder.hpp\"\n\nint\
    \ main(void) {\n    sonic();\n    int q;\n    cin >> q;\n    int size = 0;\n \
    \   Treap<int> treap;\n    rep(i, q) {\n        int x, y;\n        cin >> x >>\
    \ y;\n        if (x == 0) {\n            if (!treap.contains(y)) {\n         \
    \       treap.insert(y);\n                ++size;\n            }\n           \
    \ co(size);\n        } else if (x == 1) {\n            co(treap.contains(y));\n\
    \        } else if (x == 2) {\n            if (treap.contains(y)) {\n        \
    \        treap.erase(y);\n                --size;\n            }\n        }\n\
    \    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/binary_tree/treap.hpp
  - lib/random/xorshift.hpp
  - lib/random/split_mix_64.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  isVerificationFile: true
  path: test/aoj/itp2/treap.test.cpp
  requiredBy: []
  timestamp: '2022-06-15 03:56:13+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/itp2/treap.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/itp2/treap.test.cpp
- /verify/test/aoj/itp2/treap.test.cpp.html
title: test/aoj/itp2/treap.test.cpp
---
