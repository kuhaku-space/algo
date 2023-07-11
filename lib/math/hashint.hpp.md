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
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.12/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"template/template.hpp\"\n\nstruct HashInt {\n  \
    \  static constexpr std::uint64_t get_mod() noexcept { return mod; }\n\n    constexpr\
    \ HashInt() noexcept : x(0) {}\n    constexpr HashInt(int y) noexcept : x(y >=\
    \ 0 ? y % mod : (mod - 1 - ~y % mod)) {}\n    constexpr HashInt(unsigned int y)\
    \ noexcept : x(y % mod) {}\n    constexpr HashInt(long y) noexcept : x(y >= 0\
    \ ? y % mod : (mod - 1 - ~y % mod)) {}\n    constexpr HashInt(unsigned long y)\
    \ noexcept : x(y % mod) {}\n    constexpr HashInt(long long y) noexcept : x(y\
    \ >= 0 ? y % mod : (mod - 1 - ~y % mod)) {}\n    constexpr HashInt(unsigned long\
    \ long y) noexcept : x(y % mod) {}\n\n    constexpr HashInt &operator+=(const\
    \ HashInt &rhs) noexcept {\n        if ((this->x += rhs.x) >= mod) this->x -=\
    \ mod;\n        return *this;\n    }\n    constexpr HashInt &operator-=(const\
    \ HashInt &rhs) noexcept {\n        if ((this->x += mod - rhs.x) >= mod) this->x\
    \ -= mod;\n        return *this;\n    }\n    constexpr HashInt &operator*=(const\
    \ HashInt &rhs) noexcept {\n        std::uint64_t au = this->x >> 31, ad = this->x\
    \ & this->mask31;\n        std::uint64_t bu = rhs.x >> 31, bd = rhs.x & this->mask31;\n\
    \        std::uint64_t mid = ad * bu + au * bd;\n        std::uint64_t midu =\
    \ mid >> 30, midd = mid & this->mask30;\n        this->x = this->_mod(au * bu\
    \ * 2 + midu + (midd << 31) + ad * bd);\n        return *this;\n    }\n    constexpr\
    \ HashInt &operator/=(const HashInt &rhs) noexcept {\n        *this *= rhs.inverse();\n\
    \        return *this;\n    }\n\n    constexpr HashInt &operator++() noexcept\
    \ {\n        if ((++(this->x)) >= mod) this->x -= mod;\n        return *this;\n\
    \    }\n    constexpr HashInt operator++(int) noexcept {\n        HashInt tmp(*this);\n\
    \        this->operator++();\n        return tmp;\n    }\n    constexpr HashInt\
    \ &operator--() noexcept {\n        if ((this->x += mod - 1) >= mod) this->x -=\
    \ mod;\n        return *this;\n    }\n    constexpr HashInt operator--(int) noexcept\
    \ {\n        HashInt tmp(*this);\n        this->operator--();\n        return\
    \ tmp;\n    }\n\n    constexpr HashInt operator-() const noexcept { return HashInt(-this->x);\
    \ }\n    constexpr HashInt operator+(const HashInt &rhs) const noexcept { return\
    \ HashInt(*this) += rhs; }\n    constexpr HashInt operator-(const HashInt &rhs)\
    \ const noexcept { return HashInt(*this) -= rhs; }\n    constexpr HashInt operator*(const\
    \ HashInt &rhs) const noexcept { return HashInt(*this) *= rhs; }\n    constexpr\
    \ HashInt operator/(const HashInt &rhs) const noexcept { return HashInt(*this)\
    \ /= rhs; }\n\n    constexpr bool operator==(const HashInt &rhs) const noexcept\
    \ { return this->x == rhs.x; }\n    constexpr bool operator!=(const HashInt &rhs)\
    \ const noexcept { return this->x != rhs.x; }\n\n    constexpr explicit operator\
    \ long() const noexcept { return x; }\n    constexpr explicit operator unsigned\
    \ long() const noexcept { return x; }\n    constexpr explicit operator long long()\
    \ const noexcept { return x; }\n    constexpr explicit operator unsigned long\
    \ long() const noexcept { return x; }\n\n    constexpr HashInt inverse() const\
    \ noexcept {\n        std::int64_t a = x, b = mod, u = 1, v = 0, t = 0;\n    \
    \    while (b > 0) {\n            t = a / b;\n            std::swap(a -= t * b,\
    \ b);\n            std::swap(u -= t * v, v);\n        }\n        return HashInt(u);\n\
    \    }\n\n    constexpr HashInt pow(std::uint64_t n) const noexcept { return HashInt(*this).pow_self(n);\
    \ }\n    constexpr HashInt &pow_self(std::uint64_t n) noexcept {\n        HashInt\
    \ res(1);\n        for (; n > 0; n >>= 1) {\n            if (n & 1) res *= *this;\n\
    \            *this *= *this;\n        }\n        *this = res;\n        return\
    \ *this;\n    }\n\n  private:\n    std::uint64_t x;\n\n    static constexpr std::uint64_t\
    \ mod = (1ul << 61) - 1;\n    static constexpr std::uint64_t mask30 = (1ul <<\
    \ 30) - 1;\n    static constexpr std::uint64_t mask31 = (1ul << 31) - 1;\n\n \
    \   constexpr std::uint64_t _mod(std::uint64_t x) const {\n        std::uint64_t\
    \ xu = x >> 61, xd = x & this->mod;\n        std::uint64_t res = xu + xd;\n  \
    \      if (res >= this->mod) res -= this->mod;\n        return res;\n    }\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/math/hashint.hpp
  requiredBy: []
  timestamp: '2023-05-22 20:02:34+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/math/hashint.hpp
layout: document
redirect_from:
- /library/lib/math/hashint.hpp
- /library/lib/math/hashint.hpp.html
title: lib/math/hashint.hpp
---
