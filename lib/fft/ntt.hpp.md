---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_bit.hpp
    title: lib/internal/internal_bit.hpp
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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: internal/internal_bit.hpp:\
    \ line -1: no such header\n"
  code: "#include \"internal/internal_bit.hpp\"\r\n#include \"internal/internal_math.hpp\"\
    \r\n#include \"internal/internal_type_traits.hpp\"\r\n#include \"math/modint.hpp\"\
    \r\n#include \"template/template.hpp\"\r\n\r\nnamespace internal {\r\n\r\ntemplate\
    \ <class mint, int g = internal::primitive_root<mint::mod()>,\r\n          internal::is_static_modint_t<mint>\
    \ * = nullptr>\r\nstruct fft_info {\r\n    static constexpr int rank2 = countr_zero_constexpr(mint::mod()\
    \ - 1);\r\n    std::array<mint, rank2 + 1> root;   // root[i]^(2^i) == 1\r\n \
    \   std::array<mint, rank2 + 1> iroot;  // root[i] * iroot[i] == 1\r\n\r\n   \
    \ std::array<mint, std::max(0, rank2 - 2 + 1)> rate2;\r\n    std::array<mint,\
    \ std::max(0, rank2 - 2 + 1)> irate2;\r\n\r\n    std::array<mint, std::max(0,\
    \ rank2 - 3 + 1)> rate3;\r\n    std::array<mint, std::max(0, rank2 - 3 + 1)> irate3;\r\
    \n\r\n    fft_info() {\r\n        root[rank2] = mint(g).pow((mint::mod() - 1)\
    \ >> rank2);\r\n        iroot[rank2] = root[rank2].inv();\r\n        for (int\
    \ i = rank2 - 1; i >= 0; i--) {\r\n            root[i] = root[i + 1] * root[i\
    \ + 1];\r\n            iroot[i] = iroot[i + 1] * iroot[i + 1];\r\n        }\r\n\
    \r\n        {\r\n            mint prod = 1, iprod = 1;\r\n            for (int\
    \ i = 0; i <= rank2 - 2; i++) {\r\n                rate2[i] = root[i + 2] * prod;\r\
    \n                irate2[i] = iroot[i + 2] * iprod;\r\n                prod *=\
    \ iroot[i + 2];\r\n                iprod *= root[i + 2];\r\n            }\r\n\
    \        }\r\n        {\r\n            mint prod = 1, iprod = 1;\r\n         \
    \   for (int i = 0; i <= rank2 - 3; i++) {\r\n                rate3[i] = root[i\
    \ + 3] * prod;\r\n                irate3[i] = iroot[i + 3] * iprod;\r\n      \
    \          prod *= iroot[i + 3];\r\n                iprod *= root[i + 3];\r\n\
    \            }\r\n        }\r\n    }\r\n};\r\n\r\ntemplate <class mint, internal::is_static_modint_t<mint>\
    \ * = nullptr>\r\nvoid butterfly(std::vector<mint> &a) {\r\n    int n = int(a.size());\r\
    \n    int h = internal::countr_zero((unsigned int)n);\r\n\r\n    static const\
    \ fft_info<mint> info;\r\n\r\n    int len = 0;  // a[i, i+(n>>len), i+2*(n>>len),\
    \ ..] is transformed\r\n    while (len < h) {\r\n        if (h - len == 1) {\r\
    \n            int p = 1 << (h - len - 1);\r\n            mint rot = 1;\r\n   \
    \         for (int s = 0; s < (1 << len); s++) {\r\n                int offset\
    \ = s << (h - len);\r\n                for (int i = 0; i < p; i++) {\r\n     \
    \               auto l = a[i + offset];\r\n                    auto r = a[i +\
    \ offset + p] * rot;\r\n                    a[i + offset] = l + r;\r\n       \
    \             a[i + offset + p] = l - r;\r\n                }\r\n            \
    \    if (s + 1 != (1 << len)) rot *= info.rate2[countr_zero(~(unsigned int)(s))];\r\
    \n            }\r\n            len++;\r\n        } else {\r\n            // 4-base\r\
    \n            int p = 1 << (h - len - 2);\r\n            mint rot = 1, imag =\
    \ info.root[2];\r\n            for (int s = 0; s < (1 << len); s++) {\r\n    \
    \            mint rot2 = rot * rot;\r\n                mint rot3 = rot2 * rot;\r\
    \n                int offset = s << (h - len);\r\n                for (int i =\
    \ 0; i < p; i++) {\r\n                    auto mod2 = 1ULL * mint::mod() * mint::mod();\r\
    \n                    auto a0 = 1ULL * a[i + offset].val();\r\n              \
    \      auto a1 = 1ULL * a[i + offset + p].val() * rot.val();\r\n             \
    \       auto a2 = 1ULL * a[i + offset + 2 * p].val() * rot2.val();\r\n       \
    \             auto a3 = 1ULL * a[i + offset + 3 * p].val() * rot3.val();\r\n \
    \                   auto a1na3imag = 1ULL * mint(a1 + mod2 - a3).val() * imag.val();\r\
    \n                    auto na2 = mod2 - a2;\r\n                    a[i + offset]\
    \ = a0 + a2 + a1 + a3;\r\n                    a[i + offset + 1 * p] = a0 + a2\
    \ + (2 * mod2 - (a1 + a3));\r\n                    a[i + offset + 2 * p] = a0\
    \ + na2 + a1na3imag;\r\n                    a[i + offset + 3 * p] = a0 + na2 +\
    \ (mod2 - a1na3imag);\r\n                }\r\n                if (s + 1 != (1\
    \ << len)) rot *= info.rate3[countr_zero(~(unsigned int)(s))];\r\n           \
    \ }\r\n            len += 2;\r\n        }\r\n    }\r\n}\r\n\r\ntemplate <class\
    \ mint, internal::is_static_modint_t<mint> * = nullptr>\r\nvoid butterfly_inv(std::vector<mint>\
    \ &a) {\r\n    int n = int(a.size());\r\n    int h = internal::countr_zero((unsigned\
    \ int)n);\r\n\r\n    static const fft_info<mint> info;\r\n\r\n    int len = h;\
    \  // a[i, i+(n>>len), i+2*(n>>len), ..] is transformed\r\n    while (len) {\r\
    \n        if (len == 1) {\r\n            int p = 1 << (h - len);\r\n         \
    \   mint irot = 1;\r\n            for (int s = 0; s < (1 << (len - 1)); s++) {\r\
    \n                int offset = s << (h - len + 1);\r\n                for (int\
    \ i = 0; i < p; i++) {\r\n                    auto l = a[i + offset];\r\n    \
    \                auto r = a[i + offset + p];\r\n                    a[i + offset]\
    \ = l + r;\r\n                    a[i + offset + p] =\r\n                    \
    \    (std::uint64_t)(mint::mod() + l.val() - r.val()) * irot.val();\r\n      \
    \              ;\r\n                }\r\n                if (s + 1 != (1 << (len\
    \ - 1))) irot *= info.irate2[countr_zero(~(unsigned int)(s))];\r\n           \
    \ }\r\n            len--;\r\n        } else {\r\n            // 4-base\r\n   \
    \         int p = 1 << (h - len);\r\n            mint irot = 1, iimag = info.iroot[2];\r\
    \n            for (int s = 0; s < (1 << (len - 2)); s++) {\r\n               \
    \ mint irot2 = irot * irot;\r\n                mint irot3 = irot2 * irot;\r\n\
    \                int offset = s << (h - len + 2);\r\n                for (int\
    \ i = 0; i < p; i++) {\r\n                    auto a0 = 1ULL * a[i + offset +\
    \ 0 * p].val();\r\n                    auto a1 = 1ULL * a[i + offset + 1 * p].val();\r\
    \n                    auto a2 = 1ULL * a[i + offset + 2 * p].val();\r\n      \
    \              auto a3 = 1ULL * a[i + offset + 3 * p].val();\r\n\r\n         \
    \           auto a2na3iimag = 1ULL * mint((mint::mod() + a2 - a3) * iimag.val()).val();\r\
    \n\r\n                    a[i + offset] = a0 + a1 + a2 + a3;\r\n             \
    \       a[i + offset + 1 * p] = (a0 + (mint::mod() - a1) + a2na3iimag) * irot.val();\r\
    \n                    a[i + offset + 2 * p] =\r\n                        (a0 +\
    \ a1 + (mint::mod() - a2) + (mint::mod() - a3)) * irot2.val();\r\n           \
    \         a[i + offset + 3 * p] =\r\n                        (a0 + (mint::mod()\
    \ - a1) + (mint::mod() - a2na3iimag)) * irot3.val();\r\n                }\r\n\
    \                if (s + 1 != (1 << (len - 2))) irot *= info.irate3[countr_zero(~(unsigned\
    \ int)(s))];\r\n            }\r\n            len -= 2;\r\n        }\r\n    }\r\
    \n}\r\n\r\ntemplate <class mint, internal::is_static_modint_t<mint> * = nullptr>\r\
    \nstd::vector<mint> convolution_naive(const std::vector<mint> &a, const std::vector<mint>\
    \ &b) {\r\n    int n = int(a.size()), m = int(b.size());\r\n    std::vector<mint>\
    \ ans(n + m - 1);\r\n    if (n < m) {\r\n        for (int j = 0; j < m; j++) {\r\
    \n            for (int i = 0; i < n; i++) {\r\n                ans[i + j] += a[i]\
    \ * b[j];\r\n            }\r\n        }\r\n    } else {\r\n        for (int i\
    \ = 0; i < n; i++) {\r\n            for (int j = 0; j < m; j++) {\r\n        \
    \        ans[i + j] += a[i] * b[j];\r\n            }\r\n        }\r\n    }\r\n\
    \    return ans;\r\n}\r\n\r\ntemplate <class mint, internal::is_static_modint_t<mint>\
    \ * = nullptr>\r\nstd::vector<mint> convolution_fft(std::vector<mint> a, std::vector<mint>\
    \ b) {\r\n    int n = int(a.size()), m = int(b.size());\r\n    int z = (int)internal::bit_ceil((unsigned\
    \ int)(n + m - 1));\r\n    a.resize(z);\r\n    internal::butterfly(a);\r\n   \
    \ b.resize(z);\r\n    internal::butterfly(b);\r\n    for (int i = 0; i < z; i++)\
    \ {\r\n        a[i] *= b[i];\r\n    }\r\n    internal::butterfly_inv(a);\r\n \
    \   a.resize(n + m - 1);\r\n    mint iz = mint(z).inv();\r\n    for (int i = 0;\
    \ i < n + m - 1; i++) a[i] *= iz;\r\n    return a;\r\n}\r\n\r\n}  // namespace\
    \ internal\r\n\r\ntemplate <class mint, internal::is_static_modint_t<mint> * =\
    \ nullptr>\r\nstd::vector<mint> convolution(std::vector<mint> &&a, std::vector<mint>\
    \ &&b) {\r\n    int n = int(a.size()), m = int(b.size());\r\n    if (!n || !m)\
    \ return {};\r\n\r\n    int z = (int)internal::bit_ceil((unsigned int)(n + m -\
    \ 1));\r\n    assert((mint::mod() - 1) % z == 0);\r\n\r\n    if (std::min(n, m)\
    \ <= 60) return convolution_naive(a, b);\r\n    return internal::convolution_fft(a,\
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
  - lib/internal/internal_bit.hpp
  - lib/template/template.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/math/modint.hpp
  isVerificationFile: false
  path: lib/fft/ntt.hpp
  requiredBy:
  - lib/fft/ntt_mod.hpp
  - lib/fft/formal_power_series.hpp
  - lib/data_structure/bigint.hpp
  timestamp: '2023-05-24 16:19:45+09:00'
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
documentation_of: lib/fft/ntt.hpp
layout: document
redirect_from:
- /library/lib/fft/ntt.hpp
- /library/lib/fft/ntt.hpp.html
title: lib/fft/ntt.hpp
---
