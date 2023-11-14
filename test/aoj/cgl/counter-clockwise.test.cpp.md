---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/geometry/geometry.hpp
    title: lib/geometry/geometry.hpp
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/CGL_1_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/CGL_1_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: geometry/geometry.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/CGL_1_C\"\n#include\
    \ <cstdio>\n#include <iostream>\n#include \"geometry/geometry.hpp\"\n\nint main(void)\
    \ {\n    Point<double> a, b;\n    std::cin >> a >> b;\n    Line l(a, b);\n   \
    \ int q;\n    std::cin >> q;\n    while (q--) {\n        Point<double> p;\n  \
    \      std::cin >> p;\n        auto ans = ccw(a, b, p);\n        if (ans == 1)\
    \ std::puts(\"COUNTER_CLOCKWISE\");\n        else if (ans == -1) std::puts(\"\
    CLOCKWISE\");\n        else if (ans == 2) std::puts(\"ONLINE_BACK\");\n      \
    \  else if (ans == -2) std::puts(\"ONLINE_FRONT\");\n        else std::puts(\"\
    ON_SEGMENT\");\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/geometry/geometry.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/aoj/cgl/counter-clockwise.test.cpp
  requiredBy: []
  timestamp: '2023-11-07 17:18:00+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/cgl/counter-clockwise.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/cgl/counter-clockwise.test.cpp
- /verify/test/aoj/cgl/counter-clockwise.test.cpp.html
title: test/aoj/cgl/counter-clockwise.test.cpp
---
