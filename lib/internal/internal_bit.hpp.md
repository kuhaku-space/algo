---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/bigint.hpp
    title: "\u591A\u500D\u9577\u6574\u6570"
  - icon: ':warning:'
    path: lib/fft/formal_power_series.hpp
    title: lib/fft/formal_power_series.hpp
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt.hpp
    title: lib/fft/ntt.hpp
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt_mod.hpp
    title: "\u4EFB\u610Fmod\u7573\u307F\u8FBC\u307F"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/addition.test.cpp
    title: test/aoj/ntl/addition.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/difference.test.cpp
    title: test/aoj/ntl/difference.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/division.test.cpp
    title: test/aoj/ntl/division.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/multiplication.test.cpp
    title: test/aoj/ntl/multiplication.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/multiplication2.test.cpp
    title: test/aoj/ntl/multiplication2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/remainder.test.cpp
    title: test/aoj/ntl/remainder.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution/convolution.test.cpp
    title: test/yosupo/convolution/convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution/convolution_mod.test.cpp
    title: test/yosupo/convolution/convolution_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"template/template.hpp\"\n\nnamespace internal {\n\
    \n// @return same with std::bit::bit_ceil\nunsigned int bit_ceil(unsigned int\
    \ n) {\n    unsigned int x = 1;\n    while (x < (unsigned int)(n)) x *= 2;\n \
    \   return x;\n}\n\n// @param n `1 <= n`\n// @return same with std::bit::countr_zero\n\
    int countr_zero(unsigned int n) {\n    return __builtin_ctz(n);\n}\n\n// @param\
    \ n `1 <= n`\n// @return same with std::bit::countr_zero\nconstexpr int countr_zero_constexpr(unsigned\
    \ int n) {\n    int x = 0;\n    while (!(n & (1 << x))) x++;\n    return x;\n\
    }\n\n}  // namespace internal\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/internal/internal_bit.hpp
  requiredBy:
  - lib/fft/ntt_mod.hpp
  - lib/fft/ntt.hpp
  - lib/fft/formal_power_series.hpp
  - lib/data_structure/bigint.hpp
  timestamp: '2023-05-22 19:46:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/ntl/addition.test.cpp
  - test/aoj/ntl/remainder.test.cpp
  - test/aoj/ntl/multiplication2.test.cpp
  - test/aoj/ntl/multiplication.test.cpp
  - test/aoj/ntl/division.test.cpp
  - test/aoj/ntl/difference.test.cpp
  - test/yosupo/convolution/convolution.test.cpp
  - test/yosupo/convolution/convolution_mod.test.cpp
documentation_of: lib/internal/internal_bit.hpp
layout: document
redirect_from:
- /library/lib/internal/internal_bit.hpp
- /library/lib/internal/internal_bit.hpp.html
title: lib/internal/internal_bit.hpp
---
