---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/lis.hpp
    title: "\u6700\u9577\u5897\u52A0\u90E8\u5206\u5217"
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
    PROBLEM: https://judge.yosupo.jp/problem/longest_increasing_subsequence
    links:
    - https://judge.yosupo.jp/problem/longest_increasing_subsequence
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algorithm/lis.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/longest_increasing_subsequence\"\
    \n#include \"algorithm/lis.hpp\"\n#include \"template/atcoder.hpp\"\n\nint main(void)\
    \ {\n    int n;\n    cin >> n;\n    vector<int> a(n);\n    cin >> a;\n\n    auto\
    \ ans = make_LIS(a);\n    co(ans.size());\n    co(ans);\n\n    return 0;\n}\n"
  dependsOn:
  - lib/algorithm/lis.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/yosupo/new/longest_increasing_subsequence.test.cpp
  requiredBy: []
  timestamp: '2022-07-29 05:36:41+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/new/longest_increasing_subsequence.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/new/longest_increasing_subsequence.test.cpp
- /verify/test/yosupo/new/longest_increasing_subsequence.test.cpp.html
title: test/yosupo/new/longest_increasing_subsequence.test.cpp
---
