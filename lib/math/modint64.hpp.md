---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.5/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\r\n#include \"template/template.hpp\"\r\n\r\ntemplate <int mod>\r\
    \nstruct ModInt {\r\n    constexpr ModInt() noexcept : x(0) {}\r\n    constexpr\
    \ ModInt(int y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}\r\n \
    \   constexpr ModInt(int64_t y) noexcept : x(y >= 0 ? y % mod : (mod - 1 - ~y\
    \ % mod)) {}\r\n\r\n    constexpr ModInt &operator+=(const ModInt &rhs) noexcept\
    \ {\r\n        if ((this->x += rhs.x) >= mod) this->x -= mod;\r\n        return\
    \ *this;\r\n    }\r\n    constexpr ModInt &operator-=(const ModInt &rhs) noexcept\
    \ {\r\n        if ((this->x += mod - rhs.x) >= mod) this->x -= mod;\r\n      \
    \  return *this;\r\n    }\r\n    constexpr ModInt &operator*=(const ModInt &rhs)\
    \ noexcept {\r\n        this->x = (int64_t)(1LL * this->x * rhs.x % mod);\r\n\
    \        return *this;\r\n    }\r\n    constexpr ModInt &operator/=(const ModInt\
    \ &rhs) noexcept {\r\n        *this *= rhs.inverse();\r\n        return *this;\r\
    \n    }\r\n\r\n    constexpr ModInt &operator++() noexcept {\r\n        if ((++(this->x))\
    \ >= mod) this->x -= mod;\r\n        return *this;\r\n    }\r\n    constexpr ModInt\
    \ operator++(int) noexcept {\r\n        ModInt tmp(*this);\r\n        this->operator++();\r\
    \n        return tmp;\r\n    }\r\n    constexpr ModInt &operator--() noexcept\
    \ {\r\n        if ((this->x += mod - 1) >= mod) this->x -= mod;\r\n        return\
    \ *this;\r\n    }\r\n    constexpr ModInt operator--(int) noexcept {\r\n     \
    \   ModInt tmp(*this);\r\n        this->operator--();\r\n        return tmp;\r\
    \n    }\r\n\r\n    constexpr ModInt operator-() const noexcept { return ModInt(-x);\
    \ }\r\n    constexpr ModInt operator+(const ModInt &rhs) const noexcept { return\
    \ ModInt(*this) += rhs; }\r\n    constexpr ModInt operator-(const ModInt &rhs)\
    \ const noexcept { return ModInt(*this) -= rhs; }\r\n    constexpr ModInt operator*(const\
    \ ModInt &rhs) const noexcept { return ModInt(*this) *= rhs; }\r\n    constexpr\
    \ ModInt operator/(const ModInt &rhs) const noexcept { return ModInt(*this) /=\
    \ rhs; }\r\n\r\n    constexpr bool operator==(const ModInt &rhs) const noexcept\
    \ { return this->x == rhs.x; }\r\n    constexpr bool operator!=(const ModInt &rhs)\
    \ const noexcept { return this->x != rhs.x; }\r\n\r\n    explicit operator int()\
    \ const noexcept { return int(x); }\r\n    explicit operator int64_t() const noexcept\
    \ { return x; }\r\n\r\n    constexpr ModInt inverse() const noexcept {\r\n   \
    \     int64_t a = x, b = mod, u = 1, v = 0, t;\r\n        while (b > 0) {\r\n\
    \            t = a / b;\r\n            swap(a -= t * b, b);\r\n            swap(u\
    \ -= t * v, v);\r\n        }\r\n        return ModInt(u);\r\n    }\r\n\r\n   \
    \ constexpr ModInt pow(int64_t n) const noexcept { return ModInt(*this).pow_self(n);\
    \ }\r\n    constexpr ModInt &pow_self(int64_t n) noexcept {\r\n        ModInt\
    \ res(1);\r\n        for (; n > 0; n >>= 1) {\r\n            if (n & 1) res *=\
    \ *this;\r\n            *this *= *this;\r\n        }\r\n        *this = res;\r\
    \n        return *this;\r\n    }\r\n\r\n    friend istream &operator>>(istream\
    \ &is, ModInt &rhs) {\r\n        int64_t t;\r\n        is >> t;\r\n        rhs\
    \ = ModInt<mod>(t);\r\n        return (is);\r\n    }\r\n    friend ostream &operator<<(ostream\
    \ &os, const ModInt &rhs) { return os << rhs.x; }\r\n\r\n    static int get_mod()\
    \ noexcept { return mod; }\r\n\r\n  private:\r\n    int64_t x;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/modint64.hpp
  requiredBy: []
  timestamp: '2022-06-14 14:06:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/modint64.hpp
layout: document
redirect_from:
- /library/lib/math/modint64.hpp
- /library/lib/math/modint64.hpp.html
title: lib/math/modint64.hpp
---
