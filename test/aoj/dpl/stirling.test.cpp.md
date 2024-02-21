---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_math.hpp
    title: lib/internal/internal_math.hpp
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_type_traits.hpp
    title: lib/internal/internal_type_traits.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/combination.hpp
    title: lib/math/combination.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/enumeration.hpp
    title: lib/math/enumeration.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: lib/math/modint.hpp
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_I
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_I
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/enumeration.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/DPL_5_I\"\n#include\
    \ <iostream>\n#include \"math/enumeration.hpp\"\n\nint main(void) {\n    int n,\
    \ k;\n    std::cin >> n >> k;\n    Enumeration<modint107> enume;\n    std::cout\
    \ << enume.stirling(n, k) << std::endl;\n\n    return 0;\n}\n"
  dependsOn:
  - lib/math/enumeration.hpp
  - lib/math/combination.hpp
  - lib/math/modint.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/aoj/dpl/stirling.test.cpp
  requiredBy: []
  timestamp: '2023-11-07 17:21:48+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/dpl/stirling.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/dpl/stirling.test.cpp
- /verify/test/aoj/dpl/stirling.test.cpp.html
title: test/aoj/dpl/stirling.test.cpp
---
