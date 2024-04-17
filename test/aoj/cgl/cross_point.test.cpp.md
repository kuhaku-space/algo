---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/geometry/geometry.hpp
    title: lib/geometry/geometry.hpp
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
    ERROR: '0.00000001'
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/CGL_2_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/CGL_2_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: geometry/geometry.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/CGL_2_C\"\n#define\
    \ ERROR 0.00000001\n#include <iostream>\n#include \"geometry/geometry.hpp\"\n\
    #include \"template/sonic.hpp\"\n\nint main(void) {\n    int q;\n    std::cin\
    \ >> q;\n    while (q--) {\n        Point<double> a, b, c, d;\n        std::cin\
    \ >> a >> b >> c >> d;\n        Line l(a, b), m(c, d);\n        std::cout << cross_point(l,\
    \ m) << std::endl;\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/geometry/geometry.hpp
  - lib/template/template.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/aoj/cgl/cross_point.test.cpp
  requiredBy: []
  timestamp: '2023-11-07 17:53:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/cgl/cross_point.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/cgl/cross_point.test.cpp
- /verify/test/aoj/cgl/cross_point.test.cpp.html
title: test/aoj/cgl/cross_point.test.cpp
---
