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
    path: lib/fft/ntt.hpp
    title: "\u7573\u307F\u8FBC\u307F"
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
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: internal/internal_bit.hpp:\
    \ line -1: no such header\n"
  code: "#include \"internal/internal_bit.hpp\"\n#include \"internal/internal_math.hpp\"\
    \n#include \"internal/internal_type_traits.hpp\"\n#include \"math/modint.hpp\"\
    \n#include \"template/template.hpp\"\n\nnamespace internal {\n\ntemplate <class\
    \ mint, int g = internal::primitive_root<mint::mod()>,\n          internal::is_static_modint_t<mint>\
    \ * = nullptr>\nstruct fft_info {\n    static constexpr int rank2 = countr_zero_constexpr(mint::mod()\
    \ - 1);\n    std::array<mint, rank2 + 1> root, iroot;\n    std::array<mint, std::max(0,\
    \ rank2 - 2 + 1)> rate2, irate2;\n    std::array<mint, std::max(0, rank2 - 3 +\
    \ 1)> rate3, irate3;\n\n    fft_info() {\n        root[rank2] = mint(g).pow((mint::mod()\
    \ - 1) >> rank2);\n        iroot[rank2] = root[rank2].inv();\n        for (int\
    \ i = rank2 - 1; i >= 0; i--) {\n            root[i] = root[i + 1] * root[i +\
    \ 1];\n            iroot[i] = iroot[i + 1] * iroot[i + 1];\n        }\n\n    \
    \    {\n            mint prod = 1, iprod = 1;\n            for (int i = 0; i <=\
    \ rank2 - 2; i++) {\n                rate2[i] = root[i + 2] * prod;\n        \
    \        irate2[i] = iroot[i + 2] * iprod;\n                prod *= iroot[i +\
    \ 2];\n                iprod *= root[i + 2];\n            }\n        }\n     \
    \   {\n            mint prod = 1, iprod = 1;\n            for (int i = 0; i <=\
    \ rank2 - 3; i++) {\n                rate3[i] = root[i + 3] * prod;\n        \
    \        irate3[i] = iroot[i + 3] * iprod;\n                prod *= iroot[i +\
    \ 3];\n                iprod *= root[i + 3];\n            }\n        }\n    }\n\
    };\n\ntemplate <class mint, internal::is_static_modint_t<mint> * = nullptr>\n\
    void butterfly(std::vector<mint> &a) {\n    int n = int(a.size());\n    int h\
    \ = internal::countr_zero((unsigned int)n);\n    static const fft_info<mint> info;\n\
    \    int len = 0;\n    while (len < h) {\n        if (h - len == 1) {\n      \
    \      int p = 1 << (h - len - 1);\n            mint rot = 1;\n            for\
    \ (int s = 0; s < (1 << len); s++) {\n                int offset = s << (h - len);\n\
    \                for (int i = 0; i < p; i++) {\n                    auto l = a[i\
    \ + offset], r = a[i + offset + p] * rot;\n                    a[i + offset] =\
    \ l + r, a[i + offset + p] = l - r;\n                }\n                if (s\
    \ + 1 != (1 << len)) rot *= info.rate2[countr_zero(~(unsigned int)(s))];\n   \
    \         }\n            len++;\n        } else {\n            int p = 1 << (h\
    \ - len - 2);\n            mint rot = 1, imag = info.root[2];\n            for\
    \ (int s = 0; s < (1 << len); s++) {\n                mint rot2 = rot * rot;\n\
    \                mint rot3 = rot2 * rot;\n                int offset = s << (h\
    \ - len);\n                for (int i = 0; i < p; i++) {\n                   \
    \ auto mod2 = 1ULL * mint::mod() * mint::mod();\n                    auto a0 =\
    \ 1ULL * a[i + offset].val();\n                    auto a1 = 1ULL * a[i + offset\
    \ + p].val() * rot.val();\n                    auto a2 = 1ULL * a[i + offset +\
    \ 2 * p].val() * rot2.val();\n                    auto a3 = 1ULL * a[i + offset\
    \ + 3 * p].val() * rot3.val();\n                    auto a1na3imag = 1ULL * mint(a1\
    \ + mod2 - a3).val() * imag.val();\n                    auto na2 = mod2 - a2;\n\
    \                    a[i + offset] = a0 + a2 + a1 + a3;\n                    a[i\
    \ + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));\n                    a[i\
    \ + offset + 2 * p] = a0 + na2 + a1na3imag;\n                    a[i + offset\
    \ + 3 * p] = a0 + na2 + (mod2 - a1na3imag);\n                }\n             \
    \   if (s + 1 != (1 << len)) rot *= info.rate3[countr_zero(~(unsigned int)(s))];\n\
    \            }\n            len += 2;\n        }\n    }\n}\n\ntemplate <class\
    \ mint, internal::is_static_modint_t<mint> * = nullptr>\nvoid butterfly_inv(std::vector<mint>\
    \ &a) {\n    int n = int(a.size());\n    int h = internal::countr_zero((unsigned\
    \ int)n);\n\n    static const fft_info<mint> info;\n\n    int len = h;\n    while\
    \ (len) {\n        if (len == 1) {\n            int p = 1 << (h - len);\n    \
    \        mint irot = 1;\n            for (int s = 0; s < (1 << (len - 1)); s++)\
    \ {\n                int offset = s << (h - len + 1);\n                for (int\
    \ i = 0; i < p; i++) {\n                    auto l = a[i + offset], r = a[i +\
    \ offset + p];\n                    a[i + offset] = l + r;\n                 \
    \   a[i + offset + p] =\n                        (std::uint64_t)(mint::mod() +\
    \ l.val() - r.val()) * irot.val();\n                    ;\n                }\n\
    \                if (s + 1 != (1 << (len - 1))) irot *= info.irate2[countr_zero(~(unsigned\
    \ int)(s))];\n            }\n            len--;\n        } else {\n          \
    \  int p = 1 << (h - len);\n            mint irot = 1, iimag = info.iroot[2];\n\
    \            for (int s = 0; s < (1 << (len - 2)); s++) {\n                mint\
    \ irot2 = irot * irot;\n                mint irot3 = irot2 * irot;\n         \
    \       int offset = s << (h - len + 2);\n                for (int i = 0; i <\
    \ p; i++) {\n                    auto a0 = 1ULL * a[i + offset + 0 * p].val();\n\
    \                    auto a1 = 1ULL * a[i + offset + 1 * p].val();\n         \
    \           auto a2 = 1ULL * a[i + offset + 2 * p].val();\n                  \
    \  auto a3 = 1ULL * a[i + offset + 3 * p].val();\n\n                    auto a2na3iimag\
    \ = 1ULL * mint((mint::mod() + a2 - a3) * iimag.val()).val();\n\n            \
    \        a[i + offset] = a0 + a1 + a2 + a3;\n                    a[i + offset\
    \ + 1 * p] = (a0 + (mint::mod() - a1) + a2na3iimag) * irot.val();\n          \
    \          a[i + offset + 2 * p] =\n                        (a0 + a1 + (mint::mod()\
    \ - a2) + (mint::mod() - a3)) * irot2.val();\n                    a[i + offset\
    \ + 3 * p] =\n                        (a0 + (mint::mod() - a1) + (mint::mod()\
    \ - a2na3iimag)) * irot3.val();\n                }\n                if (s + 1\
    \ != (1 << (len - 2))) irot *= info.irate3[countr_zero(~(unsigned int)(s))];\n\
    \            }\n            len -= 2;\n        }\n    }\n}\n\ntemplate <class\
    \ mint, internal::is_static_modint_t<mint> * = nullptr>\nstd::vector<mint> convolution_naive(const\
    \ std::vector<mint> &a, const std::vector<mint> &b) {\n    int n = int(a.size()),\
    \ m = int(b.size());\n    std::vector<mint> ans(n + m - 1);\n    if (n < m) {\n\
    \        for (int j = 0; j < m; j++) {\n            for (int i = 0; i < n; i++)\
    \ ans[i + j] += a[i] * b[j];\n        }\n    } else {\n        for (int i = 0;\
    \ i < n; i++) {\n            for (int j = 0; j < m; j++) ans[i + j] += a[i] *\
    \ b[j];\n        }\n    }\n    return ans;\n}\n\ntemplate <class mint, internal::is_static_modint_t<mint>\
    \ * = nullptr>\nstd::vector<mint> convolution_fft(std::vector<mint> a, std::vector<mint>\
    \ b) {\n    int n = int(a.size()), m = int(b.size());\n    int z = (int)internal::bit_ceil((unsigned\
    \ int)(n + m - 1));\n    a.resize(z);\n    internal::butterfly(a);\n    b.resize(z);\n\
    \    internal::butterfly(b);\n    for (int i = 0; i < z; i++) { a[i] *= b[i];\
    \ }\n    internal::butterfly_inv(a);\n    a.resize(n + m - 1);\n    mint iz =\
    \ mint(z).inv();\n    for (int i = 0; i < n + m - 1; i++) a[i] *= iz;\n    return\
    \ a;\n}\n\n}  // namespace internal\n"
  dependsOn:
  - lib/internal/internal_bit.hpp
  - lib/internal/internal_math.hpp
  - lib/internal/internal_type_traits.hpp
  - lib/math/modint.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/internal/internal_fft.hpp
  requiredBy:
  - lib/data_structure/bigint.hpp
  - lib/fft/formal_power_series.hpp
  - lib/fft/ntt_mod.hpp
  - lib/fft/ntt.hpp
  timestamp: '2024-04-17 14:43:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/convolution/convolution.test.cpp
  - test/yosupo/convolution/convolution_mod.test.cpp
  - test/yosupo/data_structure/addition_of_big_integers.test.cpp
  - test/aoj/ntl/multiplication2.test.cpp
  - test/aoj/ntl/division.test.cpp
  - test/aoj/ntl/remainder.test.cpp
  - test/aoj/ntl/difference.test.cpp
  - test/aoj/ntl/multiplication.test.cpp
  - test/aoj/ntl/addition.test.cpp
documentation_of: lib/internal/internal_fft.hpp
layout: document
redirect_from:
- /library/lib/internal/internal_fft.hpp
- /library/lib/internal/internal_fft.hpp.html
title: lib/internal/internal_fft.hpp
---
