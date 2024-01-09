---
data:
  _extendedDependsOn:
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
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/bigint.hpp
    title: "\u591A\u500D\u9577\u6574\u6570"
  - icon: ':warning:'
    path: lib/fft/formal_power_series.hpp
    title: lib/fft/formal_power_series.hpp
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
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/addition_of_big_integers.test.cpp
    title: test/yosupo/data_structure/addition_of_big_integers.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u7573\u307F\u8FBC\u307F"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: internal/internal_fft.hpp:\
    \ line -1: no such header\n"
  code: "\r\n#include \"internal/internal_fft.hpp\"\r\n#include \"template/template.hpp\"\
    \r\n\r\n/**\r\n * @brief \u7573\u307F\u8FBC\u307F\r\n *\r\n * @tparam mint\r\n\
    \ * @param a\r\n * @param b\r\n * @return std::vector<mint>\r\n */\r\ntemplate\
    \ <class mint, internal::is_static_modint_t<mint> * = nullptr>\r\nstd::vector<mint>\
    \ convolution(std::vector<mint> &&a, std::vector<mint> &&b) {\r\n    int n = int(a.size()),\
    \ m = int(b.size());\r\n    if (!n || !m) return {};\r\n\r\n    int z = (int)internal::bit_ceil((unsigned\
    \ int)(n + m - 1));\r\n    assert((mint::mod() - 1) % z == 0);\r\n\r\n    if (std::min(n,\
    \ m) <= 60) return convolution_naive(a, b);\r\n    return internal::convolution_fft(a,\
    \ b);\r\n}\r\ntemplate <class mint, internal::is_static_modint_t<mint> * = nullptr>\r\
    \nstd::vector<mint> convolution(const std::vector<mint> &a, const std::vector<mint>\
    \ &b) {\r\n    int n = int(a.size()), m = int(b.size());\r\n    if (!n || !m)\
    \ return {};\r\n\r\n    int z = (int)internal::bit_ceil((unsigned int)(n + m -\
    \ 1));\r\n    assert((mint::mod() - 1) % z == 0);\r\n\r\n    if (std::min(n, m)\
    \ <= 60) return convolution_naive(a, b);\r\n    return internal::convolution_fft(a,\
    \ b);\r\n}\r\n\r\ntemplate <unsigned int mod = 998244353, class T,\r\n       \
    \   std::enable_if_t<std::is_integral<T>::value> * = nullptr>\r\nstd::vector<T>\
    \ convolution(const std::vector<T> &a, const std::vector<T> &b) {\r\n    int n\
    \ = int(a.size()), m = int(b.size());\r\n    if (!n || !m) return {};\r\n\r\n\
    \    using mint = static_modint<mod>;\r\n\r\n    int z = (int)internal::bit_ceil((unsigned\
    \ int)(n + m - 1));\r\n    assert((mint::mod() - 1) % z == 0);\r\n\r\n    std::vector<mint>\
    \ a2(n), b2(m);\r\n    for (int i = 0; i < n; i++) {\r\n        a2[i] = mint(a[i]);\r\
    \n    }\r\n    for (int i = 0; i < m; i++) {\r\n        b2[i] = mint(b[i]);\r\n\
    \    }\r\n    auto c2 = convolution(std::move(a2), std::move(b2));\r\n    std::vector<T>\
    \ c(n + m - 1);\r\n    for (int i = 0; i < n + m - 1; i++) {\r\n        c[i] =\
    \ c2[i].val();\r\n    }\r\n    return c;\r\n}\r\n\r\nstd::vector<std::int64_t>\
    \ convolution_ll(const std::vector<std::int64_t> &a,\r\n                     \
    \                    const std::vector<std::int64_t> &b) {\r\n    int n = int(a.size()),\
    \ m = int(b.size());\r\n    if (!n || !m) return {};\r\n\r\n    static constexpr\
    \ std::uint64_t MOD1 = 754974721;  // 2^24\r\n    static constexpr std::uint64_t\
    \ MOD2 = 167772161;  // 2^25\r\n    static constexpr std::uint64_t MOD3 = 469762049;\
    \  // 2^26\r\n    static constexpr std::uint64_t M2M3 = MOD2 * MOD3;\r\n    static\
    \ constexpr std::uint64_t M1M3 = MOD1 * MOD3;\r\n    static constexpr std::uint64_t\
    \ M1M2 = MOD1 * MOD2;\r\n    static constexpr std::uint64_t M1M2M3 = MOD1 * MOD2\
    \ * MOD3;\r\n\r\n    static constexpr std::uint64_t i1 = internal::inv_gcd(MOD2\
    \ * MOD3, MOD1).second;\r\n    static constexpr std::uint64_t i2 = internal::inv_gcd(MOD1\
    \ * MOD3, MOD2).second;\r\n    static constexpr std::uint64_t i3 = internal::inv_gcd(MOD1\
    \ * MOD2, MOD3).second;\r\n\r\n    static constexpr int MAX_AB_BIT = 24;\r\n \
    \   static_assert(MOD1 % (1ull << MAX_AB_BIT) == 1,\r\n                  \"MOD1\
    \ isn't enough to support an array length of 2^24.\");\r\n    static_assert(MOD2\
    \ % (1ull << MAX_AB_BIT) == 1,\r\n                  \"MOD2 isn't enough to support\
    \ an array length of 2^24.\");\r\n    static_assert(MOD3 % (1ull << MAX_AB_BIT)\
    \ == 1,\r\n                  \"MOD3 isn't enough to support an array length of\
    \ 2^24.\");\r\n    assert(n + m - 1 <= (1 << MAX_AB_BIT));\r\n\r\n    auto c1\
    \ = convolution<MOD1>(a, b);\r\n    auto c2 = convolution<MOD2>(a, b);\r\n   \
    \ auto c3 = convolution<MOD3>(a, b);\r\n\r\n    std::vector<std::int64_t> c(n\
    \ + m - 1);\r\n    for (int i = 0; i < n + m - 1; i++) {\r\n        std::uint64_t\
    \ x = 0;\r\n        x += (c1[i] * i1) % MOD1 * M2M3;\r\n        x += (c2[i] *\
    \ i2) % MOD2 * M1M3;\r\n        x += (c3[i] * i3) % MOD3 * M1M2;\r\n        std::int64_t\
    \ diff = c1[i] - internal::safe_mod((std::int64_t)(x), (std::int64_t)(MOD1));\r\
    \n        if (diff < 0) diff += MOD1;\r\n        static constexpr std::uint64_t\
    \ offset[5] = {0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};\r\n        x -= offset[diff\
    \ % 5];\r\n        c[i] = x;\r\n    }\r\n\r\n    return c;\r\n}\r\n"
  dependsOn:
  - lib/internal/internal_fft.hpp
  - lib/internal/internal_bit.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/math/modint.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/fft/ntt.hpp
  requiredBy:
  - lib/fft/ntt_mod.hpp
  - lib/fft/formal_power_series.hpp
  - lib/data_structure/bigint.hpp
  timestamp: '2023-10-01 18:31:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/convolution/convolution_mod.test.cpp
  - test/yosupo/convolution/convolution.test.cpp
  - test/yosupo/data_structure/addition_of_big_integers.test.cpp
  - test/aoj/ntl/multiplication.test.cpp
  - test/aoj/ntl/remainder.test.cpp
  - test/aoj/ntl/division.test.cpp
  - test/aoj/ntl/difference.test.cpp
  - test/aoj/ntl/multiplication2.test.cpp
  - test/aoj/ntl/addition.test.cpp
documentation_of: lib/fft/ntt.hpp
layout: document
redirect_from:
- /library/lib/fft/ntt.hpp
- /library/lib/fft/ntt.hpp.html
title: "\u7573\u307F\u8FBC\u307F"
---
