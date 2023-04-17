---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: modint
  - icon: ':heavy_check_mark:'
    path: lib/math/pow.hpp
    title: lib/math/pow.hpp
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
  - icon: ':warning:'
    path: lib/fft/ntt_mod.hpp
    title: "\u4EFB\u610Fmod\u6570\u8AD6\u5909\u63DB"
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
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6570\u8AD6\u5909\u63DB"
    links:
    - https://hcpc-hokudai.github.io/archive/math_fft_002.pdf
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: math/modint.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"math/modint.hpp\"\r\n#include \"math/pow.hpp\"\
    \r\n#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u6570\u8AD6\u5909\
    \u63DB\r\n * @see https://hcpc-hokudai.github.io/archive/math_fft_002.pdf\r\n\
    \ *\r\n * @tparam mod \u6CD5\r\n * @tparam primitive_root \u539F\u59CB\u6839\r\
    \n */\r\ntemplate <int mod = MOD_N, int primitive_root = 3>\r\nstruct NTT {\r\n\
    \    using mint = ModInt<mod>;\r\n    static constexpr int get_mod() { return\
    \ mod; }\r\n\r\n    template <class T, class U>\r\n    static void convolution_self(std::vector<T>\
    \ &a, std::vector<U> b) {\r\n        int n = a.size() + b.size() - 1;\r\n    \
    \    int N = 1 << ceil_pow2(n);\r\n        a.resize(N), b.resize(N);\r\n\r\n \
    \       _ntt(a, false), _ntt(b, false);\r\n\r\n        for (int i = 0; i < N;\
    \ ++i) a[i] = T(1LL * a[i] * b[i] % mod);\r\n\r\n        _ntt(a, true);\r\n  \
    \      a.resize(n);\r\n    }\r\n\r\n    template <class T, class U>\r\n    static\
    \ std::vector<T> convolution(const std::vector<T> &a, const std::vector<U> &b)\
    \ {\r\n        std::vector<T> res = a;\r\n        convolution_self(res, b);\r\n\
    \        return res;\r\n    }\r\n\r\n  private:\r\n    template <class T>\r\n\
    \    static void _ntt(std::vector<T> &a, bool inv) {\r\n        int N = a.size();\r\
    \n        static bool is_first = true;\r\n        static std::array<mint, 30>\
    \ vbw, vibw;\r\n        if (is_first) {\r\n            is_first = false;\r\n \
    \           for (int i = 0; i < 30; ++i) {\r\n                vbw[i] = mint(primitive_root).pow((mod\
    \ - 1) >> (i + 1));\r\n                vibw[i] = vbw[i].inverse();\r\n       \
    \     }\r\n        }\r\n        for (int i = 0, j = 1; j < N - 1; ++j) {\r\n \
    \           for (int k = N >> 1; k > (i ^= k); k >>= 1)\r\n                ;\r\
    \n            if (i > j) swap(a[i], a[j]);\r\n        }\r\n        for (int k\
    \ = 0, t = 1; t < N; ++k, t <<= 1) {\r\n            mint bw = vbw[k];\r\n    \
    \        if (inv) bw = vibw[k];\r\n            for (int i = 0; i < N; i += t *\
    \ 2) {\r\n                mint w = 1;\r\n                for (int j = 0; j < t;\
    \ ++j) {\r\n                    int l = i + j, r = i + j + t;\r\n            \
    \        mint c = a[l], d = w * a[r];\r\n                    a[l] = int(c + d);\r\
    \n                    a[r] = int(c - d);\r\n                    w *= bw;\r\n \
    \               }\r\n            }\r\n        }\r\n        if (inv) {\r\n    \
    \        int m = int(mint(N).inverse());\r\n            for (int i = 0; i < N;\
    \ ++i) a[i] = T(1LL * a[i] * m % mod);\r\n        }\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/math/modint.hpp
  - lib/template/template.hpp
  - lib/math/pow.hpp
  isVerificationFile: false
  path: lib/fft/ntt.hpp
  requiredBy:
  - lib/data_structure/bigint.hpp
  - lib/fft/formal_power_series.hpp
  - lib/fft/ntt_mod.hpp
  timestamp: '2022-07-31 15:35:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/convolution/convolution.test.cpp
  - test/aoj/ntl/addition.test.cpp
  - test/aoj/ntl/multiplication.test.cpp
  - test/aoj/ntl/division.test.cpp
  - test/aoj/ntl/difference.test.cpp
  - test/aoj/ntl/remainder.test.cpp
  - test/aoj/ntl/multiplication2.test.cpp
documentation_of: lib/fft/ntt.hpp
layout: document
redirect_from:
- /library/lib/fft/ntt.hpp
- /library/lib/fft/ntt.hpp.html
title: "\u6570\u8AD6\u5909\u63DB"
---
