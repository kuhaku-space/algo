---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/math/prime_number.hpp
    title: "\u7D20\u6570\u30E9\u30A4\u30D6\u30E9\u30EA"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_1_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_1_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/prime_number.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_1_C\"\n\
    #include <iostream>\n#include \"math/prime_number.hpp\"\n\nprime_number pn;\n\n\
    int main(void) {\n    int n;\n    std::cin >> n;\n    int ans = 0;\n    while\
    \ (n--) {\n        int a;\n        std::cin >> a;\n        ans += pn.is_prime(a);\n\
    \    }\n    std::cout << ans << std::endl;\n\n    return 0;\n}\n"
  dependsOn:
  - lib/math/prime_number.hpp
  isVerificationFile: true
  path: test/aoj/alds1/prime_numbers.test.cpp
  requiredBy: []
  timestamp: '2023-10-02 05:19:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/alds1/prime_numbers.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/alds1/prime_numbers.test.cpp
- /verify/test/aoj/alds1/prime_numbers.test.cpp.html
title: test/aoj/alds1/prime_numbers.test.cpp
---
