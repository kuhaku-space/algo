---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/binary_tree/BIT.hpp
    title: lib/binary_tree/BIT.hpp
  - icon: ':question:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/1/ALDS1_1_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/1/ALDS1_1_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: binary_tree/BIT.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/1/ALDS1_1_C\"\
    \n#include \"binary_tree/BIT.hpp\"\n#include \"template/atcoder.hpp\"\n\nint main(void)\
    \ {\n    sonic();\n    int n;\n    cin >> n;\n    vector<int> a(n);\n    cin >>\
    \ a;\n    vector<pair<int, int>> b(n);\n    rep(i, n) b[i] = {a[i], i};\n    sort(all(b));\n\
    \    BIT<int> bit(n);\n    ll ans = 0;\n    repr(i, n) {\n        ans += bit.sum(b[i].second);\n\
    \        bit.add(b[i].second, 1);\n    }\n    co(ans);\n\n    return 0;\n}\n"
  dependsOn:
  - lib/binary_tree/BIT.hpp
  - lib/template/template.hpp
  - lib/template/atcoder.hpp
  isVerificationFile: true
  path: test/aoj/the_number_of_inversions.test.cpp
  requiredBy: []
  timestamp: '2021-09-22 04:23:32+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/aoj/the_number_of_inversions.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/the_number_of_inversions.test.cpp
- /verify/test/aoj/the_number_of_inversions.test.cpp.html
title: test/aoj/the_number_of_inversions.test.cpp
---
