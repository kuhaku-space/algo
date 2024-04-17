---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/template/atcoder.hpp
    title: lib/template/atcoder.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/sample/many_a+b.test.cpp
    title: test/yosupo/sample/many_a+b.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: '#pragma once

    #include "template/template.hpp"

    #define FOR(i, m, n) for (int i = (m); i < int(n); ++i)

    #define FORR(i, m, n) for (int i = (m)-1; i >= int(n); --i)

    #define FORL(i, m, n) for (int64_t i = (m); i < int64_t(n); ++i)

    #define rep(i, n) FOR (i, 0, n)

    #define repn(i, n) FOR (i, 1, n + 1)

    #define repr(i, n) FORR (i, n, 0)

    #define repnr(i, n) FORR (i, n + 1, 1)

    #define all(s) (s).begin(), (s).end()'
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/template/macro.hpp
  requiredBy:
  - lib/template/atcoder.hpp
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/sample/many_a+b.test.cpp
documentation_of: lib/template/macro.hpp
layout: document
redirect_from:
- /library/lib/template/macro.hpp
- /library/lib/template/macro.hpp.html
title: lib/template/macro.hpp
---
