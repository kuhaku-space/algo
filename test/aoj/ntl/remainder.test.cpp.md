---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/bigint.hpp
    title: "\u591A\u500D\u9577\u6574\u6570"
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt.hpp
    title: "\u7573\u307F\u8FBC\u307F"
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_bit.hpp
    title: lib/internal/internal_bit.hpp
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_fft.hpp
    title: lib/internal/internal_fft.hpp
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_math.hpp
    title: lib/internal/internal_math.hpp
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_type_traits.hpp
    title: lib/internal/internal_type_traits.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: lib/math/modint.hpp
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_E
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_E
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: data_structure/bigint.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/NTL_2_E\"\n#include\
    \ <iostream>\n#include \"data_structure/bigint.hpp\"\n\nint main(void) {\n   \
    \ BigInt a, b;\n    std::cin >> a >> b;\n    std::cout << a % b << std::endl;\n\
    \n    return 0;\n}\n"
  dependsOn:
  - lib/data_structure/bigint.hpp
  - lib/fft/ntt.hpp
  - lib/internal/internal_fft.hpp
  - lib/internal/internal_bit.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/math/modint.hpp
  - lib/template/template.hpp
  isVerificationFile: true
  path: test/aoj/ntl/remainder.test.cpp
  requiredBy: []
  timestamp: '2024-04-28 13:30:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/aoj/ntl/remainder.test.cpp
layout: document
redirect_from:
- /verify/test/aoj/ntl/remainder.test.cpp
- /verify/test/aoj/ntl/remainder.test.cpp.html
title: test/aoj/ntl/remainder.test.cpp
---
