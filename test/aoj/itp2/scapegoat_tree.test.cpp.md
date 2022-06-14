---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/scapegoat_tree.hpp
    title: "\u30B9\u30B1\u30FC\u30D7\u30B4\u30FC\u30C8\u6728"
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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: binary_tree/scapegoat_tree.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/lesson/8/ITP2/7/ITP2_7_B\"\
    \n#include \"binary_tree/scapegoat_tree.hpp\"\n#include \"template/atcoder.hpp\"\
    \n\nint main(void) {\n    sonic();\n    int q;\n    cin >> q;\n    int size =\
    \ 0;\n    scapegoat_tree<int> st;\n    rep(i, q) {\n        int x, y;\n      \
    \  cin >> x >> y;\n        if (x == 0) {\n            if (!st.contains(y)) {\n\
    \                st.insert(y);\n                ++size;\n            }\n     \
    \       co(size);\n        } else if (x == 1) {\n            co(st.contains(y));\n\
    \        } else if (x == 2) {\n            if (st.contains(y)) {\n           \
    \     st.erase(y);\n                --size;\n            }\n        }\n    }\n\
    \n    return 0;\n}\n"
  dependsOn:
  - lib/binary_tree/scapegoat_tree.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  isVerificationFile: true
  path: test/aoj/itp2/scapegoat_tree.test.cpp
  requiredBy: []
  timestamp: '2022-06-15 03:56:13+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/itp2/scapegoat_tree.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/itp2/scapegoat_tree.test.cpp
- /verify/test/aoj/itp2/scapegoat_tree.test.cpp.html
title: test/aoj/itp2/scapegoat_tree.test.cpp
---
