---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/geometry/geometry.hpp
    title: lib/geometry/geometry.hpp
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: geometry/geometry.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_C\"\
    \n#include \"geometry/geometry.hpp\"\n#include \"template/atcoder.hpp\"\n\nint\
    \ main(void) {\n    sonic();\n    setp(10);\n    Point<double> a, b;\n    cin\
    \ >> a >> b;\n    Line l(a, b);\n    int q;\n    cin >> q;\n    while (q--) {\n\
    \        Point<double> p;\n        cin >> p;\n        auto ans = ccw(a, b, p);\n\
    \        if (ans == 1)\n            co(\"COUNTER_CLOCKWISE\");\n        else if\
    \ (ans == -1)\n            co(\"CLOCKWISE\");\n        else if (ans == 2)\n  \
    \          co(\"ONLINE_BACK\");\n        else if (ans == -2)\n            co(\"\
    ONLINE_FRONT\");\n        else\n            co(\"ON_SEGMENT\");\n    }\n\n   \
    \ return 0;\n}\n"
  dependsOn:
  - lib/geometry/geometry.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/aoj/cgl/counter-clockwise.test.cpp
  requiredBy: []
  timestamp: '2022-06-22 08:11:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/cgl/counter-clockwise.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/cgl/counter-clockwise.test.cpp
- /verify/test/aoj/cgl/counter-clockwise.test.cpp.html
title: test/aoj/cgl/counter-clockwise.test.cpp
---
