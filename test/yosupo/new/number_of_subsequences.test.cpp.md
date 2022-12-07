---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/algorithm/compress.hpp
    title: "\u5EA7\u6A19\u5727\u7E2E"
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: modint
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
    PROBLEM: https://judge.yosupo.jp/problem/number_of_subsequences
    links:
    - https://judge.yosupo.jp/problem/number_of_subsequences
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.8/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: algorithm/compress.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_subsequences\"\
    \n#include \"algorithm/compress.hpp\"\n#include \"math/modint.hpp\"\n#include\
    \ \"template/atcoder.hpp\"\n\nusing Mint = ModInt<>;\n\nint main(void) {\n   \
    \ int n;\n    cin >> n;\n    vector<int> a(n);\n    cin >> a;\n    a = compress(a);\n\
    \    Mint ans = 0;\n    vector<Mint> dp(*max_element(all(a)) + 1);\n    for (auto\
    \ x : a) {\n        auto t = ans - dp[x] + 1;\n        ans += t;\n        dp[x]\
    \ += t;\n    }\n    co(ans);\n\n    return 0;\n}\n"
  dependsOn:
  - lib/algorithm/compress.hpp
  - lib/template/template.hpp
  - lib/math/modint.hpp
  - lib/template/atcoder.hpp
  - lib/template/macro.hpp
  - lib/template/sonic.hpp
  isVerificationFile: true
  path: test/yosupo/new/number_of_subsequences.test.cpp
  requiredBy: []
  timestamp: '2022-07-30 08:32:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/yosupo/new/number_of_subsequences.test.cpp
layout: document
redirect_from:
- /verify/test/yosupo/new/number_of_subsequences.test.cpp
- /verify/test/yosupo/new/number_of_subsequences.test.cpp.html
title: test/yosupo/new/number_of_subsequences.test.cpp
---
