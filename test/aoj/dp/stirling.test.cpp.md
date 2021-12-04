---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: lib/math/combination.hpp
    title: lib/math/combination.hpp
  - icon: ':x:'
    path: lib/math/enumeration.hpp
    title: lib/math/enumeration.hpp
  - icon: ':x:'
    path: lib/math/modint.hpp
    title: modint
  - icon: ':x:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  - icon: ':x:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_I
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_I
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/enumeration.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/5/DPL_5_I\"\
    \n#include \"math/enumeration.hpp\"\n#include \"template/atcoder.hpp\"\n\nint\
    \ main(void) {\n    sonic();\n    int n, k;\n    cin >> n >> k;\n    Enumeration<MOD>\
    \ enume;\n    co(enume.stirling(n, k));\n\n    return 0;\n}\n"
  dependsOn:
  - lib/math/enumeration.hpp
  - lib/math/combination.hpp
  - lib/math/modint.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  isVerificationFile: true
  path: test/aoj/dp/stirling.test.cpp
  requiredBy: []
  timestamp: '2021-12-04 19:53:58+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/aoj/dp/stirling.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/dp/stirling.test.cpp
- /verify/test/aoj/dp/stirling.test.cpp.html
title: test/aoj/dp/stirling.test.cpp
---
