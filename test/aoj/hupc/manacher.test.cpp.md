---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/string/manacher.hpp
    title: Manacher
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/2934
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/2934
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: string/manacher.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/2934\"\n#include\
    \ \"string/manacher.hpp\"\n#include <iostream>\n#include <string>\n\nint solve(const\
    \ std::string &s) {\n    int n = s.size();\n    if (n == 1) return 1;\n    Manacher\
    \ manacher(s);\n    for (int m = 1; m < n; ++m) {\n        bool flag = true;\n\
    \        int k = m;\n        while (k < n) {\n            flag &= manacher[k]\
    \ >= std::min(m + 1, n - k);\n            k += m;\n        }\n        if (flag)\
    \ return m + 1;\n    }\n    return n;\n}\n\nint main(void) {\n    int n;\n   \
    \ std::cin >> n;\n    std::string s;\n    std::cin >> s;\n    std::cout << solve(s)\
    \ << std::endl;\n\n    return 0;\n}\n"
  dependsOn:
  - lib/string/manacher.hpp
  isVerificationFile: true
  path: test/aoj/hupc/manacher.test.cpp
  requiredBy: []
  timestamp: '2024-01-23 18:07:39+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/hupc/manacher.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/hupc/manacher.test.cpp
- /verify/test/aoj/hupc/manacher.test.cpp.html
title: test/aoj/hupc/manacher.test.cpp
---
