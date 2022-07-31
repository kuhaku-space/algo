---
data:
  _extendedDependsOn:
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
    path: lib/tree/cartesian_tree.hpp
    title: Cartesian Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/cartesian_tree
    links:
    - https://judge.yosupo.jp/problem/cartesian_tree
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/atcoder.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\n#include\
    \ \"template/atcoder.hpp\"\n#include \"tree/cartesian_tree.hpp\"\n\nint main(void)\
    \ {\n    int n;\n    cin >> n;\n    vector<int> a(n);\n    cin >> a;\n    auto\
    \ ans = cartesian_tree(a);\n    rep (i, n) {\n        if (ans[i] == -1) ans[i]\
    \ = i;\n    }\n    co(ans);\n\n    return 0;\n}\n"
  dependsOn:
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/template.hpp
  - lib/template/sonic.hpp
  - lib/tree/cartesian_tree.hpp
  isVerificationFile: true
  path: test/yosupo/tree/cartesian_tree.test.cpp
  requiredBy: []
  timestamp: '2022-07-31 09:42:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/tree/cartesian_tree.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/tree/cartesian_tree.test.cpp
- /verify/test/yosupo/tree/cartesian_tree.test.cpp.html
title: test/yosupo/tree/cartesian_tree.test.cpp
---
