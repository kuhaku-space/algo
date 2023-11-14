---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/lis.hpp
    title: "\u6700\u9577\u5897\u52A0\u90E8\u5206\u5217"
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_D
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_D
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algorithm/lis.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_D\"\n#include\
    \ <algorithm>\n#include <iostream>\n#include <iterator>\n#include <vector>\n#include\
    \ \"algorithm/lis.hpp\"\n\nint main(void) {\n    int n;\n    std::cin >> n;\n\
    \    std::vector<int> a(n);\n    std::copy_n(std::istream_iterator<int>(std::cin),\
    \ n, std::begin(a));\n    std::cout << longest_increasing_subsequence(a) << std::endl;\n\
    \n    return 0;\n}\n"
  dependsOn:
  - lib/algorithm/lis.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/aoj/dpl/longest_increasing_subsequense.test.cpp
  requiredBy: []
  timestamp: '2023-11-07 17:51:24+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/dpl/longest_increasing_subsequense.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/dpl/longest_increasing_subsequense.test.cpp
- /verify/test/aoj/dpl/longest_increasing_subsequense.test.cpp.html
title: test/aoj/dpl/longest_increasing_subsequense.test.cpp
---
