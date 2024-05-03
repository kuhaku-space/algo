---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/compress.hpp
    title: "\u5EA7\u6A19\u5727\u7E2E"
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/inversion_number.hpp
    title: "\u8EE2\u5012\u6570\u3092\u6C42\u3081\u308B"
  - icon: ':heavy_check_mark:'
    path: lib/binary_tree/fenwick_tree.hpp
    title: "\u30D5\u30A7\u30CB\u30C3\u30AF\u6728"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_5_D
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_5_D
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algorithm/inversion_number.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_5_D\"\n\
    #include \"algorithm/inversion_number.hpp\"\n#include <algorithm>\n#include <iostream>\n\
    #include <iterator>\n#include <vector>\n\nint main(void) {\n    int n;\n    std::cin\
    \ >> n;\n    std::vector<int> a(n);\n    std::copy_n(std::istream_iterator<int>(std::cin),\
    \ n, std::begin(a));\n    std::cout << inversion_number(a) << std::endl;\n\n \
    \   return 0;\n}\n"
  dependsOn:
  - lib/algorithm/inversion_number.hpp
  - lib/algorithm/compress.hpp
  - lib/binary_tree/fenwick_tree.hpp
  isVerificationFile: true
  path: test/aoj/alds1/inversion_number.test.cpp
  requiredBy: []
  timestamp: '2024-04-28 13:30:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/alds1/inversion_number.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/alds1/inversion_number.test.cpp
- /verify/test/aoj/alds1/inversion_number.test.cpp.html
title: test/aoj/alds1/inversion_number.test.cpp
---
