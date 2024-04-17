---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/math/min_linear.hpp
    title: min of mod of linear
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/min_of_mod_of_linear
    links:
    - https://judge.yosupo.jp/problem/min_of_mod_of_linear
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/min_linear.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/min_of_mod_of_linear\"\n\
    #include \"math/min_linear.hpp\"\n#include <iostream>\n\nint main() {\n    int\
    \ t;\n    std::cin >> t;\n    while (t--) {\n        int n, m, a, b;\n       \
    \ std::cin >> n >> m >> a >> b;\n        std::cout << min_linear(n, m, a, b) <<\
    \ '\\n';\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/math/min_linear.hpp
  isVerificationFile: true
  path: test/yosupo/math/min_linear.test.cpp
  requiredBy: []
  timestamp: '2024-03-23 07:02:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/math/min_linear.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/math/min_linear.test.cpp
- /verify/test/yosupo/math/min_linear.test.cpp.html
title: test/yosupo/math/min_linear.test.cpp
---
