---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: lib/atcoder/internal_bit.hpp
    title: lib/atcoder/internal_bit.hpp
  - icon: ':warning:'
    path: lib/atcoder/internal_math.hpp
    title: lib/atcoder/internal_math.hpp
  - icon: ':warning:'
    path: lib/atcoder/internal_type_traits.hpp
    title: lib/atcoder/internal_type_traits.hpp
  - icon: ':warning:'
    path: lib/atcoder/modint.hpp
    title: lib/atcoder/modint.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/atcoder/convolution.hpp\"\n\n\n\r\n#include <algorithm>\r\
    \n#include <array>\r\n#include <atcoder/internal_bit>\r\n#include <atcoder/modint>\r\
    \n#include <cassert>\r\n#include <type_traits>\r\n#include <vector>\r\n\r\nnamespace\
    \ atcoder {\r\n\r\nnamespace internal {\r\n\r\ntemplate <class mint, internal::is_static_modint_t<mint>*\
    \ = nullptr>\r\nvoid butterfly(std::vector<mint>& a) {\r\n    static constexpr\
    \ int g = internal::primitive_root<mint::mod()>;\r\n    int n = int(a.size());\r\
    \n    int h = internal::ceil_pow2(n);\r\n\r\n    static bool first = true;\r\n\
    \    static mint sum_e[30];  // sum_e[i] = ies[0] * ... * ies[i - 1] * es[i]\r\
    \n    if (first) {\r\n        first = false;\r\n        mint es[30], ies[30];\
    \  // es[i]^(2^(2+i)) == 1\r\n        int cnt2 = bsf(mint::mod() - 1);\r\n   \
    \     mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();\r\n     \
    \   for (int i = cnt2; i >= 2; i--) {\r\n            // e^(2^i) == 1\r\n     \
    \       es[i - 2] = e;\r\n            ies[i - 2] = ie;\r\n            e *= e;\r\
    \n            ie *= ie;\r\n        }\r\n        mint now = 1;\r\n        for (int\
    \ i = 0; i < cnt2 - 2; i++) {\r\n            sum_e[i] = es[i] * now;\r\n     \
    \       now *= ies[i];\r\n        }\r\n    }\r\n    for (int ph = 1; ph <= h;\
    \ ph++) {\r\n        int w = 1 << (ph - 1), p = 1 << (h - ph);\r\n        mint\
    \ now = 1;\r\n        for (int s = 0; s < w; s++) {\r\n            int offset\
    \ = s << (h - ph + 1);\r\n            for (int i = 0; i < p; i++) {\r\n      \
    \          auto l = a[i + offset];\r\n                auto r = a[i + offset +\
    \ p] * now;\r\n                a[i + offset] = l + r;\r\n                a[i +\
    \ offset + p] = l - r;\r\n            }\r\n            now *= sum_e[bsf(~(unsigned\
    \ int)(s))];\r\n        }\r\n    }\r\n}\r\n\r\ntemplate <class mint, internal::is_static_modint_t<mint>*\
    \ = nullptr>\r\nvoid butterfly_inv(std::vector<mint>& a) {\r\n    static constexpr\
    \ int g = internal::primitive_root<mint::mod()>;\r\n    int n = int(a.size());\r\
    \n    int h = internal::ceil_pow2(n);\r\n\r\n    static bool first = true;\r\n\
    \    static mint sum_ie[30];  // sum_ie[i] = es[0] * ... * es[i - 1] * ies[i]\r\
    \n    if (first) {\r\n        first = false;\r\n        mint es[30], ies[30];\
    \  // es[i]^(2^(2+i)) == 1\r\n        int cnt2 = bsf(mint::mod() - 1);\r\n   \
    \     mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();\r\n     \
    \   for (int i = cnt2; i >= 2; i--) {\r\n            // e^(2^i) == 1\r\n     \
    \       es[i - 2] = e;\r\n            ies[i - 2] = ie;\r\n            e *= e;\r\
    \n            ie *= ie;\r\n        }\r\n        mint now = 1;\r\n        for (int\
    \ i = 0; i < cnt2 - 2; i++) {\r\n            sum_ie[i] = ies[i] * now;\r\n   \
    \         now *= es[i];\r\n        }\r\n    }\r\n\r\n    for (int ph = h; ph >=\
    \ 1; ph--) {\r\n        int w = 1 << (ph - 1), p = 1 << (h - ph);\r\n        mint\
    \ inow = 1;\r\n        for (int s = 0; s < w; s++) {\r\n            int offset\
    \ = s << (h - ph + 1);\r\n            for (int i = 0; i < p; i++) {\r\n      \
    \          auto l = a[i + offset];\r\n                auto r = a[i + offset +\
    \ p];\r\n                a[i + offset] = l + r;\r\n                a[i + offset\
    \ + p] =\r\n                    (unsigned long long)(mint::mod() + l.val() - r.val())\
    \ *\r\n                    inow.val();\r\n            }\r\n            inow *=\
    \ sum_ie[bsf(~(unsigned int)(s))];\r\n        }\r\n    }\r\n}\r\n\r\n}  // namespace\
    \ internal\r\n\r\ntemplate <class mint, internal::is_static_modint_t<mint>* =\
    \ nullptr>\r\nstd::vector<mint> convolution(std::vector<mint> a, std::vector<mint>\
    \ b) {\r\n    int n = int(a.size()), m = int(b.size());\r\n    if (!n || !m) return\
    \ {};\r\n    if (std::min(n, m) <= 60) {\r\n        if (n < m) {\r\n         \
    \   std::swap(n, m);\r\n            std::swap(a, b);\r\n        }\r\n        std::vector<mint>\
    \ ans(n + m - 1);\r\n        for (int i = 0; i < n; i++) {\r\n            for\
    \ (int j = 0; j < m; j++) {\r\n                ans[i + j] += a[i] * b[j];\r\n\
    \            }\r\n        }\r\n        return ans;\r\n    }\r\n    int z = 1 <<\
    \ internal::ceil_pow2(n + m - 1);\r\n    a.resize(z);\r\n    internal::butterfly(a);\r\
    \n    b.resize(z);\r\n    internal::butterfly(b);\r\n    for (int i = 0; i < z;\
    \ i++) {\r\n        a[i] *= b[i];\r\n    }\r\n    internal::butterfly_inv(a);\r\
    \n    a.resize(n + m - 1);\r\n    mint iz = mint(z).inv();\r\n    for (int i =\
    \ 0; i < n + m - 1; i++) a[i] *= iz;\r\n    return a;\r\n}\r\n\r\ntemplate <unsigned\
    \ int mod = 998244353,\r\n          class T,\r\n          std::enable_if_t<internal::is_integral<T>::value>*\
    \ = nullptr>\r\nstd::vector<T> convolution(const std::vector<T>& a, const std::vector<T>&\
    \ b) {\r\n    int n = int(a.size()), m = int(b.size());\r\n    if (!n || !m) return\
    \ {};\r\n\r\n    using mint = static_modint<mod>;\r\n    std::vector<mint> a2(n),\
    \ b2(m);\r\n    for (int i = 0; i < n; i++) {\r\n        a2[i] = mint(a[i]);\r\
    \n    }\r\n    for (int i = 0; i < m; i++) {\r\n        b2[i] = mint(b[i]);\r\n\
    \    }\r\n    auto c2 = convolution(move(a2), move(b2));\r\n    std::vector<T>\
    \ c(n + m - 1);\r\n    for (int i = 0; i < n + m - 1; i++) {\r\n        c[i] =\
    \ c2[i].val();\r\n    }\r\n    return c;\r\n}\r\n\r\nstd::vector<long long> convolution_ll(const\
    \ std::vector<long long>& a,\r\n                                      const std::vector<long\
    \ long>& b) {\r\n    int n = int(a.size()), m = int(b.size());\r\n    if (!n ||\
    \ !m) return {};\r\n\r\n    static constexpr unsigned long long MOD1 = 754974721;\
    \  // 2^24\r\n    static constexpr unsigned long long MOD2 = 167772161;  // 2^25\r\
    \n    static constexpr unsigned long long MOD3 = 469762049;  // 2^26\r\n    static\
    \ constexpr unsigned long long M2M3 = MOD2 * MOD3;\r\n    static constexpr unsigned\
    \ long long M1M3 = MOD1 * MOD3;\r\n    static constexpr unsigned long long M1M2\
    \ = MOD1 * MOD2;\r\n    static constexpr unsigned long long M1M2M3 = MOD1 * MOD2\
    \ * MOD3;\r\n\r\n    static constexpr unsigned long long i1 =\r\n        internal::inv_gcd(MOD2\
    \ * MOD3, MOD1).second;\r\n    static constexpr unsigned long long i2 =\r\n  \
    \      internal::inv_gcd(MOD1 * MOD3, MOD2).second;\r\n    static constexpr unsigned\
    \ long long i3 =\r\n        internal::inv_gcd(MOD1 * MOD2, MOD3).second;\r\n\r\
    \n    auto c1 = convolution<MOD1>(a, b);\r\n    auto c2 = convolution<MOD2>(a,\
    \ b);\r\n    auto c3 = convolution<MOD3>(a, b);\r\n\r\n    std::vector<long long>\
    \ c(n + m - 1);\r\n    for (int i = 0; i < n + m - 1; i++) {\r\n        unsigned\
    \ long long x = 0;\r\n        x += (c1[i] * i1) % MOD1 * M2M3;\r\n        x +=\
    \ (c2[i] * i2) % MOD2 * M1M3;\r\n        x += (c3[i] * i3) % MOD3 * M1M2;\r\n\
    \        // B = 2^63, -B <= x, r(real value) < B\r\n        // (x, x - M, x -\
    \ 2M, or x - 3M) = r (mod 2B)\r\n        // r = c1[i] (mod MOD1)\r\n        //\
    \ focus on MOD1\r\n        // r = x, x - M', x - 2M', x - 3M' (M' = M % 2^64)\
    \ (mod 2B)\r\n        // r = x,\r\n        //     x - M' + (0 or 2B),\r\n    \
    \    //     x - 2M' + (0, 2B or 4B),\r\n        //     x - 3M' + (0, 2B, 4B or\
    \ 6B) (without mod!)\r\n        // (r - x) = 0, (0)\r\n        //           -\
    \ M' + (0 or 2B), (1)\r\n        //           -2M' + (0 or 2B or 4B), (2)\r\n\
    \        //           -3M' + (0 or 2B or 4B or 6B) (3) (mod MOD1)\r\n        //\
    \ we checked that\r\n        //   ((1) mod MOD1) mod 5 = 2\r\n        //   ((2)\
    \ mod MOD1) mod 5 = 3\r\n        //   ((3) mod MOD1) mod 5 = 4\r\n        long\
    \ long diff =\r\n            c1[i] - internal::safe_mod((long long)(x), (long\
    \ long)(MOD1));\r\n        if (diff < 0) diff += MOD1;\r\n        static constexpr\
    \ unsigned long long offset[5] = {\r\n            0, 0, M1M2M3, 2 * M1M2M3, 3\
    \ * M1M2M3};\r\n        x -= offset[diff % 5];\r\n        c[i] = x;\r\n    }\r\
    \n\r\n    return c;\r\n}\r\n\r\n}  // namespace atcoder\r\n\r\n\n"
  code: "#ifndef ATCODER_CONVOLUTION_HPP\r\n#define ATCODER_CONVOLUTION_HPP 1\r\n\r\
    \n#include <algorithm>\r\n#include <array>\r\n#include <atcoder/internal_bit>\r\
    \n#include <atcoder/modint>\r\n#include <cassert>\r\n#include <type_traits>\r\n\
    #include <vector>\r\n\r\nnamespace atcoder {\r\n\r\nnamespace internal {\r\n\r\
    \ntemplate <class mint, internal::is_static_modint_t<mint>* = nullptr>\r\nvoid\
    \ butterfly(std::vector<mint>& a) {\r\n    static constexpr int g = internal::primitive_root<mint::mod()>;\r\
    \n    int n = int(a.size());\r\n    int h = internal::ceil_pow2(n);\r\n\r\n  \
    \  static bool first = true;\r\n    static mint sum_e[30];  // sum_e[i] = ies[0]\
    \ * ... * ies[i - 1] * es[i]\r\n    if (first) {\r\n        first = false;\r\n\
    \        mint es[30], ies[30];  // es[i]^(2^(2+i)) == 1\r\n        int cnt2 =\
    \ bsf(mint::mod() - 1);\r\n        mint e = mint(g).pow((mint::mod() - 1) >> cnt2),\
    \ ie = e.inv();\r\n        for (int i = cnt2; i >= 2; i--) {\r\n            //\
    \ e^(2^i) == 1\r\n            es[i - 2] = e;\r\n            ies[i - 2] = ie;\r\
    \n            e *= e;\r\n            ie *= ie;\r\n        }\r\n        mint now\
    \ = 1;\r\n        for (int i = 0; i < cnt2 - 2; i++) {\r\n            sum_e[i]\
    \ = es[i] * now;\r\n            now *= ies[i];\r\n        }\r\n    }\r\n    for\
    \ (int ph = 1; ph <= h; ph++) {\r\n        int w = 1 << (ph - 1), p = 1 << (h\
    \ - ph);\r\n        mint now = 1;\r\n        for (int s = 0; s < w; s++) {\r\n\
    \            int offset = s << (h - ph + 1);\r\n            for (int i = 0; i\
    \ < p; i++) {\r\n                auto l = a[i + offset];\r\n                auto\
    \ r = a[i + offset + p] * now;\r\n                a[i + offset] = l + r;\r\n \
    \               a[i + offset + p] = l - r;\r\n            }\r\n            now\
    \ *= sum_e[bsf(~(unsigned int)(s))];\r\n        }\r\n    }\r\n}\r\n\r\ntemplate\
    \ <class mint, internal::is_static_modint_t<mint>* = nullptr>\r\nvoid butterfly_inv(std::vector<mint>&\
    \ a) {\r\n    static constexpr int g = internal::primitive_root<mint::mod()>;\r\
    \n    int n = int(a.size());\r\n    int h = internal::ceil_pow2(n);\r\n\r\n  \
    \  static bool first = true;\r\n    static mint sum_ie[30];  // sum_ie[i] = es[0]\
    \ * ... * es[i - 1] * ies[i]\r\n    if (first) {\r\n        first = false;\r\n\
    \        mint es[30], ies[30];  // es[i]^(2^(2+i)) == 1\r\n        int cnt2 =\
    \ bsf(mint::mod() - 1);\r\n        mint e = mint(g).pow((mint::mod() - 1) >> cnt2),\
    \ ie = e.inv();\r\n        for (int i = cnt2; i >= 2; i--) {\r\n            //\
    \ e^(2^i) == 1\r\n            es[i - 2] = e;\r\n            ies[i - 2] = ie;\r\
    \n            e *= e;\r\n            ie *= ie;\r\n        }\r\n        mint now\
    \ = 1;\r\n        for (int i = 0; i < cnt2 - 2; i++) {\r\n            sum_ie[i]\
    \ = ies[i] * now;\r\n            now *= es[i];\r\n        }\r\n    }\r\n\r\n \
    \   for (int ph = h; ph >= 1; ph--) {\r\n        int w = 1 << (ph - 1), p = 1\
    \ << (h - ph);\r\n        mint inow = 1;\r\n        for (int s = 0; s < w; s++)\
    \ {\r\n            int offset = s << (h - ph + 1);\r\n            for (int i =\
    \ 0; i < p; i++) {\r\n                auto l = a[i + offset];\r\n            \
    \    auto r = a[i + offset + p];\r\n                a[i + offset] = l + r;\r\n\
    \                a[i + offset + p] =\r\n                    (unsigned long long)(mint::mod()\
    \ + l.val() - r.val()) *\r\n                    inow.val();\r\n            }\r\
    \n            inow *= sum_ie[bsf(~(unsigned int)(s))];\r\n        }\r\n    }\r\
    \n}\r\n\r\n}  // namespace internal\r\n\r\ntemplate <class mint, internal::is_static_modint_t<mint>*\
    \ = nullptr>\r\nstd::vector<mint> convolution(std::vector<mint> a, std::vector<mint>\
    \ b) {\r\n    int n = int(a.size()), m = int(b.size());\r\n    if (!n || !m) return\
    \ {};\r\n    if (std::min(n, m) <= 60) {\r\n        if (n < m) {\r\n         \
    \   std::swap(n, m);\r\n            std::swap(a, b);\r\n        }\r\n        std::vector<mint>\
    \ ans(n + m - 1);\r\n        for (int i = 0; i < n; i++) {\r\n            for\
    \ (int j = 0; j < m; j++) {\r\n                ans[i + j] += a[i] * b[j];\r\n\
    \            }\r\n        }\r\n        return ans;\r\n    }\r\n    int z = 1 <<\
    \ internal::ceil_pow2(n + m - 1);\r\n    a.resize(z);\r\n    internal::butterfly(a);\r\
    \n    b.resize(z);\r\n    internal::butterfly(b);\r\n    for (int i = 0; i < z;\
    \ i++) {\r\n        a[i] *= b[i];\r\n    }\r\n    internal::butterfly_inv(a);\r\
    \n    a.resize(n + m - 1);\r\n    mint iz = mint(z).inv();\r\n    for (int i =\
    \ 0; i < n + m - 1; i++) a[i] *= iz;\r\n    return a;\r\n}\r\n\r\ntemplate <unsigned\
    \ int mod = 998244353,\r\n          class T,\r\n          std::enable_if_t<internal::is_integral<T>::value>*\
    \ = nullptr>\r\nstd::vector<T> convolution(const std::vector<T>& a, const std::vector<T>&\
    \ b) {\r\n    int n = int(a.size()), m = int(b.size());\r\n    if (!n || !m) return\
    \ {};\r\n\r\n    using mint = static_modint<mod>;\r\n    std::vector<mint> a2(n),\
    \ b2(m);\r\n    for (int i = 0; i < n; i++) {\r\n        a2[i] = mint(a[i]);\r\
    \n    }\r\n    for (int i = 0; i < m; i++) {\r\n        b2[i] = mint(b[i]);\r\n\
    \    }\r\n    auto c2 = convolution(move(a2), move(b2));\r\n    std::vector<T>\
    \ c(n + m - 1);\r\n    for (int i = 0; i < n + m - 1; i++) {\r\n        c[i] =\
    \ c2[i].val();\r\n    }\r\n    return c;\r\n}\r\n\r\nstd::vector<long long> convolution_ll(const\
    \ std::vector<long long>& a,\r\n                                      const std::vector<long\
    \ long>& b) {\r\n    int n = int(a.size()), m = int(b.size());\r\n    if (!n ||\
    \ !m) return {};\r\n\r\n    static constexpr unsigned long long MOD1 = 754974721;\
    \  // 2^24\r\n    static constexpr unsigned long long MOD2 = 167772161;  // 2^25\r\
    \n    static constexpr unsigned long long MOD3 = 469762049;  // 2^26\r\n    static\
    \ constexpr unsigned long long M2M3 = MOD2 * MOD3;\r\n    static constexpr unsigned\
    \ long long M1M3 = MOD1 * MOD3;\r\n    static constexpr unsigned long long M1M2\
    \ = MOD1 * MOD2;\r\n    static constexpr unsigned long long M1M2M3 = MOD1 * MOD2\
    \ * MOD3;\r\n\r\n    static constexpr unsigned long long i1 =\r\n        internal::inv_gcd(MOD2\
    \ * MOD3, MOD1).second;\r\n    static constexpr unsigned long long i2 =\r\n  \
    \      internal::inv_gcd(MOD1 * MOD3, MOD2).second;\r\n    static constexpr unsigned\
    \ long long i3 =\r\n        internal::inv_gcd(MOD1 * MOD2, MOD3).second;\r\n\r\
    \n    auto c1 = convolution<MOD1>(a, b);\r\n    auto c2 = convolution<MOD2>(a,\
    \ b);\r\n    auto c3 = convolution<MOD3>(a, b);\r\n\r\n    std::vector<long long>\
    \ c(n + m - 1);\r\n    for (int i = 0; i < n + m - 1; i++) {\r\n        unsigned\
    \ long long x = 0;\r\n        x += (c1[i] * i1) % MOD1 * M2M3;\r\n        x +=\
    \ (c2[i] * i2) % MOD2 * M1M3;\r\n        x += (c3[i] * i3) % MOD3 * M1M2;\r\n\
    \        // B = 2^63, -B <= x, r(real value) < B\r\n        // (x, x - M, x -\
    \ 2M, or x - 3M) = r (mod 2B)\r\n        // r = c1[i] (mod MOD1)\r\n        //\
    \ focus on MOD1\r\n        // r = x, x - M', x - 2M', x - 3M' (M' = M % 2^64)\
    \ (mod 2B)\r\n        // r = x,\r\n        //     x - M' + (0 or 2B),\r\n    \
    \    //     x - 2M' + (0, 2B or 4B),\r\n        //     x - 3M' + (0, 2B, 4B or\
    \ 6B) (without mod!)\r\n        // (r - x) = 0, (0)\r\n        //           -\
    \ M' + (0 or 2B), (1)\r\n        //           -2M' + (0 or 2B or 4B), (2)\r\n\
    \        //           -3M' + (0 or 2B or 4B or 6B) (3) (mod MOD1)\r\n        //\
    \ we checked that\r\n        //   ((1) mod MOD1) mod 5 = 2\r\n        //   ((2)\
    \ mod MOD1) mod 5 = 3\r\n        //   ((3) mod MOD1) mod 5 = 4\r\n        long\
    \ long diff =\r\n            c1[i] - internal::safe_mod((long long)(x), (long\
    \ long)(MOD1));\r\n        if (diff < 0) diff += MOD1;\r\n        static constexpr\
    \ unsigned long long offset[5] = {\r\n            0, 0, M1M2M3, 2 * M1M2M3, 3\
    \ * M1M2M3};\r\n        x -= offset[diff % 5];\r\n        c[i] = x;\r\n    }\r\
    \n\r\n    return c;\r\n}\r\n\r\n}  // namespace atcoder\r\n\r\n#endif  // ATCODER_CONVOLUTION_HPP\r\
    \n"
  dependsOn:
  - lib/atcoder/internal_bit.hpp
  - lib/atcoder/modint.hpp
  - lib/atcoder/internal_math.hpp
  - lib/atcoder/internal_type_traits.hpp
  isVerificationFile: false
  path: lib/atcoder/convolution.hpp
  requiredBy: []
  timestamp: '2021-09-18 16:27:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/atcoder/convolution.hpp
layout: document
redirect_from:
- /library/lib/atcoder/convolution.hpp
- /library/lib/atcoder/convolution.hpp.html
title: lib/atcoder/convolution.hpp
---
