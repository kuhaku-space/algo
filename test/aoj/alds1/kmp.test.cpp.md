---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/string/kmp.hpp
    title: "KMP\u6CD5"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: string/kmp.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B\"\n\
    #include \"string/kmp.hpp\"\n#include <iostream>\n#include <string>\n\nint main(void)\
    \ {\n    std::string s, t;\n    std::cin >> s >> t;\n    knuth_morris_pratt kmp(t);\n\
    \    auto ans = kmp.search(s);\n    for (int i = 0; i < (int)s.size(); ++i) {\n\
    \        if (ans[i] == (int)t.size()) std::cout << i - t.size() + 1 << std::endl;\n\
    \    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/string/kmp.hpp
  isVerificationFile: true
  path: test/aoj/alds1/kmp.test.cpp
  requiredBy: []
  timestamp: '2023-10-02 04:22:01+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/alds1/kmp.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/alds1/kmp.test.cpp
- /verify/test/aoj/alds1/kmp.test.cpp.html
title: test/aoj/alds1/kmp.test.cpp
---
