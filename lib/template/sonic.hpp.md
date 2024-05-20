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
    path: test/aoj/cgl/cross_point.test.cpp
    title: test/aoj/cgl/cross_point.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/cgl/projection.test.cpp
    title: test/aoj/cgl/projection.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/cgl/reflection.test.cpp
    title: test/aoj/cgl/reflection.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/point_add_range_sum.test.cpp
    title: test/yosupo/data_structure/point_add_range_sum.test.cpp
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
  code: "#pragma once\n#include \"template/template.hpp\"\nstruct Sonic {\n    Sonic()\
    \ {\n        std::ios::sync_with_stdio(false);\n        std::cin.tie(nullptr);\n\
    \        std::cout << std::fixed << std::setprecision(20);\n    }\n\n    constexpr\
    \ void operator()() const {}\n} sonic;\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/template/sonic.hpp
  requiredBy:
  - lib/template/atcoder.hpp
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/cgl/projection.test.cpp
  - test/aoj/cgl/cross_point.test.cpp
  - test/aoj/cgl/reflection.test.cpp
  - test/yosupo/sample/many_a+b.test.cpp
  - test/yosupo/data_structure/point_add_range_sum.test.cpp
documentation_of: lib/template/sonic.hpp
layout: document
redirect_from:
- /library/lib/template/sonic.hpp
- /library/lib/template/sonic.hpp.html
title: lib/template/sonic.hpp
---
