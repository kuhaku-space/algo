---
data:
  _extendedDependsOn:
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
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution/convolution_mod.test.cpp
    title: test/yosupo/convolution/convolution_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4EFB\u610Fmod\u7573\u307F\u8FBC\u307F"
    links:
    - https://asako.growi.cloud/compro/NTT
    - https://math314.hateblo.jp/entry/2015/05/07/014908
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: fft/ntt.hpp: line\
    \ -1: no such header\n"
  code: "#pragma once\r\n#include \"fft/ntt.hpp\"\r\n#include \"template/template.hpp\"\
    \r\n\r\n/**\r\n * @brief \u4EFB\u610Fmod\u7573\u307F\u8FBC\u307F\r\n *\r\n * @tparam\
    \ mod\r\n * @tparam T\r\n * @param a\r\n * @param b\r\n * @return std::vector<T>\r\
    \n *\r\n * @see https://math314.hateblo.jp/entry/2015/05/07/014908\r\n * @see\
    \ https://asako.growi.cloud/compro/NTT\r\n */\r\ntemplate <unsigned int mod =\
    \ 998244353, class T,\r\n          std::enable_if_t<std::is_integral<T>::value>\
    \ * = nullptr>\r\nstd::vector<T> convolution_mod(const std::vector<T> &a, const\
    \ std::vector<T> &b) {\r\n    int n = int(a.size()), m = int(b.size());\r\n  \
    \  if (!n || !m) return {};\r\n\r\n    int z = (int)internal::bit_ceil((unsigned\
    \ int)(n + m - 1));\r\n\r\n    static constexpr std::uint64_t MOD1 = 754974721;\
    \  // 2^24\r\n    static constexpr std::uint64_t MOD2 = 167772161;  // 2^25\r\n\
    \    static constexpr std::uint64_t MOD3 = 469762049;  // 2^26\r\n    static constexpr\
    \ std::uint64_t M2M3 = MOD2 * MOD3;\r\n    static constexpr std::uint64_t M1M3\
    \ = MOD1 * MOD3;\r\n    static constexpr std::uint64_t M1M2 = MOD1 * MOD2;\r\n\
    \    static constexpr __uint128_t M1M2M3 = (__uint128_t)MOD1 * MOD2 * MOD3;\r\n\
    \r\n    static constexpr std::uint64_t i1 = internal::inv_gcd(MOD2 * MOD3, MOD1).second;\r\
    \n    static constexpr std::uint64_t i2 = internal::inv_gcd(MOD1 * MOD3, MOD2).second;\r\
    \n    static constexpr std::uint64_t i3 = internal::inv_gcd(MOD1 * MOD2, MOD3).second;\r\
    \n\r\n    static constexpr int MAX_AB_BIT = 24;\r\n    static_assert(MOD1 % (1ull\
    \ << MAX_AB_BIT) == 1,\r\n                  \"MOD1 isn't enough to support an\
    \ array length of 2^24.\");\r\n    static_assert(MOD2 % (1ull << MAX_AB_BIT) ==\
    \ 1,\r\n                  \"MOD2 isn't enough to support an array length of 2^24.\"\
    );\r\n    static_assert(MOD3 % (1ull << MAX_AB_BIT) == 1,\r\n                \
    \  \"MOD3 isn't enough to support an array length of 2^24.\");\r\n    assert(n\
    \ + m - 1 <= (1 << MAX_AB_BIT));\r\n\r\n    auto c1 = convolution<MOD1>(a, b);\r\
    \n    auto c2 = convolution<MOD2>(a, b);\r\n    auto c3 = convolution<MOD3>(a,\
    \ b);\r\n\r\n    std::vector<int> c(n + m - 1);\r\n    for (int i = 0; i < n +\
    \ m - 1; ++i) {\r\n        __uint128_t x = (c1[i] * i1) % MOD1 * (__uint128_t)M2M3;\r\
    \n        x += (c2[i] * i2) % MOD2 * (__uint128_t)M1M3;\r\n        if (x >= M1M2M3)\
    \ x -= M1M2M3;\r\n        x += (c3[i] * i3) % MOD3 * (__uint128_t)M1M2;\r\n  \
    \      if (x >= M1M2M3) x -= M1M2M3;\r\n        c[i] = x % mod;\r\n    }\r\n\r\
    \n    return c;\r\n}\r\n"
  dependsOn:
  - lib/fft/ntt.hpp
  - lib/internal/internal_fft.hpp
  - lib/internal/internal_bit.hpp
  - lib/template/template.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/math/modint.hpp
  isVerificationFile: false
  path: lib/fft/ntt_mod.hpp
  requiredBy: []
  timestamp: '2023-07-12 23:02:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/convolution/convolution_mod.test.cpp
documentation_of: lib/fft/ntt_mod.hpp
layout: document
redirect_from:
- /library/lib/fft/ntt_mod.hpp
- /library/lib/fft/ntt_mod.hpp.html
title: "\u4EFB\u610Fmod\u7573\u307F\u8FBC\u307F"
---
