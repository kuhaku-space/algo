---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/dp/lis.hpp
    title: lib/dp/lis.hpp
  - icon: ':question:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/1/DPL_1_D
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/1/DPL_1_D
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: dp/lis.hpp: line\
    \ -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/1/DPL_1_D\"\
    \n#include \"dp/lis.hpp\"\n#include \"template/atcoder.hpp\"\n\nint main(void)\
    \ {\n    sonic();\n    int n;\n    cin >> n;\n    vector<int> a(n);\n    cin >>\
    \ a;\n    co(LIS(a));\n\n    return 0;\n}\n"
  dependsOn:
  - lib/dp/lis.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  isVerificationFile: true
  path: test/aoj/longest_increasing_subsequense.test.cpp
  requiredBy: []
  timestamp: '2021-09-29 10:01:10+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/longest_increasing_subsequense.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/longest_increasing_subsequense.test.cpp
- /verify/test/aoj/longest_increasing_subsequense.test.cpp.html
title: test/aoj/longest_increasing_subsequense.test.cpp
---
