---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/data_structure/bigint.hpp
    title: lib/data_structure/bigint.hpp
  - icon: ':warning:'
    path: lib/data_structure/bigint_beta.hpp
    title: lib/data_structure/bigint_beta.hpp
  - icon: ':warning:'
    path: lib/fft/formal_power_series.hpp
    title: lib/fft/formal_power_series.hpp
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt.hpp
    title: lib/fft/ntt.hpp
  - icon: ':warning:'
    path: lib/fft/ntt_mod.hpp
    title: lib/fft/ntt_mod.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/combination.hpp
    title: lib/math/combination.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/enumeration.hpp
    title: lib/math/enumeration.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dp/bell.test.cpp
    title: test/aoj/dp/bell.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dp/stirling.test.cpp
    title: test/aoj/dp/stirling.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/power.test.cpp
    title: test/aoj/power.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution/convolution_mod.test.cpp
    title: test/yosupo/convolution/convolution_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: modint
    links:
    - https://github.com/ei1333/library/blob/master/math/combinatorics/mod-int.cpp
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief\
    \ modint\r\n * @ref https://github.com/ei1333/library/blob/master/math/combinatorics/mod-int.cpp\
    \ \"\u53C2\u8003\"\r\n *\r\n * @tparam mod \u6CD5\r\n */\r\n\r\ntemplate <int\
    \ mod>\r\nstruct ModInt {\r\n    int x;\r\n\r\n    constexpr ModInt() : x(0) {}\r\
    \n    constexpr ModInt(int64_t y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y\
    \ % mod)) {}\r\n\r\n    constexpr ModInt &operator+=(const ModInt &rhs) noexcept\
    \ {\r\n        if ((x += rhs.x) >= mod) x -= mod;\r\n        return *this;\r\n\
    \    }\r\n    constexpr ModInt &operator-=(const ModInt &rhs) noexcept {\r\n \
    \       if ((x += mod - rhs.x) >= mod) x -= mod;\r\n        return *this;\r\n\
    \    }\r\n    constexpr ModInt &operator*=(const ModInt &rhs) noexcept {\r\n \
    \       x = (int)(1LL * x * rhs.x % mod);\r\n        return *this;\r\n    }\r\n\
    \    constexpr ModInt &operator/=(const ModInt &rhs) noexcept {\r\n        *this\
    \ *= rhs.inverse();\r\n        return *this;\r\n    }\r\n\r\n    constexpr ModInt\
    \ &operator++() noexcept {\r\n        if ((++x) >= mod) x -= mod;\r\n        return\
    \ *this;\r\n    }\r\n    constexpr ModInt operator++(int) noexcept {\r\n     \
    \   ModInt tmp(*this);\r\n        operator++();\r\n        return tmp;\r\n   \
    \ }\r\n    constexpr ModInt &operator--() noexcept {\r\n        if ((x += mod\
    \ - 1) >= mod) x -= mod;\r\n        return *this;\r\n    }\r\n    constexpr ModInt\
    \ operator--(int) noexcept {\r\n        ModInt tmp(*this);\r\n        operator--();\r\
    \n        return tmp;\r\n    }\r\n\r\n    constexpr ModInt operator-() const noexcept\
    \ { return ModInt(-x); }\r\n    constexpr ModInt operator+(const ModInt &rhs)\
    \ const noexcept { return ModInt(*this) += rhs; }\r\n    constexpr ModInt operator-(const\
    \ ModInt &rhs) const noexcept { return ModInt(*this) -= rhs; }\r\n    constexpr\
    \ ModInt operator*(const ModInt &rhs) const noexcept { return ModInt(*this) *=\
    \ rhs; }\r\n    constexpr ModInt operator/(const ModInt &rhs) const noexcept {\
    \ return ModInt(*this) /= rhs; }\r\n\r\n    constexpr bool operator==(const ModInt\
    \ &rhs) const noexcept { return x == rhs.x; }\r\n    constexpr bool operator!=(const\
    \ ModInt &rhs) const noexcept { return x != rhs.x; }\r\n\r\n    constexpr ModInt\
    \ inverse() const noexcept {\r\n        int a = x, b = mod, u = 1, v = 0, t;\r\
    \n        while (b > 0) {\r\n            t = a / b;\r\n            swap(a -= t\
    \ * b, b);\r\n            swap(u -= t * v, v);\r\n        }\r\n        return\
    \ ModInt(u);\r\n    }\r\n\r\n    constexpr ModInt pow(int64_t n) const noexcept\
    \ { return ModInt(*this).pow_self(n); }\r\n    constexpr ModInt &pow_self(int64_t\
    \ n) noexcept {\r\n        ModInt res(1);\r\n        for (; n > 0; n >>= 1) {\r\
    \n            if (n & 1) res *= *this;\r\n            *this *= *this;\r\n    \
    \    }\r\n        *this = res;\r\n        return *this;\r\n    }\r\n\r\n    friend\
    \ istream &operator>>(istream &is, ModInt &rhs) {\r\n        int64_t t;\r\n  \
    \      is >> t;\r\n        rhs = ModInt<mod>(t);\r\n        return (is);\r\n \
    \   }\r\n    friend ostream &operator<<(ostream &os, const ModInt &rhs) { return\
    \ os << rhs.x; }\r\n\r\n    int to_int() const noexcept { return x; }\r\n\r\n\
    \    static int get_mod() noexcept { return mod; }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/modint.hpp
  requiredBy:
  - lib/data_structure/bigint_beta.hpp
  - lib/data_structure/bigint.hpp
  - lib/fft/ntt_mod.hpp
  - lib/fft/formal_power_series.hpp
  - lib/fft/ntt.hpp
  - lib/math/enumeration.hpp
  - lib/math/combination.hpp
  timestamp: '2021-10-02 14:41:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/power.test.cpp
  - test/aoj/dp/bell.test.cpp
  - test/aoj/dp/stirling.test.cpp
  - test/yosupo/convolution/convolution_mod.test.cpp
documentation_of: lib/math/modint.hpp
layout: document
redirect_from:
- /library/lib/math/modint.hpp
- /library/lib/math/modint.hpp.html
title: modint
---
