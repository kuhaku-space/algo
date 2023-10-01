---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/string/kmp.hpp
    title: "KMP\u6CD5"
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/2763
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/2763
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: string/kmp.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/2763\"\n#include\
    \ \"string/kmp.hpp\"\n#include \"template/atcoder.hpp\"\n\nint main(void) {\n\
    \    std::string s;\n    std::cin >> s;\n    int n = s.size();\n    int x = n\
    \ - knuth_morris_pratt(s)[n];\n    int y = n + 1;\n    while (!(y % x == 0 &&\
    \ y / x % 3 == 0)) ++y;\n    int b = y - n;\n    if (b * 2 > n - 3) {\n      \
    \  co(\"mitomerarenaiWA\");\n        return 0;\n    }\n    std::string ans = \"\
    Love \";\n    ans += s.substr(0, y / 3);\n    ans += \"!\";\n    co(ans);\n\n\
    \    return 0;\n}\n"
  dependsOn:
  - lib/string/kmp.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/aoj/hupc/kmp.test.cpp
  requiredBy: []
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/hupc/kmp.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/hupc/kmp.test.cpp
- /verify/test/aoj/hupc/kmp.test.cpp.html
title: test/aoj/hupc/kmp.test.cpp
---
