---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/heap/leftist_heap.hpp
    title: leftist heap
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_9_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_9_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: heap/leftist_heap.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_9_C\"\n\
    #include \"heap/leftist_heap.hpp\"\n#include \"template/atcoder.hpp\"\n\nint main(void)\
    \ {\n    leftist_heap<int> heap;\n    while (true) {\n        string s;\n    \
    \    cin >> s;\n        if (s == \"end\") {\n            break;\n        } else\
    \ if (s == \"insert\") {\n            int x;\n            cin >> x;\n        \
    \    heap.push(x);\n        } else {\n            co(heap.top());\n          \
    \  heap.pop();\n        }\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/heap/leftist_heap.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/aoj/alds1/leftist_heap.test.cpp
  requiredBy: []
  timestamp: '2023-05-22 20:02:34+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/alds1/leftist_heap.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/alds1/leftist_heap.test.cpp
- /verify/test/aoj/alds1/leftist_heap.test.cpp.html
title: test/aoj/alds1/leftist_heap.test.cpp
---
